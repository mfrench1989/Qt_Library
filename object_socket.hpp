#ifndef OBJECTSOCKET_HPP
#define OBJECTSOCKET_HPP

#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

#include "define_default.hpp"

class ObjectSocket : public QTcpSocket {
  Q_OBJECT

public:
  explicit ObjectSocket(const std::string&, const std::string&, QObject* = nullptr);
  void socketConnect();
  void socketDisconnect();
  void socketWrite(std::vector<char>);

private:
#define WAIT_TIME 1000
  enum class Command_Type {
    Disconnect,
    Connect,
    Write
  };
  struct Command_Info {
    Command_Type Type;
    std::vector<char> Data;
  };

  bool Flag_Error = false;
  std::string Socket_Address;
  std::string Socket_Port;
  QTimer* Time_Out;
  std::vector<Command_Info> Vector_Command;

  void socketError(const std::string&, const std::string&);

private slots:
  void slotSocketBytesIn();
  void slotSocketBytesOut(qint64);
  void slotSocketChangeState(QAbstractSocket::SocketState);
  void slotSocketCommand(bool);
  void slotSocketQuit();
  void slotSocketTimeout();

signals:
  void signalCommand(bool);
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalSocketComplete(bool);
  void signalSocketIn(std::vector<char>);
};

#endif // OBJECTSOCKET_HPP
