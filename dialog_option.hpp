#ifndef DIALOG_OPTION_HPP
#define DIALOG_OPTION_HPP

#include <QDialog>

namespace Ui {
  class DialogOption;
}

class DialogOption : public QDialog {
  Q_OBJECT

public:
  explicit DialogOption(const std::string&, const std::string&, const int, const std::string&, const int, QWidget* = nullptr);
  ~DialogOption();

private:
  Ui::DialogOption *ui;

  void closeEvent(QCloseEvent *close_event);

private slots:
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_pushButton_Accept_clicked();
  void on_pushButton_Reject_clicked();
};

#endif // DIALOG_OPTION_HPP
