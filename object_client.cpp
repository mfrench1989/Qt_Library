#include <QApplication>

#include "CPPLibrary/function_string.hpp"

#include "object_client.hpp"

ObjectClient::ObjectClient(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpSocket(parent) {
  this->setObjectName("Client" + (parent ? this->parent()->objectName() : ""));
  qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");

  Client_Address = address_in;
  Client_Port = port_in;

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotClientQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slotSocketRead()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);

  QObject::connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                   this, SLOT(slotSocketState(QAbstractSocket::SocketState)), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(slotSocketWrite(qint64)), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(signalClientCommand(bool)), this, SLOT(slotClientCommand(bool)), Qt::QueuedConnection);
  QObject::connect(Time_Out, SIGNAL(timeout()), this, SLOT(slotClientTimeout()), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectClient::clientConnect() {
  /*If function is called assume force connect and clear Vector_Command*/
  Vector_Command.clear();
  Vector_Command.push_back({Command_Type::Connect, std::vector<char>()});
  Q_EMIT signalClientCommand(false);
}

void ObjectClient::clientDisconnect() {
  /*If function is called assume force disconnect and clear Vector_Command*/
  Vector_Command.clear();
  Vector_Command.push_back({Command_Type::Disconnect, std::vector<char>()});
  Q_EMIT signalClientCommand(false);
}

void ObjectClient::clientWrite(std::vector<char> bytes_out) {
  bool flag_empty = Vector_Command.empty();
  Vector_Command.push_back({Command_Type::Connect, std::vector<char>()});
  Vector_Command.push_back({Command_Type::Write, bytes_out});
  if (flag_empty) {
      Q_EMIT signalClientCommand(false);
    }
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void ObjectClient::clientError(const std::string& function_in, const std::string& error_in) {
  Flag_Error = true;
  Vector_Command.clear();
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalClientCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectClient::slotClientCommand(bool erase_in) {
  if (!Vector_Command.empty() && erase_in) {
      Vector_Command.erase(Vector_Command.begin());
    }
  if (Vector_Command.empty()) {
      Q_EMIT signalClientStatus(!Flag_Error);
      Flag_Error = false;
      return;
    }

  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        if (this->state() != QAbstractSocket::UnconnectedState && this->state() != QAbstractSocket::ClosingState) {
            this->disconnectFromHost();
          }
        else {
            Q_EMIT signalClientCommand(true);
          }
        break;
      }
    case Command_Type::Connect: {
        if (this->state() != QAbstractSocket::HostLookupState &&
            this->state() != QAbstractSocket::ConnectingState &&
            this->state() != QAbstractSocket::ConnectedState) {
            this->connectToHost(QHostAddress(QString::fromStdString(Client_Address)), quint16(stringToNum(Client_Port)));
          }
        else {
            Q_EMIT signalClientCommand(true);
          }
        break;
      }
    case Command_Type::Write: {
        char bytes_out[Vector_Command.front().Data.size()];
        std::copy(Vector_Command.front().Data.begin(), Vector_Command.front().Data.end(), bytes_out);
        this->write(bytes_out, sizeof(bytes_out));
        this->flush();
        break;
      }
    }
}

void ObjectClient::slotClientQuit() {
  Vector_Command.clear();
  this->disconnectFromHost();
}

void ObjectClient::slotClientTimeout() {
  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(),
                           stringFuncInfo(this, __func__), "Client disconnect timeout - forcing disconnect");
        this->setSocketState(QAbstractSocket::UnconnectedState);
        break;
      }
    case Command_Type::Connect: {
        Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(),
                           stringFuncInfo(this, __func__), "Client connect timeout - " + Client_Address + ":" + Client_Port);
        break;
      }
    case Command_Type::Write: {
        Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(),
                           stringFuncInfo(this, __func__), "Client write timeout");
        break;
      }
    }
  Vector_Command.clear();
}

void ObjectClient::slotSocketRead() {
  QByteArray bytes_in = this->readAll();
  Q_EMIT signalClientBytesIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}

void ObjectClient::slotSocketState(QAbstractSocket::SocketState state_in) {
  switch (state_in) {
    case QAbstractSocket::UnconnectedState: {
        if (Vector_Command.empty()) {
            Q_EMIT signalEvent(Event_Type::Warning, this->objectName().toStdString(),
                               stringFuncInfo(this, __func__), "Server disconnected");
          }
        else if (Vector_Command.front().Type == Command_Type::Disconnect) {
            Time_Out->stop();
            Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(),
                               stringFuncInfo(this, __func__), "Client disconnected");
            Q_EMIT signalClientCommand(true);
          }
        else if (Vector_Command.front().Type == Command_Type::Connect) {
            /*Do Nothing*/
          }
        else {
            Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(),
                               stringFuncInfo(this, __func__), "Server disconnected");
          }
        break;
      }
    case QAbstractSocket::ConnectingState: {
        if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Connect) {
            Time_Out->start(WAIT_TIME);
          }
        break;
      }
    case QAbstractSocket::ConnectedState: {
        if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Connect) {
            Time_Out->stop();
            Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(),
                               stringFuncInfo(this, __func__), "Client connected");
            Q_EMIT signalClientCommand(true);
          }
        break;
      }
    case QAbstractSocket::ClosingState: {
        if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Disconnect) {
            Time_Out->start(WAIT_TIME);
          }
        break;
      }
    default: {
        break;
      }
    }
}

void ObjectClient::slotSocketWrite(qint64 bytes_written) {
  if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Write &&
      static_cast<int>(bytes_written) == static_cast<int>(Vector_Command.front().Data.size())) {
      Q_EMIT signalClientCommand(true);
    }
}
