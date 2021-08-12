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

enum class Mode_Login {
  None,
  User,
  Admin
};

struct Data_Connect {
  QObject* ObjectEvent;
  QObject* WindowMain;
};

#endif // DEFINE_DEFAULT_HPP
