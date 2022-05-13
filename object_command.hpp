#ifndef OBJECTCOMMAND_HPP
#define OBJECTCOMMAND_HPP

#include <QObject>
#include <QTimer>

#include "define_default.hpp"

enum class Complete_State {
  None,
  Error,
  Complete
};

struct Command_Info {
  int Type;
  int Enum;
  std::vector<char> Bytes;
};

class ObjectCommand : public QObject {
  Q_OBJECT

public:
  explicit ObjectCommand(QObject*);

  void clearCommand();
  void clearError();
  void clearList();
  void commandError(const std::string&, const std::string&);
  void pushBack(const Command_Info&);
  void pushFront(const Command_Info&);
  void pushInsert(const int, const Command_Info&);
  void startTime(const int);
  bool isEmpty();
  bool isError();
  Command_Info getFront();
  Complete_State getState(const int, const int, const bool);

private:
#define COMMAND_ERROR -1
  bool Flag_Error = true;
  QTimer* Time_Out;
  std::list<Command_Info> List_Command;

signals:
  void signalCommand();
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalTimeout();
};

#endif // OBJECTCOMMAND_HPP
