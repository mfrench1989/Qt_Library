#ifndef OBJECTTCPCLIENT_HPP
#define OBJECTTCPCLIENT_HPP

#include <QTcpSocket>
#include <QTimer>

#include "define_default.hpp"

class ObjectTCPClient : public QTcpSocket {
  Q_OBJECT

public:
  explicit ObjectTCPClient(const std::string&, const std::string&, QObject* = nullptr);
  void clientConnect();
  void clientDisconnect();
  void clientWrite(const std::vector<char>&);

private:
#define WAIT_TIME 1000
  enum class Command_Type {
    Disconnect,
    Connect,
    Write
  };
  struct Command_Info {
    Command_Type Type;
    std::vector<char> Bytes;
  };

  bool Flag_Error = false;
  std::string Client_Address;
  std::string Client_Port;
  QTimer* Time_Out;
  std::vector<Command_Info> Vector_Command;

  void clientError(const std::string&, const std::string&);

private slots:
  void slotClientCommand(bool);
  void slotClientConnect();
  void slotClientDisconnect();
  void slotClientQuit();
  void slotClientRead();
  void slotClientTimeout();

signals:
  void signalClientIn(std::vector<char>);
  void signalClientCommand(bool);
  void signalClientComplete(bool);
  void signalEvent(Event_Type, std::string, std::string, std::string);
};

#endif // OBJECTTCPCLIENT_HPP