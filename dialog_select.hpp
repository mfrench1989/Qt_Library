#ifndef DIALOG_SELECT_HPP
#define DIALOG_SELECT_HPP

/*--------------------------------*/
/* Class to display select popup  */
/* Remembers last saved position, */
/* unique for each parent object  */
/*--------------------------------*/

#include <QDialog>

namespace Ui {
  class DialogSelect;
}

class DialogSelect : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief DialogSelect - create and display select popup
   * @param vector<string> - vector of selection options
   */
  explicit DialogSelect(const std::vector<std::string>&, QWidget* = nullptr);
  ~DialogSelect();

private:
  Ui::DialogSelect *ui;

  /**
   * @brief closeEvent - overwrite close event so cancel or select button has to be pressed
   */
  void closeEvent(QCloseEvent*);

private slots:
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_pushButton_Cancel_clicked();
  void on_pushButton_Select_clicked();

signals:
  void signalSelect(std::string);
  void signalSelect(QString);
};

#endif // DIALOG_SELECT_HPP
