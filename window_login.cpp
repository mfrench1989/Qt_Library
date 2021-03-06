#include <QSettings>

#include "CPPLibrary/function_string.hpp"
#include "function_gui.hpp"

#include "window_login.hpp"
#include "ui_window_login.h"

WindowLogin::WindowLogin(QWidget *parent) : QMainWindow(parent), ui(new Ui::WindowLogin) {
  ui->setupUi(this);
  this->setContextMenuPolicy(Qt::NoContextMenu);
  this->setObjectName("Window_Login");
  qRegisterMetaType<Mode_Login>("Mode_Login");

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Window");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();
}

WindowLogin::~WindowLogin() {
  /*Save position on close*/
  QSettings overseer_settings(qApp->objectName(), "Window");
  overseer_settings.beginGroup(this->objectName());
  overseer_settings.setValue("Position", saveGeometry());
  overseer_settings.endGroup();
  delete ui;
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
bool WindowLogin::initConfig(const QObject* object_event, const std::vector<QObject*> vector_object,
                             const std::string& string_username, const std::string& string_password) {
  /*Stylesheet*/
  guiFormatPushButton(*ui->pushButton_Logout, HUE_RED, SAT_COLOR);

  if (object_event) {
      QObject::connect(this, SIGNAL(signalEvent(Event_Type,std::string,std::string,std::string)),
                       object_event, SLOT(slotEvent(Event_Type,std::string,std::string,std::string)), Qt::QueuedConnection);
    }

  QObject::connect(this, SIGNAL(signalModeLogin(Mode_Login)), this, SLOT(slotMode_Login(Mode_Login)), Qt::QueuedConnection);
  for (const QObject* object_connect : vector_object) {
      QObject::connect(this, SIGNAL(signalModeLogin(Mode_Login)), object_connect, SLOT(slotMode_Login(Mode_Login)), Qt::QueuedConnection);
    }

  if (!string_username.empty() && !string_password.empty()) {
      ui->lineEdit_Username->setText(QString::fromStdString(string_username));
      ui->lineEdit_Password->setText(QString::fromStdString(string_password));
      on_pushButton_Login_clicked();
    }
  else {
      Q_EMIT signalModeLogin(Mode_Login::None);
    }

  Q_EMIT signalEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                     this->objectName().toStdString() + " configuration finished");
  return true;
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/
void WindowLogin::closeEvent(QCloseEvent*) {
  Q_EMIT signalModeLogin(Mode_Login::None);
}

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void WindowLogin::slotMode_Login(Mode_Login mode_in) {
  /*Issue updated login/logout message if Flag_Login is changing*/
  if (Flag_Login != mode_in) {
      Q_EMIT signalEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                         mode_in == Mode_Login::None ? std::string(Flag_Login == Mode_Login::Admin ? "Admin" : "User") + " Logout" :
                                                       std::string(mode_in == Mode_Login::Admin ? "Admin" : "User") + " Login");
    }

  Flag_Login = mode_in;
  ui->stackedWidget_Login->setCurrentIndex(Flag_Login != Mode_Login::None);

  /*Clear line edits and set focus to username input*/
  ui->lineEdit_Password->clear();
  ui->lineEdit_Username->clear();
  ui->lineEdit_Username->setFocus();

  /*Ensure window is displayed if logged in*/
  if (Flag_Login != Mode_Login::None) {
      this->show();
    }
}

/*================================================================*/
/*UI Slots*/
/*================================================================*/
void WindowLogin::on_lineEdit_Password_returnPressed() {
  on_pushButton_Login_clicked();
}

void WindowLogin::on_pushButton_Login_clicked() {
  /*Get user inputs*/
  std::string username = guiGetText(*ui->lineEdit_Username);
  std::string password = guiGetText(*ui->lineEdit_Password);

  /*Compare for login mode*/
  if (username == Admin_Name && password == Admin_Pass) {
      Q_EMIT signalModeLogin(Mode_Login::Admin);
    }
  else if (username == User_Name && password == User_Pass) {
      Q_EMIT signalModeLogin(Mode_Login::User);
    }
  else {
      Q_EMIT signalEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
                         "Incorrect username or password");
      Q_EMIT signalModeLogin(Mode_Login::None);
    }
}

void WindowLogin::on_pushButton_Logout_clicked() {
  Q_EMIT signalModeLogin(Mode_Login::None);
}
