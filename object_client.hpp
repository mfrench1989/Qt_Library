#ifndef OBJECTCLIENT_HPP
#define OBJECTCLIENT_HPP

#include <QTcpSocket>
#include <QTimer>

#include "define_default.hpp"

class ObjectClient : public QTcpSocket {
  Q_OBJECT

public:
  explicit ObjectClient(const std::string&, const std::string&, QObject* = nullptr);
  void clientConnect();
  void clientDisconnect();
  void clientWrite(std::vector<char>);

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
  std::string Client_Address;
  std::string Client_Port;
  QTimer* Time_Out;
  std::vector<Command_Info> Vector_Command;

  void clientError(const std::string&, const std::string&);

private slots:
  void slotClientRead();
  void slotClientChangeState(QAbstractSocket::SocketState);
  void slotClientCommand(bool);
  void slotClientQuit();
  void slotClientTimeout();

signals:
  void signalCommand(bool);
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalClientComplete(bool);
  void signalClientIn(std::vector<char>);
};

#endif // OBJECTCLIENT_HPP
