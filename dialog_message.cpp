#include <QSettings>

#include "function_interface.hpp"

#include "dialog_message.hpp"
#include "ui_dialog_message.h"

DialogMessage::DialogMessage(const std::string& text_in, QWidget* parent) : QDialog(parent), ui(new Ui::DialogMessage) {
  ui->setupUi(this);
  this->setModal(false);
  if (parent) {
      this->setObjectName(this->parent()->objectName() + "Message");
    }
  else {
      this->setObjectName("Message");
    }

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();

  /*Format UI elements*/
  guiFormatWidget(*this, HUE_BASE, SAT_BASE, 5);
  guiFormatLabel(*ui->label_Message, HUE_BASE, SAT_GRAY, LUM_GRAY, false);

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
