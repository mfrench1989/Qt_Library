#include "function_string.hpp"

#include "object_command.hpp"

ObjectCommand::ObjectCommand(QObject *parent) : QObject(parent) {
  this->setObjectName(this->parent()->objectName() + "_Command");

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(Time_Out, SIGNAL(timeout()), this, SIGNAL(signalTimeout()), Qt::DirectConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectCommand::clearCommand() {
  Time_Out->stop();
  if (!List_Command.empty()) {
      List_Command.pop_front();
    }
  Q_EMIT signalCommand();
}

void ObjectCommand::clearError() {
  Flag_Error = false;
}

void ObjectCommand::clearList() {
  Flag_Error = false;
  Time_Out->stop();
  List_Command.clear();
}

void ObjectCommand::commandError(const std::string& function_in, const std::string& error_in) {
  clearList();
  Flag_Error = true;
  if (!function_in.empty() && !error_in.empty()) {
      Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
    }
}

void ObjectCommand::pushBack(const Command_Info& command_in) {
  List_Command.push_back(command_in);
}

void ObjectCommand::pushFront(const Command_Info& command_in) {
  List_Command.push_front(command_in);
}

void ObjectCommand::pushInsert(const int index_in, const Command_Info& command_in) {
  std::list<Command_Info>::iterator iterator = List_Command.begin();
  std::advance(iterator, index_in);
  List_Command.insert(iterator, command_in);
}

void ObjectCommand::startTime(const int time_in) {
  if (time_in >= 0) {
      Time_Out->start(time_in);
    }
}

bool ObjectCommand::isEmpty() {
  return List_Command.empty();
}

bool ObjectCommand::isError() {
  return Flag_Error;
}

Command_Info ObjectCommand::getFront() {
  return (List_Command.empty() ? Command_Info() : List_Command.front());
}

Complete_State ObjectCommand::getState(const int type_in, const int enum_in, const bool state_in) {
  if(!List_Command.empty() && List_Command.front().Type == type_in && List_Command.front().Enum == enum_in && state_in) {
      return Complete_State::Complete;
    }
  else if (!List_Command.empty() && List_Command.front().Type == type_in &&
           (COMMAND_ERROR == enum_in || (List_Command.front().Enum == enum_in && ! state_in))) {
      return Complete_State::Error;
    }
  return Complete_State::None;
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/

/*================================================================*/
/*Private Slots*/
/*================================================================*/
