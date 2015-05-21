#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QColor>
#include <QFont>
#include <QSystemTrayIcon>
#include "crowmon.h"
class Settings;

class Application : public QApplication
{
	Q_OBJECT

public:
	explicit			Application(int & argc, char ** argv);
						~Application();

private:
	void				doPollRepository(bool bForceShow = false);
	void				showWidget(const logmsg_t&);
protected:
	logmsg_t			parseLog(const QString&);
	void				timerEvent(QTimerEvent *event);
public:
	void				setSysIcon(QSystemTrayIcon* i);

public slots:
	void				applySettings(Settings*);
	void				forceReDisplay();
	void				aboutToQuit();
	void				showSettings();
	void				handleSysTrayIconClick(QSystemTrayIcon::ActivationReason);

private:
	logmsg_t					m_lastlog;
	int						m_iTimerID;
	int						m_iLastRevision;
	QString					m_url;
	QString					m_user;
	QString					m_pwd;
	QFont						m_font;
	QColor					m_fontColor;
	QColor					m_color;
	int						m_iCheckPeriod;
	int						m_iOpacity;
	int						m_iDisplayTimeout;
	QSystemTrayIcon*		m_trayIcon;
};

#endif // APPLICATION_H
