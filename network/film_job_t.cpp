#include "film_job_t.h"

namespace film {
QDataStream& operator<<(QDataStream& stream, const film_job_t& job) {
  stream << job.frameId << job.width << job.height << job.firstRow
         << job.lastRow;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, film_job_t& job) {
  stream >> job.frameId >> job.width >> job.height >> job.firstRow >>
      job.lastRow;
  return stream;
}
}
