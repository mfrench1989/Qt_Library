#include <QCoreApplication>

#include "CPPLibrary/function_string.hpp"

#include "object_tcp_server.hpp"

ObjectTCPServer::ObjectTCPServer(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpServer(parent) {
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Server");

  Server_Address = address_in;
  Server_Port = port_in;

  Server_Socket = new QTcpSocket(this);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotServerQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(newConnection()), this, SLOT(slotServerConnect()), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(signalServerCommand(bool)), this, SLOT(slotServerCommand(bool)), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectTCPServer::serverWrite(const std::vector<char>& bytes_out) {
  bool flag_empty = List_Command.empty();
  List_Command.push_back({Command_Type::Write, bytes_out});
  if (flag_empty) {
      Q_EMIT signalServerCommand(false);
    }
}

bool ObjectTCPServer::serverListen() {
  QHostAddress server_address = Server_Address.empty() ? QHostAddress::Any : QHostAddress(QString::fromStdString(Server_Address));
  if (this->listen(server_address, quint16(stringToNum(Server_Port)))) {
      Q_EMIT signalEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                         "Server listening - " + Server_Address + ":" + Server_Port);
      return true;
    }
  else {
      Q_EMIT signalEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                         "Server failed listening - " + Server_Address + ":" + Server_Port);
      return false;
    }
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void ObjectTCPServer::serverError(const std::string& function_in, const std::string& error_in) {
  Flag_Error = true;
  List_Command.clear();
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalServerCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectTCPServer::slotServerCommand(bool flag_erase) {
  if (!List_Command.empty() && flag_erase) {
      List_Command.pop_front();
    }
  if (List_Command.empty()) {
      Q_EMIT signalServerComplete(!Flag_Error);
      Flag_Error = false;
      return;
    }

  switch (List_Command.front().Type) {
    case Command_Type::Write: {
        /*Check connection before writing*/
        if (Server_Socket->state() == QAbstractSocket::ConnectedState ||
            Server_Socket->state() == QAbstractSocket::ConnectingState ||
            Server_Socket->state() == QAbstractSocket::HostLookupState) {
            char bytes_out[List_Command.front().Bytes.size()];
            std::copy(List_Command.front().Bytes.begin(), List_Command.front().Bytes.end(), bytes_out);
            Server_Socket->write(bytes_out, sizeof(bytes_out));
            Server_Socket->flush();
            Q_EMIT signalServerCommand(true);
          }
        else {
            serverError(stringFuncInfo(this, __func__), "Socket cannot write - not connected");
          }
        break;
      }
    }
}

void ObjectTCPServer::slotServerConnect() {
  Server_Socket->close();
  Server_Socket = this->nextPendingConnection();
  QObject::connect(Server_Socket, SIGNAL(readyRead()), this, SLOT(slotServerRead()), Qt::DirectConnection);
  QObject::connect(Server_Socket, SIGNAL(disconnected()), this, SLOT(slotServerDisconnect()), Qt::QueuedConnection);
  slotServerRead();
}

void ObjectTCPServer::slotServerDisconnect() {
  Server_Socket->close();
}

void ObjectTCPServer::slotServerQuit() {
  Server_Socket->close();
  this->close();
}

void ObjectTCPServer::slotServerRead() {
  if (!Server_Socket->bytesAvailable()) {
      return;
    }
  QByteArray bytes_in = Server_Socket->readAll();
  Q_EMIT signalServerIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}
