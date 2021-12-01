#include <QCloseEvent>
#include <QSettings>

#include "function_interface.hpp"

#include "dialog_message.hpp"
#include "ui_dialog_message.h"

DialogMessage::DialogMessage(const std::string& text_in, QWidget* parent) : QDialog(parent), ui(new Ui::DialogMessage) {
  ui->setupUi(this);
  this->setModal(false);
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Message");

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();

  /*Format UI elements*/
  guiFormatWidget(*this, HUE_BASE, SAT_BASE, 5);
  guiFormatLabel(*ui->label_Message, HUE_BASE, SAT_GRAY, LUM_GRAY, false);
  guiFormatPushButton(*ui->pushButton_Close, HUE_BLUE, SAT_COLOR);

  ui->label_Message->setText(QString::fromStdString(text_in));
}

DialogMessage::~DialogMessage() {
  /*Save position on close*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  overseer_settings.setValue("Position", saveGeometry());
  overseer_settings.endGroup();
  delete ui;
}

void DialogMessage::closeEvent(QCloseEvent *event_in) {
  event_in->ignore();
}

void DialogMessage::on_pushButton_Close_clicked() {
  reject();
  this->deleteLater();
}

