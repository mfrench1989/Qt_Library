#include <unistd.h>
#include <iostream>

#include "CPPLibrary/function_string.hpp"

#include "object_console.hpp"

ObjectConsole::ObjectConsole(QObject* parent) : QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, parent) {
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Console");

  QObject::connect(this, SIGNAL(activated(int)), this, SLOT(slotConsoleRead()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/

/*================================================================*/
/*Private Methods*/
/*================================================================*/

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectConsole::slotConsoleRead() {
  std::string string_in;
  std::getline(std::cin, string_in);
  Q_EMIT signalConsoleIn(string_in);
  Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(), stringFuncInfo(this, __func__), "<IN>\t" + string_in);
}

void ObjectConsole::slotConsoleWrite(std::string string_out) {
  std::cout << "[" + stringDateTime("%H:%M:%S") + "] " + string_out << std::endl;
  Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(), stringFuncInfo(this, __func__), "<OUT>\t" + string_out);
}
