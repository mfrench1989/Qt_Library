#include <QCoreApplication>
#include <QHostAddress>

#include "CPPLibrary/function_string.hpp"

#include "object_tcp_client.hpp"

ObjectTCPClient::ObjectTCPClient(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpSocket(parent) {
  this->setObjectName(this->parent()->objectName() + "_TCPClient");

  Client_Address = address_in;
  Client_Port = port_in;

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotClientQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(connected()), this, SLOT(slotClientConnect()), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(disconnected()), this, SLOT(slotClientDisconnect()), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slotClientRead()), Qt::DirectConnection);
  QObject::connect(Time_Out, SIGNAL(timeout()), this, SLOT(slotClientTimeout()), Qt::QueuedConnection);

  /*signalClientIn*/
  QObject::connect(this, SIGNAL(signalClientIn(std::vector<char>)),
                   parent, SLOT(slotClientIn(std::vector<char>)), Qt::QueuedConnection);

  /*signalClientCommand*/
  QObject::connect(this, SIGNAL(signalClientCommand(bool)), this, SLOT(slotClientCommand(bool)), Qt::QueuedConnection);

  /*signalClientComplete*/
  QObject::connect(this, SIGNAL(signalClientComplete(bool)),
                   parent, SLOT(slotClientComplete(bool)), Qt::QueuedConnection);

  /*signalEvent*/
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);

}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectTCPClient::clientConnect() {
  /*If function is called assume force connect and clear Vector_Command*/
  clearCommand();
  Vector_Command.push_back({Command_Type::Connect, std::vector<char>()});
  Q_EMIT signalClientCommand(false);
}

void ObjectTCPClient::clientDisconnect() {
  /*If function is called assume force disconnect and clear Vector_Command*/
  clearCommand();
  Vector_Command.push_back({Command_Type::Disconnect, std::vector<char>()});
  Q_EMIT signalClientCommand(false);
}

void ObjectTCPClient::clientWrite(const std::vector<char>& bytes_out) {
  bool flag_empty = Vector_Command.empty();
  Vector_Command.push_back({Command_Type::Write, bytes_out});
  if (flag_empty) {
      Q_EMIT signalClientCommand(false);
    }
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void ObjectTCPClient::clearCommand() {
  Time_Out->stop();
  Vector_Command.clear();
}

void ObjectTCPClient::clientError(const std::string& function_in, const std::string& error_in) {
  clearCommand();
  Flag_Error = true;
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalClientCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectTCPClient::slotClientCommand(bool flag_erase) {
  if (!Vector_Command.empty() && flag_erase) {
      Vector_Command.erase(Vector_Command.begin());
    }
  if (Vector_Command.empty()) {
      Q_EMIT signalClientComplete(!Flag_Error);
      Flag_Error = false;
      return;
    }

  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        /*Dont disconnect if already disconnect(ed/ing)*/
        if (this->state() == QAbstractSocket::UnconnectedState || this->state() == QAbstractSocket::ClosingState) {
            Q_EMIT signalClientCommand(true);
          }
        else {
            Time_Out->start(WAIT_CLIENT);
            this->disconnectFromHost();
          }
        break;
      }
    case Command_Type::Connect: {
        /*Dont connect if already connect(ed/ing)*/
        if (this->state() == QAbstractSocket::ConnectedState ||
            this->state() == QAbstractSocket::ConnectingState ||
            this->state() == QAbstractSocket::HostLookupState) {
            Q_EMIT signalClientCommand(true);
          }
        else {
            Time_Out->start(WAIT_CLIENT);
            this->connectToHost(QHostAddress(QString::fromStdString(Client_Address)), quint16(stringToNum(Client_Port)));
          }
        break;
      }
    case Command_Type::Write: {
        /*Check connection before writing & connect if needed*/
        if (this->state() == QAbstractSocket::ConnectedState ||
            this->state() == QAbstractSocket::ConnectingState ||
            this->state() == QAbstractSocket::HostLookupState) {
            char bytes_out[Vector_Command.front().Bytes.size()];
            std::copy(Vector_Command.front().Bytes.begin(), Vector_Command.front().Bytes.end(), bytes_out);
            this->write(bytes_out, sizeof(bytes_out));
            this->flush();
            Q_EMIT signalClientCommand(true);
          }
        else {
            Vector_Command.insert(Vector_Command.begin(), {Command_Type::Connect, std::vector<char>()});
            Q_EMIT signalClientCommand(false);
          }
        break;
      }
    }
}

void ObjectTCPClient::slotClientConnect() {
  if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Connect) {
      Time_Out->stop();
      Q_EMIT signalClientCommand(true);
    }
}

void ObjectTCPClient::slotClientDisconnect() {
  /*Emit warning for display if server disconnected from client*/
  if (Vector_Command.empty()) {
      Q_EMIT signalEvent(Event_Type::Warning, this->objectName().toStdString(), stringFuncInfo(this, __func__), "Server disconnected");
    }
  else if (Vector_Command.front().Type == Command_Type::Disconnect) {
      Time_Out->stop();
      Q_EMIT signalClientCommand(true);
    }
  else {
      clientError(stringFuncInfo(this, __func__), "Server disconnected");
    }
}

void ObjectTCPClient::slotClientQuit() {
  clearCommand();
  this->disconnectFromHost();
}

void ObjectTCPClient::slotClientRead() {
  QByteArray bytes_in = this->readAll();
  Q_EMIT signalClientIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}

void ObjectTCPClient::slotClientTimeout() {
  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        clientError(stringFuncInfo(this, __func__), "Client disconnect timeout - forcing disconnect");
        this->setSocketState(QAbstractSocket::UnconnectedState);
        break;
      }
    case Command_Type::Connect: {
        clientError(stringFuncInfo(this, __func__), "Client connect timeout - " + Client_Address + ":" + Client_Port);
        clientDisconnect();
        break;
      }
    case Command_Type::Write: {
        clientError(stringFuncInfo(this, __func__), "Client write timeout");
        break;
      }
    }
}
