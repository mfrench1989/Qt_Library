#ifndef DIALOG_MESSAGE_HPP
#define DIALOG_MESSAGE_HPP

/*--------------------------------*/
/* Class to display message popup */
/* Remembers last saved position, */
/* unique for each parent object  */
/*--------------------------------*/

#include <QDialog>

namespace Ui {
  class DialogMessage;
}

class DialogMessage : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief DialogMessage - create and display message popup
   * @param string - message text to display
   */
  explicit DialogMessage(const std::string&, QWidget* = nullptr);
  ~DialogMessage();

private:
  Ui::DialogMessage *ui;
};

#endif // DIALOG_MESSAGE_HPP
