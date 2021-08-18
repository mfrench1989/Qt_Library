#include <QCoreApplication>

#include "CPPLibrary/function_string.hpp"

#include "object_server.hpp"

ObjectServer::ObjectServer(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpServer(parent) {
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Server");

  Server_Address = address_in;
  Server_Port = port_in;

  Server_Socket = new QTcpSocket(this);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotServerQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(newConnection()), this, SLOT(slotServerConnect()), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);

  QObject::connect(this, SIGNAL(signalCommand(bool)), this, SLOT(slotServerCommand(bool)), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectServer::serverWrite(const std::vector<char>& bytes_out) {
  bool flag_empty = Vector_Command.empty();
  Vector_Command.push_back({Command_Type::Write, bytes_out});
  if (flag_empty) {
      Q_EMIT signalCommand(false);
    }
}

bool ObjectServer::serverListen() {
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
void ObjectServer::serverError(const std::string& function_in, const std::string& error_in) {
  Flag_Error = true;
  Vector_Command.clear();
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectServer::slotServerCommand(bool flag_erase) {
  if (!Vector_Command.empty() && flag_erase) {
      Vector_Command.erase(Vector_Command.begin());
    }
  if (Vector_Command.empty()) {
      Q_EMIT signalServerComplete(!Flag_Error);
      Flag_Error = false;
      return;
    }

  switch (Vector_Command.front().Type) {
    case Command_Type::Write: {
        /*Check connection before writing*/
        if (Server_Socket->state() == QAbstractSocket::ConnectedState ||
            Server_Socket->state() == QAbstractSocket::ConnectingState ||
            Server_Socket->state() == QAbstractSocket::HostLookupState) {
            char bytes_out[Vector_Command.front().Data.size()];
            std::copy(Vector_Command.front().Data.begin(), Vector_Command.front().Data.end(), bytes_out);
            Server_Socket->write(bytes_out, sizeof(bytes_out));
            Server_Socket->flush();
            Q_EMIT signalCommand(true);
          }
        else {
            serverError(stringFuncInfo(this, __func__), "Socket cannot write - not connected");
          }
        break;
      }
    }
}

void ObjectServer::slotServerConnect() {
  Server_Socket->close();
  Server_Socket = this->nextPendingConnection();
  QObject::connect(Server_Socket, SIGNAL(readyRead()), this, SLOT(slotServerRead()), Qt::DirectConnection);
  QObject::connect(Server_Socket, SIGNAL(disconnected()), this, SLOT(slotServerDisconnect()), Qt::QueuedConnection);
  slotServerRead();
}

void ObjectServer::slotServerDisconnect() {
  Server_Socket->close();
}

void ObjectServer::slotServerQuit() {
  Server_Socket->close();
  this->close();
}

void ObjectServer::slotServerRead() {
  if (!Server_Socket->bytesAvailable()) {
      return;
    }
  QByteArray bytes_in = Server_Socket->readAll();
  Q_EMIT signalServerIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}
