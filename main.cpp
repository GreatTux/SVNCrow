#include "output.h"
#include "application.h"
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
	Application a(argc, argv);
	a.setQuitOnLastWindowClosed(false);

	qDebug() << "Launching SVN Crow";

	QSystemTrayIcon sysTray;
	sysTray.setIcon(QIcon(":/trayicon"));
	sysTray.setToolTip("SVN Crow");
	a.setSysIcon(&sysTray);
	sysTray.show();

	return a.exec();
}
