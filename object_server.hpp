#ifndef OBJECTSERVER_HPP
#define OBJECTSERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

#include "define_default.hpp"

class ObjectServer : public QTcpServer {
  Q_OBJECT

public:
  explicit ObjectServer(const std::string&, const std::string&, QObject*);
  bool serverListen();

private:
  enum class Command_Type {
    Write
  };
  struct Command_Info {
    Command_Type Type;
    std::vector<char> Data;
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
  void slotServerWrite(std::vector<char>);

signals:
  void signalCommand(bool);
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalServerComplete(bool);
  void signalServerIn(std::vector<char>);
};

#endif // OBJECTSERVER_HPP
