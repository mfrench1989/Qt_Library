#include <QApplication>
#include <QClipboard>
#include <QEvent>
#include <QKeyEvent>

#include "CPPLibrary/function_string.hpp"
#include "function_interface.hpp"

#include "function_filter.hpp"

bool filterComboBox(QComboBox*, QEvent* event_in) {
  return static_cast<bool>(event_in->type() == QEvent::Wheel);
}

bool filterLineEdit(QLineEdit* line_edit, QEvent* event_in) {
  if (event_in->type() == QEvent::KeyPress) {
      QKeyEvent *key_event = static_cast<QKeyEvent*>(event_in);

      /*Paste clipboard text in line edits*/
      if (key_event->matches(QKeySequence::Paste)) {
          std::string string_copy = qApp->clipboard()->text().toStdString();

          /*Replace tabs with spaces*/
          string_copy = stringReplace(string_copy, "\t", " ");

          /*Recursively replaces all double spaces with single spaces*/
          while (string_copy.find("  ") != std::string::npos) {
              string_copy = stringReplace(string_copy, "  ", " ");
            }

          /*Replace all valid delimiters with string_delimiter*/
          const std::string string_delimiter = ",";
          string_copy = stringReplace(string_copy, "\n", string_delimiter);
          string_copy = stringReplace(string_copy, ";", string_delimiter);
          string_copy = stringReplace(string_copy, ", ", string_delimiter);
          string_copy = stringReplace(string_copy, " ", string_delimiter);

          /*Create vector of strings split by delimiter*/
          std::vector<std::string> vector_copy = stringSplit(string_copy, string_delimiter);
          for (const std::string& string_paste : vector_copy) {
              line_edit->clear();

              /*Paste index of vector_copy in line edit if it's visible and enabled*/
              if (line_edit->isVisible() && line_edit->isEnabled()) {
                  if (stringIsNum(string_paste)) {
                      guiSetText(*line_edit, stringToNum(string_paste));
                    }
                  else {
                      line_edit->setText(QString::fromStdString(string_paste));
                    }
                }

              /*Get next line edit in focus chain*/
              QWidget* widget_focus = line_edit->nextInFocusChain();
              while (!widget_focus->inherits("QLineEdit") && widget_focus->isVisible()) {
                  widget_focus = widget_focus->nextInFocusChain();
                }
              if (widget_focus->inherits("QLineEdit") && widget_focus->isVisible()) {
                  line_edit = qobject_cast<QLineEdit*>(widget_focus);
                }
              else {
                  break;
                }
            }
          return true;
        }

      /*Clear line edit text*/
      else if (key_event->key() == Qt::Key_Escape) {
          line_edit->clear();
        }

      /*Bring background text forward*/
      else if ((key_event->key() == Qt::Key_Enter || key_event->key() == Qt::Key_Return) && line_edit->text().isEmpty()) {
          if (stringIsNum(line_edit->placeholderText().toStdString()) && line_edit->validator()) {
              guiSetText(*line_edit, stringToNum(line_edit->placeholderText().toStdString()));
            }
          else {
              line_edit->setText(line_edit->placeholderText());
            }
        }

      /*Tab to next focus*/
      else if ((key_event->key() == Qt::Key_Enter || key_event->key() == Qt::Key_Return) && !line_edit->text().isEmpty()) {
          line_edit->nextInFocusChain()->setFocus();
        }

      /*Key press is a numerical value and line edit has validator*/
      else if (line_edit->validator() && stringIsNum(key_event->text().toStdString())) {
          /*Delete selected text*/
          if (line_edit->hasSelectedText()) {
              line_edit->del();
            }

          /*Insert key text into current line edit text*/
          QString string_text = line_edit->text();
          int pos_cursor = line_edit->cursorPosition();
          string_text.insert(pos_cursor, key_event->text());

          /*Validate text*/
          if (line_edit->validator()->validate(string_text, pos_cursor) == QValidator::Acceptable) {
              return false;
            }
          else {
              return true;
            }
        }
    }
  return false;
}

bool filterToolButton(QToolButton*, QEvent* event_in) {
  return static_cast<bool>(event_in->type() == QEvent::ToolTip);
}
