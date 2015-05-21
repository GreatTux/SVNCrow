#ifndef CROWMON_H
#define CROWMON_H

#include <QString>
#include <QDateTime>
#include <QtAlgorithms>
#include <QByteArray>

//-----------------------------------------------------------------------------

#define CROW_ORG "SVNCrow"
#define CROW_APP "SVNCrow"

struct logmsg_t
{
	int			revision;
	QString		author;
	QDateTime	date;
	QString		msg;
	bool			valid;
};

namespace CrowMon
{

	QByteArray	XOR(const QByteArray &data, const QByteArray &key);
	QString		shadowPass(const QString &pass, const QString &key);
	QString		unShadowPass(const QString &shadow, const QString &key);

}

#endif // CROWMON_H
