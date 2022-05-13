#ifndef DIALOG_AUTHORIZE_HPP
#define DIALOG_UTHORIZE_HPP

/*--------------------------------*/
/* Class to display option popup  */
/* Remembers last saved position, */
/* unique for each parent object  */
/*--------------------------------*/

#include <QDialog>

namespace Ui {
  class DialogAuthorize;
}

class DialogAuthorize : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief DialogAuthorize - create and display authorize popup
   * @param string - message text to display
   * @param string - text for accept button
   * @param int - hue for accept button
   * @param string - text for reject button
   * @param int - hue for reject button
   */
  explicit DialogAuthorize(const std::string&, const std::string&, const std::string&, QWidget* = nullptr);
  ~DialogAuthorize();

private:
  Ui::DialogAuthorize *ui;

  /**
   * @brief closeEvent - overwrite close event so accept or reject button has to be pressed
   */
  void closeEvent(QCloseEvent*);

  std::string Username;
  std::string Password;

private slots:
  /*----------------------------------------------------------------*/
  /*UI Slots*/
  /*----------------------------------------------------------------*/
  void on_lineEdit_Password_returnPressed();
  void on_pushButton_Accept_clicked();
  void on_pushButton_Cancel_clicked();
};

#endif // DIALOG_AUTHORIZE_HPP
