#ifndef NETWORK_FILM_JOB_TH
#define NETWORK_FILM_JOB_TH

#include <QDataStream>

namespace film {
struct film_job_t {
  quint16 frameId, width, height, firstRow, lastRow;
};

QDataStream& operator<<(QDataStream& stream, const film_job_t& job);
QDataStream& operator>>(QDataStream& stream, film_job_t& job);
}

#endif
