#ifndef OBJECTCONSOLE_HPP
#define OBJECTCONSOLE_HPP

#include <QSocketNotifier>

#include "define_default.hpp"

class ObjectConsole : public QSocketNotifier {
  Q_OBJECT

public:
  explicit ObjectConsole(QObject* = nullptr);
  void consoleWrite(const std::string&);

private:

private slots:
  void slotConsoleRead();

signals:
  void signalConsoleIn(std::string);
  void signalEvent(Event_Type, std::string, std::string, std::string);
};

#endif // OBJECTCONSOLE_HPP
