#ifndef TOAST_H
#define TOAST_H

#include "ui_toast.h"
#include "crowmon.h"
#include <QColor>
#include <QFont>

class Toast : public QWidget
{
	Q_OBJECT
	
public:
	explicit		Toast(QFont font,
						  QColor fontColor,
						  QColor color,
						  int iOpacity,
						  QWidget *parent = nullptr);
	
private:
	QColor			negative(QColor &);

protected:
	void			changeEvent(QEvent *e);
	void			mousePressEvent(QMouseEvent *);

public:
	void			updateStyleSheet();
	void			setData(const logmsg_t &);

public slots:
	void			showFadeIn();
	void			hideFadeOut();
	
private:
	Ui::Toast		ui;
	QFont			m_font;
	QColor			m_fontColor;
	QColor			m_color;
	int				m_iOpacity; //0-255
};

#endif // TOAST_H
