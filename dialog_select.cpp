#include "dialog_select.hpp"
#include "ui_dialog_select.h"

DialogSelect::DialogSelect(const std::vector<std::string>& vector_select, QWidget* parent) : QDialog(parent), ui(new Ui::DialogSelect) {
  ui->setupUi(this);
}

DialogSelect::~DialogSelect()
{
  delete ui;
}
