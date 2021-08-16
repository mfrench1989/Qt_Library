#ifndef OBJECTCLIENT_HPP
#define OBJECTCLIENT_HPP

#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

class ObjectClient : public QTcpSocket {
  Q_OBJECT

public:
  explicit ObjectClient(const std::string&, const std::string&, QObject* = nullptr);

private:
#define WAIT_TIME 1000
  std::string Client_Address;
  std::string Client_Port;
  QTimer* Time_Out;

private slots:
  void slotClientConnect();
  void slotClientDisconnect();
  void slotClientQuit();
  void slotClientRead();
  void slotClientTimeout();
  void slotClientWrite();
  void slotSocketConnect();
  void slotSocketDisconnect();

signals:
  void signalClientBytesIn(std::vector<char>);
};

#endif // OBJECTCLIENT_HPP
