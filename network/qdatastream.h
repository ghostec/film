#ifndef NETWORK_QDATASTREAM
#define NETWORK_QDATASTREAM

#include <QDataStream>

#include "math/rgb.h"

QDataStream& operator<<(QDataStream& stream, const film::rgb& pixel);
QDataStream& operator>>(QDataStream& stream, film::rgb& pixel);

#endif
