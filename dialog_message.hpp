#ifndef DIALOG_MESSAGE_HPP
#define DIALOG_MESSAGE_HPP

#include <QDialog>

namespace Ui {
  class DialogMessage;
}

class DialogMessage : public QDialog {
  Q_OBJECT

public:
  explicit DialogMessage(const std::string&, QWidget* = nullptr);
  ~DialogMessage();

private:
  Ui::DialogMessage *ui;
};

#endif // DIALOG_MESSAGE_HPP
