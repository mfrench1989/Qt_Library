#include <unistd.h>
#include <iostream>

#include "CPPLibrary/function_string.hpp"

#include "object_console.hpp"

ObjectConsole::ObjectConsole(QObject* parent) : QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, parent) {
  this->setObjectName((parent ? this->parent()->objectName() : "") + "Console");

  QObject::connect(this, SIGNAL(activated()), this, SLOT(slotConsoleRead()), Qt::DirectConnection);
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
  Q_EMIT signalConsoleIn(stringSplit(string_in, " "));
//  Q_EMIT signalConsoleIn(stringSplit(QTextStream(stdin).readAll().toStdString(), " "));
}

void ObjectConsole::slotConsoleWrite(std::string string_out) {
  std::cout << "[" + stringDateTime("%H:%M:%S") + "] " + string_out << std::endl;
}
