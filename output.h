#ifndef OUTPUT_H
#define OUTPUT_H

#include <QDebug>

#define QT_NO_DEBUG_OUTPUT

#define cDebug qDebug()<<__PRETTY_FUNCTION__<<"-"
#define cWarning qWarning()<<__PRETTY_FUNCTION__<<"-"
#define cCritical qCritical()<<__PRETTY_FUNCTION__<<"-"
#define cFatal qFatal()<<__PRETTY_FUNCTION__<<"-"

#endif // OUTPUT_H
