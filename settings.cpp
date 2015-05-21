#include "settings.h"
#include "crowmon.h"
#include "output.h"
#include <QSettings>
#include <QColorDialog>

Settings::Settings(QWidget *parent) :
	QDialog(parent, Qt::Window)
{
	ui.setupUi(this);
}

void Settings::initialize(	const QString&	url,
							const QString&	user,
							const QString&	pwd,
							int				iCheckPeriod,
							const QFont&	font,
							const QColor&	fontColor,
							const QColor&	color,
							int				iOpacity,
							int				iDisplayTimeout)
{
	//Set values
	ui.m_urlLineEdit->setText(url);
	ui.m_usernameLineEdit->setText(user);
	ui.m_passwordLineEdit->setText(pwd);

	ui.m_checkPeriodSlider->setValue(iCheckPeriod);
	ui.m_checkSpinBox->setValue(iCheckPeriod);

	ui.m_fontComboBox->setCurrentFont(font);
	ui.m_opacitySlider->setValue(iOpacity);
	ui.m_opacitySpinBox->setValue(iOpacity);
	ui.m_displayTimeoutSlider->setValue(iDisplayTimeout);
	ui.m_displayTimeoutSpinBox->setValue(iDisplayTimeout);

	m_color = color;
	updateColorLabel(color);

	m_fontColor = fontColor;
	updateFontColorLabel(m_fontColor);
}

void Settings::save()
{
	QSettings settings(CROW_ORG, CROW_APP);

	m_user = ui.m_usernameLineEdit->text();
	m_url = ui.m_urlLineEdit->text();
	m_pwd = ui.m_passwordLineEdit->text();
	settings.setValue("RepoURL", m_url);
	settings.setValue("Username", m_user);
	settings.setValue("Pwd", CrowMon::shadowPass(m_pwd, m_user));
	settings.setValue("Font", ui.m_fontComboBox->currentFont());
	settings.setValue("FontColor", m_fontColor);
	settings.setValue("Color", m_color);
	settings.setValue("Opacity", ui.m_opacitySlider->value());
	settings.setValue("CheckPeriod", ui.m_checkPeriodSlider->value());
	settings.setValue("DisplayTimeOut", ui.m_displayTimeoutSlider->value());
}

void Settings::updateFontColorLabel(const QColor& color)
{
	QPixmap pix(ui.m_fontColorLabel->width(), ui.m_fontColorLabel->height());
	pix.fill(color);
	ui.m_fontColorLabel->setPixmap(pix);
}

void Settings::updateColorLabel(const QColor& color)
{
	QPixmap pix(ui.m_colorLabel->width(), ui.m_colorLabel->height());
	pix.fill(color);
	ui.m_colorLabel->setPixmap(pix);
}

void Settings::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}

void Settings::done(int r)
{
	if(r == QDialog::Accepted)
		save();

	QDialog::done(r);
}

void Settings::on_m_fontColorButton_clicked()
{
	QColor color = QColorDialog::getColor(m_color, this);
	if(color.isValid())
	{
		m_fontColor = color;
		updateFontColorLabel(m_fontColor);
	}
}

void Settings::on_m_colorButton_clicked()
{
	QColor color = QColorDialog::getColor(m_color, this);
	if(color.isValid())
	{
		m_color = color;
		updateColorLabel(m_color);
	}
}

void Settings::on_m_buttonBox_clicked(QAbstractButton *button)
{
	Q_ASSERT(button);

	if(ui.m_buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
	{
		save();
		emit applied(this);
	}
}
