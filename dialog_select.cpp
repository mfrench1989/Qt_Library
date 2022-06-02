#include <QCloseEvent>
#include <QSettings>

#include "function_gui.hpp"

#include "dialog_select.hpp"
#include "ui_dialog_select.h"

DialogSelect::DialogSelect(const std::vector<std::string>& vector_select, QWidget* parent) : QDialog(parent), ui(new Ui::DialogSelect) {
  ui->setupUi(this);
  this->setModal(false);
  this->setObjectName((parent ? this->parent()->objectName() + "_" : "") + "Select");

  /*Load position on creation*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  restoreGeometry(overseer_settings.value("Position").toByteArray());
  overseer_settings.endGroup();

  /*Format UI elements*/
  guiFormatWidget(*this, HUE_BASE, SAT_BASE, 5);
  guiFormatListWidget(*ui->listWidget_Select);
  guiFormatPushButton(*ui->pushButton_Cancel, HUE_RED, SAT_COLOR);
  guiFormatPushButton(*ui->pushButton_Select, HUE_BLUE, SAT_COLOR);

  for (const std::string& string_select : vector_select) {
      ui->listWidget_Select->addItem(QString::fromStdString(string_select));
    }
  ui->listWidget_Select->setCurrentRow(0);
}

DialogSelect::~DialogSelect() {
  /*Save position on close*/
  QSettings overseer_settings(qApp->objectName(), "Dialog");
  overseer_settings.beginGroup(this->objectName());
  overseer_settings.setValue("Position", saveGeometry());
  overseer_settings.endGroup();
  delete ui;
}

void DialogSelect::closeEvent(QCloseEvent *event_in) {
  event_in->ignore();
}

void DialogSelect::on_pushButton_Cancel_clicked() {
  this->deleteLater();
}

void DialogSelect::on_pushButton_Select_clicked() {
  if (ui->listWidget_Select->currentRow() >= 0) {
      Q_EMIT signalSelect(ui->listWidget_Select->currentItem()->text().toStdString());
      Q_EMIT signalSelect(ui->listWidget_Select->currentItem()->text());
      this->deleteLater();
    }
}
