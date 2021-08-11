#ifndef FUNCTIONINTERFACE_HPP
#define FUNCTIONINTERFACE_HPP

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollBar>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTextBrowser>
#include <QToolBar>
#include <QToolButton>

/*Hue 0-360*/
#define HUE_BASE 210
#define HUE_BLUE 205
#define HUE_GREEN 125
#define HUE_RED 5
#define HUE_YELLOW 55

/*Saturation 0-100*/
#define SAT_BASE 10
#define SAT_COLOR 65
#define SAT_GRAY 0

/*Luminosity 0-100*/
#define LUM_COLOR 55
#define LUM_DARK 15
#define LUM_GRAY 70
#define LUM_TEXT 90
#define LUM_LIGHT 95

/**
 * @brief comboBoxFormat - format stylesheet
 * @param QComboBox - ui element
 */
void comboBoxFormat(const QComboBox&);

/**
 * @brief comboBoxUpdate - update QComboBox with new items
 * @param QComboBox - ui element
 * @param vector<string> - list of strings to display
 */
void comboBoxUpdate(QComboBox&, const std::vector<std::string>&);

/**
 * @brief groubBoxFormat - format stylesheet
 * @param QGroupBox - ui element
 */
void groubBoxFormat(const QGroupBox&);

/**
 * @brief labelFormat - format stylesheet
 * @param QLabel - ui element
 * @param double - hue
 * @param double - saturation
 * @param double - luminosity
 * @param bool - bold
 */
void labelFormat(const QLabel&, const double, const double, const double, const bool);

/**
 * @brief lineEditClear - clear all line edits that are children of widget
 * @param QWidget - widget to clear the child line edits of
 */
void lineEditClear(const QWidget&);

/**
 * @brief lineEditFormat - format stylesheet
 * @param QLineEdit - ui element
 */
void lineEditFormat(const QLineEdit&);

/**
 * @brief lineEditSetPlaceholder - set placeholder text with formatted number
 * @param QLineEdit - ui element
 * @param double - value to display
 */
void lineEditSetPlaceholder(QLineEdit&, const double);

/**
 * @brief lineEditSetPlaceholder - set placeholder text with string
 * @param QLineEdit - ui element
 * @param string - string to display
 */
void lineEditSetPlaceholder(QLineEdit&, const std::string&);

/**
 * @brief lineEditSetText - set line edit text with formatted number
 * @param QLineEdit - ui element
 * @param double - value to display
 */
void lineEditSetText(QLineEdit&, const double);

/**
 * @brief listWidgetFormat - format stylesheet
 * @param QListWidget - ui element
 */
void listWidgetFormat(const QListWidget&);

/**
 * @brief progressBarFormat - format stylesheet
 * @param QProgressBar - ui element
 */
void progressBarFormat(const QProgressBar&);

/**
 * @brief pushButtonFormat - format stylesheet
 * @param QPushButton - ui element
 */
void pushButtonFormat(const QPushButton&  );

/**
 * @brief scrollBarFormat - format stylesheet
 * @param QScrollBar - ui element
 */
void scrollBarFormat(const QScrollBar&);

/**
 * @brief stackedWidgetFormat - format stylesheet
 * @param QStackedWidget - ui element
 */
void stackedWidgetFormat(const QStackedWidget&);

/**
 * @brief tableWidgetFormat - format stylesheet
 * @param QTableWidget - ui element
 */
void tableWidgetFormat(const QTableWidget&);

/**
 * @brief textBrowserFormat - format stylesheet
 * @param QTextBrowser - ui element
 */
void textBrowserFormat(const QTextBrowser&);

/**
 * @brief toolBarFormat - format stylesheet
 * @param QToolBar - ui element
 */
void toolBarFormat(const QToolBar&);

/**
 * @brief toolButtonFormat - format stylesheet
 * @param QToolButton - ui element
 */
void toolButtonFormat(const QToolButton&);

/**
 * @brief widgetFormat - format stylesheet
 * @param QWidget - ui element
 * @param double - hue
 * @param double - saturation
 * @param double - luminosity
 */
void widgetFormat(const QWidget&, const double, const double, const double);

/**
 * @brief lineEditGetText - get line edit text if available, otherwise grab placeholder text
 * @return
 */
std::string lineEditGetText(const QLineEdit&);
#endif // FUNCTIONINTERFACE_HPP
