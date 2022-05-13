#ifndef DIALOG_OPTION_HPP
#define DIALOG_OPTION_HPP

/*--------------------------------*/
/* Class to display option popup  */
/* Remembers last saved position, */
/* unique for each parent object  */
/*--------------------------------*/

#include <QDialog>

namespace Ui {
  class DialogOption;
}

class DialogOption : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief DialogOption - create and display option popup
   * @param string - message text to display
   * @param string - text for accept button
   * @param int - hue for accept button
   * @param string - text for reject button
   * @param int - hue for reject button
   */
  explicit DialogOption(const std::string&, const std::string&, const int, const std::string&, const int, QWidget* = nullptr);
  ~DialogOption();

private:
  Ui::DialogOption *ui;

  /**
   * @brief closeEvent - overwrite close event so accept or reject button has to be pressed
   */
  void closeEvent(QCloseEvent*);
  void keyReleaseEvent(QKeyEvent*);

private slots:
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_pushButton_Accept_clicked();
  void on_pushButton_Reject_clicked();
};

#endif // DIALOG_OPTION_HPP
