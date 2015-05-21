#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"
#include "crowmon.h"
#include <QColor>
#include <QFont>

class Widget : public QWidget
{
	Q_OBJECT
	
public:
	explicit			Widget(QFont font, QColor fontColor, QColor color, int iOpacity, QWidget *parent = 0);
	
private:
	QColor			negative(QColor);
protected:
	void				changeEvent(QEvent *e);
	void				mousePressEvent(QMouseEvent *);

public:
	void				updateStyleSheet();
	void				setData(logmsg_t);

public slots:
	void				showFadeIn();
	void				hideFadeOut();
	
private:
	Ui::Widget		ui;
	QFont				m_font;
	QColor			m_fontColor;
	QColor			m_color;
	int				m_iOpacity; //0-255
};

#endif // WIDGET_H
