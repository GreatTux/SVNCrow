#include "crowmon.h"

namespace CrowMon
{
	QByteArray	XOR(const QByteArray &data, const QByteArray &key)
	{
		QByteArray output, keyBuff;

		// Expanding key size to at least data size
		while(keyBuff.size() < data.size())
			keyBuff.append(key);

		// XOR for every byte of data with key
		for(int i=0 ; i < data.size() ; i++)
			output.append(data.at(i) ^ keyBuff.at(i));

		return output;
	}

	QString	shadowPass(const QString &pass, const QString &key)
	{
		QByteArray bPass(pass.toStdString().c_str());
		QByteArray bKey(key.toStdString().c_str());
		return XOR(bPass, bKey).toBase64().constData();
	}

	QString	unShadowPass(const QString &shadow, const QString &key)
	{
		QByteArray bShadow = QByteArray::fromBase64(shadow.toStdString().c_str());
		QByteArray bKey(key.toStdString().c_str());
		return XOR(bShadow, bKey).constData();
	}
}
