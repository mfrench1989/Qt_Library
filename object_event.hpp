#ifndef OBJECTEVENT_HPP
#define OBJECTEVENT_HPP

#include <QObject>

#include "define_default.hpp"

class ObjectEvent : public QObject {
  Q_OBJECT

public:
  explicit ObjectEvent(QObject* = nullptr);
  Q_INVOKABLE bool initConfig(const std::vector<QObject*>);

private:
  bool Flag_Debug = false;

private slots:
  void slotEvent(Event_Type, std::string, std::string, std::string);
  void slotMode_Debug(bool);

signals:
  void signalMessage(std::string);
};

#endif // OBJECTEVENT_HPP
