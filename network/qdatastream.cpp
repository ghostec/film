#include "qdatastream.h"

QDataStream& operator<<(QDataStream& stream, const film::rgb& pixel) {
  stream << pixel.r << pixel.g << pixel.b;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, film::rgb& pixel) {
  stream >> pixel.r >> pixel.g >> pixel.b;
  return stream;
}
