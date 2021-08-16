#include <QApplication>

#include "CPPLibrary/function_string.hpp"

#include "object_client.hpp"

ObjectClient::ObjectClient(const std::string& address_in, const std::string& port_in, QObject *parent) : QTcpSocket(parent) {
  if (parent) {
      this->setObjectName(this->parent()->objectName() + "Client");
    }
  else {
      this->setObjectName("Client");
    }

  Client_Address = address_in;
  Client_Port = port_in;

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotClientQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slotClientRead()), Qt::DirectConnection);

  QObject::connect(this, SIGNAL(connected()), this, SLOT(slotSocketConnect()), Qt::QueuedConnection);
  QObject::connect(Time_Out, SIGNAL(timeout()), this, SLOT(slotClientTimeout()), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/

/*================================================================*/
/*Private Methods*/
/*================================================================*/

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectClient::slotClientConnect() {
  Time_Out->start(WAIT_TIME);
  this->connectToHost(QHostAddress(QString::fromStdString(Client_Address)), quint16(stringToNum(Client_Port)));
}

void ObjectClient::slotClientDisconnect() {
  Time_Out->start(WAIT_TIME);
  this->disconnectFromHost();
}

void ObjectClient::slotClientQuit() {
  QObject::disconnect(this, SIGNAL(disconnected()), this, SLOT(slotSocketDisconnect()));
  this->disconnectFromHost();
}

void ObjectClient::slotClientRead() {
  QByteArray bytes_in = this->readAll();
  Q_EMIT signalClientBytesIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
}

void ObjectClient::slotClientTimeout() {
  qDebug() << this->state();
  switch (this->state()) {
    case QAbstractSocket::UnconnectedState: {
        break;
      }
    case QAbstractSocket::ConnectingState: {
        break;
      }
    case QAbstractSocket::ConnectedState: {
        break;
      }
    case QAbstractSocket::ClosingState: {
        break;
      }
    default: {
        break;
      }
    }
}

void ObjectClient::slotClientWrite() {
}

void ObjectClient::slotSocketConnect() {
  Time_Out->stop();
  QObject::connect(this, SIGNAL(disconnected()), this, SLOT(slotSocketDisconnect()), Qt::QueuedConnection);
}

void ObjectClient::slotSocketDisconnect() {
  Time_Out->stop();
  QObject::disconnect(this, SIGNAL(disconnected()), this, SLOT(slotSocketDisconnect()));
}
