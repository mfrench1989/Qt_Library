#ifndef WINDOW_LOGIN_HPP
#define WINDOW_LOGIN_HPP

#include <QMainWindow>

#include "define_default.hpp"

namespace Ui {
  class WindowLogin;
}

class WindowLogin : public QMainWindow {
  Q_OBJECT

public:
  explicit WindowLogin(QWidget* = nullptr);
  ~WindowLogin();
  void initSignal(Data_Connect*);
  void initStyle();
  bool initConfig();

private:
  Ui::WindowLogin *ui;
  const std::string Admin_Name = "";
  const std::string Admin_Pass = "";
  const std::string User_Name = "";
  const std::string User_Pass = "";
  Mode_Login Flag_Login = Mode_Login::None;

  void closeEvent(QCloseEvent*);

private slots:
  void slotModeLogin(Mode_Login);
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_lineEdit_Password_returnPressed();
  void on_pushButton_Login_clicked();
  void on_pushButton_Logout_clicked();

signals:
  void signalEvent(Event_Type, std::string, std::string, std::string);
  void signalModeLogin(Mode_Login);
};

#endif // WINDOW_LOGIN_HPP
