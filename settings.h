#ifndef SETTINGS_H
#define SETTINGS_H

#include "ui_settings.h"
#include <QColor>
#include <QFont>

class Settings : public QDialog
{
	Q_OBJECT
	
public:
	explicit Settings(QWidget *parent = 0);
	
private:
	void	updateFontColorLabel(QColor);
	void	updateColorLabel(QColor);
	void	save();
protected:
	void		changeEvent(QEvent *e);
	virtual	void done(int);
public:
	void	initialize(
				QString url,
				QString user,
				QString pwd,
				int iCheckPeriod,
				QFont font,
				QColor fontColor,
				QColor color,
				int iOpacity,
				int iDisplayTimeout);

	QString	getUser(){return m_user;}
	QString	getURL(){return m_url;}
	QString	getPWD(){return m_pwd;}
	QFont		getFont(){return ui.m_fontComboBox->currentFont();}
	QColor	getFontColor(){return m_fontColor;}
	QColor	getColor(){return m_color;}
	int		getCheckPeriod(){return ui.m_checkPeriodSlider->value();}
	int		getOpacity(){return ui.m_opacitySlider->value();}
	int		getDisplayTimeout(){return ui.m_displayTimeoutSlider->value();}

signals:
	void applied(Settings*);

private slots:
	void	on_m_colorButton_clicked();
	void	on_m_buttonBox_clicked(QAbstractButton *button);

	void on_m_fontColorButton_clicked();

private:
	Ui::Settings	ui;
	QColor			m_fontColor;
	QColor			m_color;
	QString			m_user;
	QString			m_url;
	QString			m_pwd;
};

#endif // SETTINGS_H
