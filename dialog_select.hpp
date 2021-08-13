#ifndef DIALOG_SELECT_HPP
#define DIALOG_SELECT_HPP

#include <QDialog>

namespace Ui {
  class DialogSelect;
}

class DialogSelect : public QDialog {
  Q_OBJECT

public:
  explicit DialogSelect(const std::vector<std::string>&, QWidget* = nullptr);
  ~DialogSelect();

private:
  Ui::DialogSelect *ui;

  void closeEvent(QCloseEvent *close_event);

private slots:
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_pushButton_Cancel_clicked();
  void on_pushButton_Select_clicked();
};

#endif // DIALOG_SELECT_HPP
