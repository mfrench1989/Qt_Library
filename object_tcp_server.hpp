#ifndef OBJECTTCPSERVER_HPP
#define OBJECTTCPSERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "define_default.hpp"

class ObjectTCPServer : public QTcpServer {
  Q_OBJECT

public:
  explicit ObjectTCPServer(const std::string&, const std::string&, QObject*);
  void serverWrite(const std::vector<char>&);
  bool serverListen();

private:
  enum class Command_Type {
    Write
  };
  struct Command_Info {
    Command_Type Type;
    std::vector<char> Bytes;
  };

  bool Flag_Error = false;
  std::string Server_Address;
  std::string Server_Port;
  QTcpSocket* Server_Socket;
  std::vector<Command_Info> Vector_Command;

  void serverError(const std::string&, const std::string&);

private slots:
  void slotServerRead();
  void slotServerCommand(bool);
  void slotServerConnect();
  void slotServerDisconnect();
  void slotServerQuit();

signals:
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalServerCommand(bool);
  void signalServerComplete(bool);
  void signalServerIn(std::vector<char>);
};

#endif // OBJECTTCPSERVER_HPP
