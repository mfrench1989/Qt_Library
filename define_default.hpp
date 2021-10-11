#ifndef DEFINE_DEFAULT_HPP
#define DEFINE_DEFAULT_HPP

#include <QDebug>

#define FILE_LOG ".log"

#define PORT_MAX 65535

enum class Event_Type {
  Debug,
  Error,
  Warning,
  Success,
  Default
};

enum class Mode_Login {
  None,
  User,
  Admin
};

#endif // DEFINE_DEFAULT_HPP
