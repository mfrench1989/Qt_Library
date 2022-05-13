#include <QCloseEvent>
#include <QSettings>

#include "function_interface.hpp"

#include "dialog_authorize.hpp"
#include "ui_dialog_authorize.h"

DialogAuthorize::DialogAuthorize(const std::string& text_in, const std::string& string_username,
                                 const std::string& string_password, QWidget* parent) : QDialog(parent), ui(new Ui::DialogAuthorize) {
  ui->setupUi(this);
  this->setModal(false);
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Authorize");

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();

  /*Format UI elements*/
  guiFormatWidget(*this, HUE_BASE, SAT_BASE, 5);
  guiFormatLabel(*ui->label_Message, HUE_BASE, SAT_GRAY, LUM_GRAY, false);
  guiFormatLineEdit(*ui->lineEdit_Password);
  guiFormatLineEdit(*ui->lineEdit_Username);
  guiFormatPushButton(*ui->pushButton_Accept, HUE_BLUE, SAT_COLOR);
  guiFormatPushButton(*ui->pushButton_Cancel, HUE_RED, SAT_COLOR);

  ui->label_Message->setText(QString::fromStdString(text_in));

  Username = string_username;
  Password = string_password;
}

DialogAuthorize::~DialogAuthorize() {
  /*Save position on close*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  overseer_settings.setValue("Position", saveGeometry());
  overseer_settings.endGroup();
  delete ui;
}

void DialogAuthorize::closeEvent(QCloseEvent *event_in) {
  event_in->ignore();
}

void DialogAuthorize::on_lineEdit_Password_returnPressed() {
  on_pushButton_Accept_clicked();
}

void DialogAuthorize::on_pushButton_Accept_clicked() {
  if (guiGetText(*ui->lineEdit_Username) != Username && guiGetText(*ui->lineEdit_Password) != Password) {
      ui->lineEdit_Password->clear();
      ui->lineEdit_Username->clear();
      ui->lineEdit_Username->setFocus();
      return;
    }
  accept();
  this->deleteLater();
}

void DialogAuthorize::on_pushButton_Cancel_clicked() {
  reject();
  this->deleteLater();
}
