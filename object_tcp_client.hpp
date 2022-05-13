#ifndef OBJECTTCPCLIENT_HPP
#define OBJECTTCPCLIENT_HPP

#include <QTcpSocket>
#include <QTimer>

#include "define_default.hpp"

class ObjectTCPClient : public QTcpSocket {
  Q_OBJECT

public:
  explicit ObjectTCPClient(const std::string&, const std::string&, QObject*);
  void clientConnect();
  void clientDisconnect();
  void clientWrite(const std::vector<char>&);

private:
#define WAIT_CLIENT 500
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
  std::list<Command_Info> List_Command;

  void clearList();
  void clientError(const std::string&, const std::string&);

private slots:
  void slotClientCommand(bool);
  void slotClientConnect();
  void slotClientDisconnect();
  void slotClientQuit();
  void slotClientRead();
  void slotClientTimeout();

signals:
  void signalClientCommand(bool);
  void signalClientComplete(bool);
  void signalClientIn(std::vector<char>);
  void signalEvent(Event_Type, std::string, std::string, std::string);
};

#endif // OBJECTTCPCLIENT_HPP
