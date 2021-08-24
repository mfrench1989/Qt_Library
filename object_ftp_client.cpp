#include <QCoreApplication>
#include <QHostAddress>

#include "CPPLibrary/function_string.hpp"

#include "object_ftp_client.hpp"

ObjectFTPClient::ObjectFTPClient(const std::string& address_in, const std::string& username_in,
                                 const std::string& password_in, QObject* parent) : QNetworkAccessManager(parent) {
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "FTPClient");

  Client_Address = address_in;
  Client_Username = username_in;
  Client_Password = password_in;

  Time_Out = new QTimer(this);
  Time_Out->setSingleShot(true);

  QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(slotClientQuit()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                   parent, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)), Qt::DirectConnection);

  QObject::connect(this, SIGNAL(signalCommand(bool)), this, SLOT(slotClientCommand(bool)), Qt::QueuedConnection);
  QObject::connect(Time_Out, SIGNAL(timeout()), this, SLOT(slotClientTimeout()), Qt::QueuedConnection);
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectFTPClient::clientWrite(const std::string& file_path, const std::vector<char>& bytes_out) {
  bool flag_empty = Vector_Command.empty();
  Vector_Command.push_back({Command_Type::Write, "ftp://" + Client_Address + "/" + file_path, bytes_out});
  if (flag_empty) {
      Q_EMIT signalClientCommand(false);
    }
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void ObjectFTPClient::clientError(const std::string& function_in, const std::string& error_in) {
  Flag_Error = true;
  Vector_Command.clear();
  Q_EMIT signalEvent(Event_Type::Error, this->objectName().toStdString(), function_in, error_in);
  Q_EMIT signalClientCommand(false);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectFTPClient::slotClientCommand(bool flag_erase) {
  if (!Vector_Command.empty() && flag_erase) {
      Vector_Command.erase(Vector_Command.begin());
    }
  if (Vector_Command.empty()) {
      Q_EMIT signalClientComplete(!Flag_Error);
      Flag_Error = false;
      return;
    }

  /*Format QUrl*/
  QUrl request(QString::fromStdString(Vector_Command.front().URL));
  request.setUserName(QString::fromStdString(Client_Username));
  request.setPassword(QString::fromStdString(Client_Password));

  /*Start Time_Out and issue get/put command*/
  Time_Out->start(WAIT_TIME);
  switch (Vector_Command.front().Type) {
    case Command_Type::Read: {
        FTP_Reply = this->get(QNetworkRequest(request));
        break;
      }
    case Command_Type::Write: {
        FTP_Reply = this->put(QNetworkRequest(request), QByteArray(Vector_Command.front().Bytes.data()));
        break;
      }
    }

  /*Connect signals for reply*/
  QObject::connect(FTP_Reply, SIGNAL(finished()), this, SLOT(slotFTPFinish()), Qt::DirectConnection);
  QObject::connect(FTP_Reply, SIGNAL(error(QNetworkReply::NetworkError)),
                   this, SLOT(slotFTPError(QNetworkReply::NetworkError)), Qt::QueuedConnection);
}

void ObjectFTPClient::slotFTPError(QNetworkReply::NetworkError error_in) {
  clientError(stringFuncInfo(this, __func__), "FTP error code " + std::to_string(static_cast<int>(error_in)));
}

void ObjectFTPClient::slotFTPFinish() {
  Time_Out->stop();
  switch (FTP_Reply->operation()) {
    case QNetworkAccessManager::GetOperation: {
        QByteArray bytes_in = FTP_Reply->readAll();
        Q_EMIT signalClientIn(std::vector<char>(bytes_in.begin(), bytes_in.end()));
        Q_EMIT signalClientCommand(true);
        break;
      }
    case QNetworkAccessManager::PutOperation: {
        Q_EMIT signalClientCommand(true);
        break;
      }
    default: {
        clientError(stringFuncInfo(this, __func__),
                    "FTP unhandled reply operation " + std::to_string(static_cast<int>(FTP_Reply->operation())));
        break;
      }
    }
}
