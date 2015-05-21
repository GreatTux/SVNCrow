#include "application.h"
#include "output.h"
#include "widget.h"
#include "settings.h"
#include "qmath.h"

#include <QDomComment>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QProcess>
#include <QMenu>
#include <QSettings>

Application::Application (int & argc, char ** argv ):
	QApplication(argc, argv)
{
	QSettings settings(CROW_ORG, CROW_APP);

	//Retrieve values
	m_url = settings.value("RepoURL").toString();
	m_user = settings.value("Username").toString();
	m_pwd = CrowMon::unShadowPass(settings.value("Pwd").toString(), m_user);
	m_iCheckPeriod = settings.value("CheckPeriod", 6).toInt();
	m_color = settings.value("Color", QColor(66,95,150)).value<QColor>();
	m_fontColor = settings.value("FontColor", QColor(255,255,255)).value<QColor>();
	m_font = settings.value("Font", QFont()).value<QFont>();
	m_iOpacity = settings.value("Opacity", 90).toInt();
	m_iDisplayTimeout = settings.value("DisplayTimeOut", 6).toInt();
	m_trayIcon = NULL;
	m_lastlog.author = "";
	m_lastlog.date = QDateTime();
	m_lastlog.msg = "";
	m_lastlog.revision = -1;
	m_lastlog.valid = false;

	m_iTimerID = this->startTimer(m_iCheckPeriod*10000);

	connect(this, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));

	doPollRepository();
}

Application::~Application()
{

}

void Application::timerEvent(QTimerEvent *event)
{
	if(event->timerId() == m_iTimerID)
		doPollRepository();
}

void Application::applySettings(Settings* settingsDiag)
{
	m_url = settingsDiag->getURL();
	m_user = settingsDiag->getUser();
	m_pwd = settingsDiag->getPWD();
//--------------------------------------------------
	m_iCheckPeriod = settingsDiag->getCheckPeriod();
//--------------------------------------------------
	m_fontColor = settingsDiag->getFontColor();
	m_font = settingsDiag->getFont();
	m_color = settingsDiag->getColor();
	m_iOpacity = settingsDiag->getOpacity();
	m_iDisplayTimeout = settingsDiag->getDisplayTimeout();
}

void Application::forceReDisplay()
{
	if(m_lastlog.valid)
		showWidget(m_lastlog);
	else
		doPollRepository(true);
}

void Application::aboutToQuit()
{
}

void Application::setSysIcon(QSystemTrayIcon *i)
{
	Q_ASSERT(i);

	if(m_trayIcon)
		m_trayIcon->deleteLater();

	m_trayIcon = i;
	QMenu* menu = new QMenu();
	menu->addAction(tr("Settings..."), this, SLOT(showSettings()));
	menu->addSeparator();
	menu->addAction(tr("Exit SVN Crow"), this, SLOT(quit()));
	m_trayIcon->setContextMenu(menu);

	connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(handleSysTrayIconClick(QSystemTrayIcon::ActivationReason)));
}

void Application::doPollRepository(bool bForceShow)
{
	QStringList arguments;
	arguments << "log"
				 << "-l1"
				 << "--xml"
				 << "--non-interactive"
				 << QString("--username=%1").arg(m_user)
				 << QString("--password=%1").arg(m_pwd)
				 << m_url
				 ;

	QProcess myProcess;
	myProcess.start("svn", arguments);

	if (!myProcess.waitForStarted())
		cDebug << "Error starting process";


	if (!myProcess.waitForFinished())
		cDebug << "Error waiting for process";

	QByteArray result = myProcess.readAllStandardOutput();
	//cDebug << "Output:" << QString(result);

	logmsg_t s = parseLog(QString::fromUtf8(result));
	if(s.valid)
	{
		if((m_lastlog.revision < s.revision && m_lastlog.valid)||bForceShow)
			showWidget(s);

		m_lastlog = s;
	}
}

void Application::showWidget(const logmsg_t &s)
{
	QDesktopWidget desktop;
	const int margin = 10;

	int iOpacity = qRound((m_iOpacity/100.0)*255);
	Widget* widget = new Widget(m_font, m_fontColor, m_color, iOpacity);
	widget->setData(s);
	widget->move(desktop.availableGeometry().width()- widget->width() - margin,
					 desktop.availableGeometry().height() - widget->height() - margin);

	widget->showFadeIn();
	QTimer::singleShot(m_iDisplayTimeout*1000, widget, SLOT(hideFadeOut()));
}

logmsg_t Application::parseLog(const QString& msg)
{
	QDomDocument doc;
	QDomNodeList element;
	doc.setContent(msg);

	logmsg_t s;
	s.valid = true;

	element = doc.elementsByTagName("author");
	if(element.count())
	{
		QString author = element.at(0).firstChild().nodeValue();
		cDebug << "author" << author;
		s.author = author;
	}
	else
		s.valid = false;

	element  = doc.elementsByTagName("date");
	if(element.count())
	{
		QString date = element.at(0).firstChild().nodeValue();
		cDebug << "date" << date;
		s.date = QDateTime::fromString(date, Qt::ISODate);
	}
	else
		s.valid = false;

	element  = doc.elementsByTagName("logentry");
	if(element.count())
	{
		if(element.at(0).attributes().contains("revision"))
		{
			QString rev = element.at(0).attributes().namedItem("revision").nodeValue();
			cDebug << "logentry - rev" <<  rev;
			s.revision = rev.toInt();
		}
		else
			s.valid = false;
	}
	else
		s.valid = false;

	element  = doc.elementsByTagName("msg");
	if(element.count())
	{
		QString msg = element.at(0).firstChild().nodeValue();
		cDebug << "msg" << msg;
		s.msg = msg;
	}
	else
		s.valid = false;

	return s;
}

void Application::showSettings()
{
	Settings* settingsDiag = new Settings();
	connect(settingsDiag, SIGNAL(applied(Settings*)), this, SLOT(applySettings(Settings*)));
	connect(settingsDiag, SIGNAL(applied(Settings*)), this, SLOT(forceReDisplay()));
	settingsDiag->initialize(m_url,
									 m_user,
									 m_pwd,
									 m_iCheckPeriod,
									 m_font,
									 m_fontColor,
									 m_color,
									 m_iOpacity,
									 m_iDisplayTimeout);

	if(settingsDiag->exec() == QDialog::Accepted)
		applySettings(settingsDiag);

	settingsDiag->deleteLater();
}

void Application::handleSysTrayIconClick(QSystemTrayIcon::ActivationReason reason)
{
	if(reason == QSystemTrayIcon::Trigger)
		forceReDisplay();
}
