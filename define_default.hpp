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

struct Error_Code {
  int Code;
  std::string Text;
};

inline std::string errorText(const std::vector<Error_Code>& vector_error, int code_in) {
  for (const Error_Code& error : vector_error) {
      if (error.Code == code_in) {
          return error.Text;
        }
    }
  return std::string();
}

#endif // DEFINE_DEFAULT_HPP
