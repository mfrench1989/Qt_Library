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

struct Init_Connect {
  QObject* ObjectEvent = nullptr;
  QObject* WindowMain = nullptr;
};

#endif // DEFINE_DEFAULT_HPP
