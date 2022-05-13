#include <QCloseEvent>
#include <QSettings>

#include "function_interface.hpp"

#include "dialog_option.hpp"
#include "ui_dialog_option.h"

DialogOption::DialogOption(const std::string& text_in, const std::string& string_accept, const int hue_accept,
                           const std::string& string_reject, const int hue_reject, QWidget* parent) : QDialog(parent), ui(new Ui::DialogOption) {
  ui->setupUi(this);
  this->setModal(false);
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Option");

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();

  /*Format UI elements*/
  guiFormatWidget(*this, HUE_BASE, SAT_BASE, 5);
  guiFormatLabel(*ui->label_Message, HUE_BASE, SAT_GRAY, LUM_GRAY, false);
  guiFormatPushButton(*ui->pushButton_Accept, hue_accept, SAT_COLOR);
  guiFormatPushButton(*ui->pushButton_Reject, hue_reject, SAT_COLOR);

  ui->label_Message->setText(QString::fromStdString(text_in));
  if (!string_accept.empty()) {
      ui->pushButton_Accept->setText(QString::fromStdString(string_accept));
    }
  if (!string_reject.empty()) {
      ui->pushButton_Reject->setText(QString::fromStdString(string_reject));
    }
}

DialogOption::~DialogOption() {
  /*Save position on close*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  overseer_settings.setValue("Position", saveGeometry());
  overseer_settings.endGroup();
  delete ui;
}

void DialogOption::closeEvent(QCloseEvent *event_in) {
  event_in->ignore();
}

void DialogOption::keyReleaseEvent(QKeyEvent* event_in) {
  /*Filter if button is not enabled to prevent spam*/
  if (!ui->pushButton_Accept->isEnabled()) {
      return;
    }

  if (event_in->key() == Qt::Key_Space && event_in->modifiers() ==(Qt::ShiftModifier|Qt::ControlModifier)) {
      ui->pushButton_Accept->setEnabled(false);
      on_pushButton_Accept_clicked();
    }
}

void DialogOption::on_pushButton_Accept_clicked() {
  accept();
  this->deleteLater();
}

void DialogOption::on_pushButton_Reject_clicked() {
  reject();
  this->deleteLater();
}
