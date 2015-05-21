#ifndef SETTINGS_H
#define SETTINGS_H

#include "ui_settings.h"
#include <QColor>
#include <QFont>

class Settings : public QDialog
{
	Q_OBJECT

public:
	explicit Settings(QWidget *parent = nullptr);
	
private:
	void			updateFontColorLabel(const QColor &);
	void			updateColorLabel(const QColor &);
	void			save();
protected:
	void			changeEvent(QEvent *e);
	virtual	void	done(int);
public:
	void			initialize(	const QString &url,
								const QString &user,
								const QString &pwd,
								int iCheckPeriod,
								const QFont &font,
								const QColor &fontColor,
								const QColor &color,
								int iOpacity,
								int iDisplayTimeout);

	QString			getUser() const {return m_user;}
	QString			getURL() const {return m_url;}
	QString			getPWD() const {return m_pwd;}
	QFont			getFont() const {return ui.m_fontComboBox->currentFont();}
	QColor			getFontColor() const {return m_fontColor;}
	QColor			getColor() const {return m_color;}
	int				getCheckPeriod() const {return ui.m_checkPeriodSlider->value();}
	int				getOpacity() const {return ui.m_opacitySlider->value();}
	int				getDisplayTimeout() const {return ui.m_displayTimeoutSlider->value();}

signals:
	void			applied(Settings*);

private slots:
	void			on_m_colorButton_clicked();
	void			on_m_buttonBox_clicked(QAbstractButton *button);
	void			on_m_fontColorButton_clicked();

private:
	Ui::Settings	ui;
	QColor			m_fontColor;
	QColor			m_color;
	QString			m_user;
	QString			m_url;
	QString			m_pwd;
};

#endif // SETTINGS_H
