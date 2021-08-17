#ifndef OBJECTCONSOLE_HPP
#define OBJECTCONSOLE_HPP

#include <QSocketNotifier>

class ObjectConsole : public QSocketNotifier {
  Q_OBJECT

public:
  explicit ObjectConsole(QObject* = nullptr);

private:

private slots:
  void slotConsoleRead();
  void slotConsoleWrite(std::string);

signals:
  void signalConsoleIn(std::vector<std::string>);
};

#endif // OBJECTCONSOLE_HPP
