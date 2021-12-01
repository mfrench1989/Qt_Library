#ifndef OBJECTFTPCLIENT_HPP
#define OBJECTFTPCLIENT_HPP

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

#include "define_default.hpp"

class ObjectFTPClient : public QNetworkAccessManager {
  Q_OBJECT

public:
  explicit ObjectFTPClient(const std::string&, const std::string&, const std::string&, QObject*);
  void clientAbort();
  void clientRead(const std::string&);
  void clientWrite(const std::string&, const std::vector<char>&);

private:
#define WAIT_CLIENT 500
  enum class Command_Type {
    Read,
    Write
  };
  struct Command_Info {
    Command_Type Type;
    std::string URL;
    std::vector<char> Bytes;
  };

  bool Flag_Error = false;
  std::string Client_Address;
  std::string Client_Password;
  std::string Client_Username;
  QNetworkReply* FTP_Reply;
  QTimer* Time_Out;
  std::vector<Command_Info> Vector_Command;

  void clientError(const std::string&, const std::string&);

private slots:
  void slotClientCommand(bool);
  void slotClientQuit();
  void slotClientTimeout();
  void slotFTPError(QNetworkReply::NetworkError);
  void slotFTPFinish();

signals:
  void signalClientCommand(bool);
  void signalClientComplete(bool);
  void signalClientIn(std::vector<char>);
  void signalEvent(Event_Type, std::string, std::string, std::string);
};

#endif // OBJECTFTPCLIENT_HPP
