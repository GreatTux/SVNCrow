#include "widget.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "qmath.h"

Widget::Widget(QFont font, QColor fontColor, QColor color, int iOpacity, QWidget *parent) :
	QWidget(parent, Qt::ToolTip|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint)
{
	this->setAttribute(Qt::WA_TranslucentBackground);
	ui.setupUi(this);

	m_font = font;
	m_fontColor = fontColor;
	m_color = color;
	m_iOpacity = iOpacity;

	this->setFont(m_font);

	updateStyleSheet();
}

QColor Widget::negative(QColor color)
{
	color.setRed(qAbs(255-color.red()));
	color.setGreen(qAbs(255-color.green()));
	color.setBlue(qAbs(255-color.blue()));
	return color;
}

void Widget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}

void Widget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton ||
		event->button() == Qt::MiddleButton )
	{
		this->deleteLater();
	}
}

void Widget::updateStyleSheet()
{
	ui.widget->setStyleSheet(
		QString(	".QWidget{border-radius: 4px;" \
					"background-color: rgba(%1,%2,%3,%4);}" \
					".QLabel{color: %5; font-size: 11px;}")
		.arg(m_color.red()).arg(m_color.green()).arg(m_color.blue()).arg(m_iOpacity).arg(m_fontColor.name())
	);
}

void Widget::setData(logmsg_t s)
{
	ui.m_authorLabel->setText(s.author);
	ui.m_dateLabel->setText(s.date.toString());
	ui.m_revLabel->setText(QString::number(s.revision));
	ui.m_logLabel->setText(s.msg);
}

void Widget::showFadeIn()
{
	this->setWindowOpacity(0.0);

	QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity", this);
	anim->setDuration(350);
	anim->setStartValue(0.0);
	anim->setEndValue(1.0);

	this->showNormal();
	this->raise();

	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::hideFadeOut()
{
	QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity", this);
	anim->setDuration(350);
	anim->setStartValue(1.0);
	anim->setEndValue(0.0);

	anim->start(QAbstractAnimation::DeleteWhenStopped);
	connect(anim, SIGNAL(finished()), this, SLOT(deleteLater()));
}
