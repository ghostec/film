#ifndef MESSAGE_TH
#define MESSAGE_TH

#include <QDataStream>

enum class message_t : quint16 {
  REGISTER_WORKER,
  REGISTER_GUI,
  FILM_JOB,
  FILM_JOB_RESULT
};

inline QDataStream& operator<<(QDataStream& stream, const message_t& type) {
  stream << static_cast<quint16>(type);
  return stream;
}

inline QDataStream& operator>>(QDataStream& stream, message_t& type) {
  quint16 itype;
  stream >> itype;
  type = static_cast<message_t>(itype);
  return stream;
}

#endif
