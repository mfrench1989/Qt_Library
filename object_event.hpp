#ifndef OBJECTEVENT_HPP
#define OBJECTEVENT_HPP

#include <QObject>

#include "define_default.hpp"

class ObjectEvent : public QObject {
  Q_OBJECT

public:
  explicit ObjectEvent(QObject *parent = nullptr);
  Q_INVOKABLE void initConnect(const std::vector<QObject*>);

private:
  bool Flag_Debug = false;

private slots:
  void slotEvent(Event_Type, std::string, std::string, std::string);
  void slotModeDebug(bool);

signals:
  void signalMessage(std::string);

};

#endif // OBJECTEVENT_HPP
