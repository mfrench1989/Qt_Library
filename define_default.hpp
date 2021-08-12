#ifndef DEFINE_DEFAULT_HPP
#define DEFINE_DEFAULT_HPP

#include <QDebug>

#define FILE_LOG ".log"

enum class Event_Type {
  Default,
  Debug,
  Error,
  Warning,
  Success
};

struct Data_Connect {
  QObject* WindowMain;
};

#endif // DEFINE_DEFAULT_HPP
