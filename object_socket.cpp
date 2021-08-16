#include <QCoreApplication>

#include "CPPLibrary/function_string.hpp"

#include "object_socket.hpp"

ObjectSocket::ObjectSocket(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpSocket(parent) {
  this->setObjectName("Socket" + (parent ? this->parent()->objectName() : ""));
  qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");

  Socket_Address = address_in;
  Socket_Port = port_in;

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotSocketQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slotSocketBytesIn()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);

  QObject::connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                   this, SLOT(slotSocketChangeState(QAbstractSocket::SocketState)), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(slotSocketBytesOut(qint64)), Qt::QueuedConnection);
  QObject::connect(this, SIGNAL(signalCommand(bool)), this, SLOT(slotSocketCommand(bool)), Qt::QueuedConnection);
  QObject::connect(Time_Out, SIGNAL(timeout()), this, SLOT(slotSocketTimeout()), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectSocket::socketConnect() {
  /*If function is called assume force connect and clear Vector_Command*/
  Vector_Command.clear();
  Vector_Command.push_back({Command_Type::Connect, std::vector<char>()});
  Q_EMIT signalCommand(false);
}

void ObjectSocket::socketDisconnect() {
  /*If function is called assume force disconnect and clear Vector_Command*/
  Vector_Command.clear();
  Vector_Command.push_back({Command_Type::Disconnect, std::vector<char>()});
  Q_EMIT signalCommand(false);
}

void ObjectSocket::socketWrite(std::vector<char> bytes_out) {
  bool flag_empty = Vector_Command.empty();
  Vector_Command.push_back({Command_Type::Connect, std::vector<char>()});
  Vector_Command.push_back({Command_Type::Write, bytes_out});
  if (flag_empty) {
      Q_EMIT signalCommand(false);
    }
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void ObjectSocket::socketError(const std::string& function_in, const std::string& error_in) {
  Flag_Error = true;
  Vector_Command.clear();
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectSocket::slotSocketBytesIn() {
  QByteArray bytes_in = this->readAll();
  Q_EMIT signalSocketIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}

void ObjectSocket::slotSocketBytesOut(qint64 bytes_written) {
  if (!Vector_Command.empty() && Vector_Command.front().Type == Command_Type::Write &&
      static_cast<int>(bytes_written) == static_cast<int>(Vector_Command.front().Data.size())) {
      Q_EMIT signalCommand(true);
    }
}

void ObjectSocket::slotSocketChangeState(QAbstractSocket::SocketState state_in) {
  switch (state_in) {
    case QAbstractSocket::UnconnectedState: {
        if (Vector_Command.empty()) {
            Q_EMIT signalEvent(Event_Type::Warning, this->objectName().toStdString(), stringFuncInfo(this, __func__), "Server disconnected");
          }
        else if (Vector_Command.front().Type == Command_Type::Disconnect) {
            Time_Out->stop();
            Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(), stringFuncInfo(this, __func__), "Client disconnected");
            Q_EMIT signalCommand(true);
          }
        else if (Vector_Command.front().Type == Command_Type::Connect) {
            /*Do Nothing*/
          }
        else {
            socketError(stringFuncInfo(this, __func__), "Server disconnected");
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
            Q_EMIT signalEvent(Event_Type::Debug, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                               "Client connected - " + Socket_Address + ":" + Socket_Port);
            Q_EMIT signalCommand(true);
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

void ObjectSocket::slotSocketCommand(bool flag_erase) {
  if (!Vector_Command.empty() && flag_erase) {
      Vector_Command.erase(Vector_Command.begin());
    }
  if (Vector_Command.empty()) {
      Q_EMIT signalSocketComplete(!Flag_Error);
      Flag_Error = false;
      return;
    }

  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        if (this->state() != QAbstractSocket::UnconnectedState && this->state() != QAbstractSocket::ClosingState) {
            this->disconnectFromHost();
          }
        else {
            Q_EMIT signalCommand(true);
          }
        break;
      }
    case Command_Type::Connect: {
        if (this->state() != QAbstractSocket::HostLookupState &&
            this->state() != QAbstractSocket::ConnectingState &&
            this->state() != QAbstractSocket::ConnectedState) {
            this->connectToHost(QHostAddress(QString::fromStdString(Socket_Address)), quint16(stringToNum(Socket_Port)));
          }
        else {
            Q_EMIT signalCommand(true);
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

void ObjectSocket::slotSocketQuit() {
  Vector_Command.clear();
  this->disconnectFromHost();
}

void ObjectSocket::slotSocketTimeout() {
  switch (Vector_Command.front().Type) {
    case Command_Type::Disconnect: {
        socketError(stringFuncInfo(this, __func__), "Client disconnect timeout - forcing disconnect");
        this->setSocketState(QAbstractSocket::UnconnectedState);
        break;
      }
    case Command_Type::Connect: {
        socketError(stringFuncInfo(this, __func__), "Client connect timeout - " + Socket_Address + ":" + Socket_Port);
        break;
      }
    case Command_Type::Write: {
        socketError(stringFuncInfo(this, __func__), "Client write timeout");
        break;
      }
    }
  Vector_Command.clear();
}
