#include <QHeaderView>

#include "function_string.hpp"

#include "function_gui.hpp"

void guiClearLineEdits(const QWidget& widget) {
  for (QLineEdit* line_edit : widget.findChildren<QLineEdit*>()) {
      line_edit->clear();
    }
}

void guiFormatComboBox(QComboBox& combo_box) {
  combo_box.setStyleSheet(QString::fromStdString("QComboBox {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";" +
                                                "border-radius: 4px; padding: 4px; spacing: 4px;}" +

                                                "QComboBox::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                "QComboBox::down-arrow {image: none;" +
                                                "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";" +
                                                "border-radius: 4px;}" +

                                                "QComboBox::drop-down {image: none;" +
                                                "background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";}" +
                                                "QComboBox::hover {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 35) +";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";}" +

                                                "QComboBox::indicator {background:transparent;" +
                                                "selection-background-color:transparent;" +
                                                "color:transparent;" +
                                                "selection-color:transparent;}" +

                                                "QComboBox::item:selected {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";" +
                                                "border-radius: 4px;}"));
}

void guiFormatGroupBox(QGroupBox& group_box) {
  group_box.setStyleSheet(QString::fromStdString("QGroupBox {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                "border-radius: 4px; padding: 4px; spacing: 4px;" +
                                                "margin-top: 24px;}" +

                                                "QGroupBox::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                "QGroupBox::title {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                "border-radius: 4px; padding: 2px; spacing: 4px;" +
                                                "padding-left: 16px; padding-right: 16px;" +
                                                "subcontrol-origin: margin; subcontrol-position: top;}" +

                                                "QGroupBox::indicator {border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";}" +

                                                "QGroupBox::indicator:checked {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";}" +

                                                "QGroupBox::indicator:disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                "QGroupBox::indicator:hover {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";}" +

                                                "QGroupBox::indicator::pressed {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";}"));
}

void guiFormatLabel(QLabel& label, const double hue, const double saturation, const double luminosity, const bool bold) {
  label.setStyleSheet(QString::fromStdString("QLabel {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                             "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                             "border: " + (bold ? "6" : "2") + "px solid" + stringColorHSL(hue, saturation, luminosity) + ";" +
                                             "border-radius: " + (bold ? "8" : "4") + "px; padding: 4px; spacing: 4px;}" +

                                             "QLabel::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 30) + ";" +
                                             "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";" +
                                             "border: " + (bold ? "6" : "2") + "px solid" + stringColorHSL(hue, saturation - 20, luminosity - 15) + ";" +
                                             "border-radius: " + (bold ? "8" : "4") + "px;}"));
}

void guiFormatLineEdit(QLineEdit& line_edit) {
  line_edit.setStyleSheet(QString::fromStdString("QLineEdit {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                "border-radius: 4px; padding: 4px; spacing: 4px;}" +

                                                "QLineEdit[readOnly=\"true\"] {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";}" +

                                                "QLineEdit::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}"));
}

void guiFormatListWidget(QListWidget& list_widget) {
  list_widget.setStyleSheet(QString::fromStdString("QListWidget {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                  "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                  "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                  "border-radius: 4px; padding: 4px; spacing: 4px;}" +

                                                  "QListWidget::disabled {color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                  "QListWidget::item {padding: 6px; margin-right: 4px;}" +

                                                  "QListWidget::item:selected {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";" +
                                                  "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";" +
                                                  "border-radius: 4px;}"));
}

void guiFormatProgressBar(QProgressBar& progress_bar) {
  progress_bar.setStyleSheet(QString::fromStdString("QProgressBar {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                   "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                   "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";" +
                                                   "border-radius: 4px;}" +

                                                   "QProgressBar::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 35) + ";" +
                                                   "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}"));
}

void guiFormatPushButton(QPushButton& push_button, double hue, double saturation) {
  std::string style_string;
  if (push_button.isCheckable()) {
      style_string.append("QPushButton {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 35) + ";" +
                          "border: 6px solid" + stringColorHSL(hue, saturation, 45) + ";" +
                          "border-radius: 8px;" +
                          "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";}" +

                          "QPushButton::checked {background:" + stringColorHSL(hue, saturation, 35) + ";}" +

                          "QPushButton::checked:disabled {background:" + stringColorHSL(hue, saturation - 20, 25) + ";}" +

                          "QPushButton::checked:hover {background:" + stringColorHSL(hue, saturation, 55) + ";}");
    }
  else {
      style_string.append("QPushButton {background:" + stringColorHSL(hue, saturation, 45) + ";" +
                          "border: 2px solid" + stringColorHSL(hue, saturation, 45) + ";" +
                          "border-radius: 4px;" +
                          "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";}");
    }
  style_string.append("QPushButton::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                      "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                      "QPushButton::hover {background:" + stringColorHSL(hue, saturation, 65) + ";}" +

                      "QPushButton::pressed {background:" + stringColorHSL(hue, saturation, 35) + ";}");
  push_button.setStyleSheet(QString::fromStdString(style_string));
}

void guiFormatScrollBar(QScrollBar& scroll_bar) {
  scroll_bar.setStyleSheet(QString::fromStdString("QScrollBar {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                 "border: 2px solid" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";" +
                                                 "border-radius: 4px;" +
                                                 "padding: 0px;" +
                                                 "qproperty-focusPolicy: NoFocus;}" +

                                                 "QScrollBar::handle {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";" +
                                                 "border-radius: 4px;}" +

                                                 "QScrollBar::handle:horizontal {min-width: 32px;}" +

                                                 "QScrollBar::handle:hover {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";}" +

                                                 "QScrollBar::handle:pressed {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";}" +

                                                 "QScrollBar::handle:vertical {min-height: 32px;}" +

                                                 "QScrollBar::down-arrow," +
                                                 "QScrollBar::left-arrow," +
                                                 "QScrollBar::right-arrow," +
                                                 "QScrollBar::up-arrow {background: none;}" +

                                                 "QScrollBar::add-line," +
                                                 "QScrollBar::sub-line {background: none;}" +

                                                 "QScrollBar::add-page," +
                                                 "QScrollBar::sub-page {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";}"));
}

void guiFormatStackedWidget(QStackedWidget& stacked_widget) {
  stacked_widget.setStyleSheet(QString::fromStdString("QStackedWidget {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                     "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";"  +
                                                     "border-radius: 4px;}" +

                                                     "QStackedWidget::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                     "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";"  +
                                                     "border-radius: 4px;}"));
}

void guiFormatTableWidget(QTableWidget& table_widget) {
  table_widget.setStyleSheet(QString::fromStdString("QTableWidget {background:" + stringColorHSL(HUE_BASE, SAT_BASE, LUM_DARK) + ";" +
                                                   "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                   "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                   "border-radius: 4px;" +
                                                   "gridline-color: " + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";}" +

                                                   "QHeaderView::section {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                   "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                   "padding: 4px; spacing: 4px;}" +

                                                   "QTableWidget::disabled {color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                   "QTableWidget::item {padding: 6px;}" +

                                                   "QTableWidget::item:selected {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";}"));

  table_widget.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table_widget.horizontalHeader()->setStretchLastSection(true);
  table_widget.horizontalHeader()->setFont(table_widget.font());
  table_widget.horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

  table_widget.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table_widget.verticalHeader()->setFont(table_widget.font());
  table_widget.verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
}

void guiFormatTextBrowser(QTextBrowser& text_browser) {
  text_browser.setStyleSheet(QString::fromStdString("QTextBrowser {color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";" +
                                                   "border: 2px solid" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_GRAY) + ";" +
                                                   "border-radius: 4px; padding: 4px; spacing: 4px;}" +

                                                   "QTextBrowser::disabled {color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                   "QTextEdit {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";}"));
  guiFormatWidget(*text_browser.findChild<QWidget*>("qt_scrollarea_viewport"), HUE_BASE, SAT_BASE, 25);
}

void guiFormatToolBar(QToolBar& tool_bar) {
  tool_bar.setStyleSheet(QString::fromStdString("QToolBar {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 35) + ";" +
                                               "border-radius: 0px; padding: 4px; spacing: 4px;" +
                                               "min-height: 48px;" +
                                               "min-width: 48px;" +
                                               "qproperty-iconSize: 52px 52px;" +
                                               "qproperty-toolButtonStyle: ToolButtonTextUnderIcon;}"));
}

void guiFormatToolButton(QToolButton& tool_button) {
  tool_button.setStyleSheet(QString::fromStdString("QToolButton {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 35) + ";" +
                                                  "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";"  +
                                                  "border-radius: 4px; padding: 4px; spacing: 4px;}" +

                                                  "QToolButton::checked {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 45) + ";}" +

                                                  "QToolButton::disabled {background:" + stringColorHSL(HUE_BASE, SAT_BASE, 25) + ";" +
                                                  "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}" +

                                                  "QToolButton::hover {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 65) + ";}" +

                                                  "QToolButton::pressed {background:" + stringColorHSL(HUE_BLUE, SAT_COLOR, 35) + ";}"));
}

void guiFormatWidget(QWidget& widget, const double hue, const double saturation, const double luminosity) {
  widget.setStyleSheet(QString::fromStdString("QWidget {background:" + stringColorHSL(hue, saturation, luminosity) + ";" +
                                              "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT) + ";}" +

                                              "QWidget::disabled {background:" + stringColorHSL(hue, saturation, luminosity + 10) + ";" +
                                              "color:" + stringColorHSL(HUE_BASE, SAT_GRAY, 50) + ";}"));
}

void guiInitStyle(const QObject& object) {
  for (QWidget* widget : object.findChildren<QWidget*>()) {
      guiFormatWidget(*widget, HUE_BASE, SAT_BASE, 5);
    }
  for (QToolBar* toolbar : object.findChildren<QToolBar*>()) {
      guiFormatToolBar(*toolbar);
    }

  for (QComboBox* combobox : object.findChildren<QComboBox*>()) {
      guiFormatComboBox(*combobox);
    }
  for (QGroupBox* groupbox : object.findChildren<QGroupBox*>()) {
      guiFormatGroupBox(*groupbox);
    }
  for (QLabel* label : object.findChildren<QLabel*>()) {
      guiFormatLabel(*label, HUE_BASE, SAT_GRAY, LUM_GRAY, false);
    }
  for (QLineEdit* lineedit : object.findChildren<QLineEdit*>()) {
      guiFormatLineEdit(*lineedit);
    }
  for (QListWidget* listwidget : object.findChildren<QListWidget*>()) {
      guiFormatListWidget(*listwidget);
    }
  for (QProgressBar* progressbar : object.findChildren<QProgressBar*>()) {
      guiFormatProgressBar(*progressbar);
    }
  for (QPushButton* pushbutton : object.findChildren<QPushButton*>()) {
      guiFormatPushButton(*pushbutton, HUE_BLUE, SAT_COLOR);
    }
  for (QScrollBar* scrollbar : object.findChildren<QScrollBar*>()) {
      guiFormatScrollBar(*scrollbar);
    }
  for (QStackedWidget* stackedwidget : object.findChildren<QStackedWidget*>()) {
      guiFormatStackedWidget(*stackedwidget);
    }
  for (QTableWidget* tablewidget : object.findChildren<QTableWidget*>()) {
      guiFormatTableWidget(*tablewidget);
    }
  for (QTextBrowser* textbrowser : object.findChildren<QTextBrowser*>()) {
      guiFormatTextBrowser(*textbrowser);
    }
  for (QToolButton* toolbutton : object.findChildren<QToolButton*>()) {
      guiFormatToolButton(*toolbutton);
    }
}

void guiSetPlaceholder(QLineEdit& line_edit, const double value_in) {
  if (line_edit.validator()) {
      QDoubleValidator *text_validator = line_edit.findChild<QDoubleValidator*>();
      line_edit.setPlaceholderText(QString::number(value_in, 'f', text_validator->decimals()));
    }
  else {
      line_edit.setPlaceholderText(QString::number(value_in));
    }
  line_edit.clear();
}

void guiSetPlaceholder(QLineEdit& line_edit, const std::string& string_in) {
  line_edit.setPlaceholderText(QString::fromStdString(string_in));
  line_edit.clear();
}

void guiSetText(QLineEdit& line_edit, const double value_in) {
  if (line_edit.validator()) {
      QDoubleValidator *text_validator = line_edit.findChild<QDoubleValidator*>();
      line_edit.setText(QString::number(value_in, 'f', text_validator->decimals()));
    }
  else {
      line_edit.setText(QString::number(value_in));
    }
}

void guiUpdateComboBox(QComboBox& combo_box, const std::vector<std::string>& vector_label) {
  combo_box.clear();
  for (const std::string& string_label : vector_label) {
      combo_box.addItem(QString::fromStdString(string_label));
    }
}

std::string guiGetText(const QLineEdit& line_edit) {
  return (line_edit.text().isEmpty()) ? line_edit.placeholderText().toStdString() : line_edit.text().toStdString();
}
