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
 * @brief guiFormatComboBox - format stylesheet
 * @param QComboBox - ui element
 */
void guiFormatComboBox(QComboBox&);

/**
 * @brief guiFormatGroubBox - format stylesheet
 * @param QGroupBox - ui element
 */
void guiFormatGroubBox(QGroupBox&);

/**
 * @brief guiFormatLabel - format stylesheet
 * @param QLabel - ui element
 * @param double - hue
 * @param double - saturation
 * @param double - luminosity
 * @param bool - bold
 */
void guiFormatLabel(QLabel&, const double, const double, const double, const bool);

/**
 * @brief guiFormatLineEdit - format stylesheet
 * @param QLineEdit - ui element
 */
void guiFormatLineEdit(QLineEdit&);

/**
 * @brief guiFormatListWidget - format stylesheet
 * @param QListWidget - ui element
 */
void guiFormatListWidget(QListWidget&);

/**
 * @brief guiFormatProgressBar - format stylesheet
 * @param QProgressBar - ui element
 */
void guiFormatProgressBar(QProgressBar&);

/**
 * @brief guiFormatPushButton - format stylesheet
 * @param QPushButton - ui element
 */
void guiFormatPushButton(QPushButton&, double, double);

/**
 * @brief guiFormatScrollBar - format stylesheet
 * @param QScrollBar - ui element
 */
void guiFormatScrollBar(QScrollBar&);

/**
 * @brief guiFormatStackedWidget - format stylesheet
 * @param QStackedWidget - ui element
 */
void guiFormatStackedWidget(QStackedWidget&);

/**
 * @brief guiFormatTableWidget - format stylesheet
 * @param QTableWidget - ui element
 */
void guiFormatTableWidget(QTableWidget&);

/**
 * @brief guiFormatTextBrowser - format stylesheet
 * @param QTextBrowser - ui element
 */
void guiFormatTextBrowser(QTextBrowser&);

/**
 * @brief guiFormatToolBar - format stylesheet
 * @param QToolBar - ui element
 */
void guiFormatToolBar(QToolBar&);

/**
 * @brief guiFormatToolButton - format stylesheet
 * @param QToolButton - ui element
 */
void guiFormatToolButton(QToolButton&);

/**
 * @brief guiFormatWidget - format stylesheet
 * @param QWidget - ui element
 * @param double - hue
 * @param double - saturation
 * @param double - luminosity
 */
void guiFormatWidget(QWidget&, const double, const double, const double);

/**
 * @brief guiClearLineEdits - clear all line edits that are children of widget
 * @param QWidget - widget to clear the child line edits of
 */
void guiClearLineEdits(const QWidget&);

/**
 * @brief guiSetPlaceholder - set placeholder text with formatted number
 * @param QLineEdit - ui element
 * @param double - value to display
 */
void guiSetPlaceholder(QLineEdit&, const double);

/**
 * @brief guiSetPlaceholder - set placeholder text with string
 * @param QLineEdit - ui element
 * @param string - string to display
 */
void guiSetPlaceholder(QLineEdit&, const std::string&);

/**
 * @brief guiSetText - set line edit text with formatted number
 * @param QLineEdit - ui element
 * @param double - value to display
 */
void guiSetText(QLineEdit&, const double);

/**
 * @brief guiUpdateComboBox - update QComboBox with new items
 * @param QComboBox - ui element
 * @param vector<string> - list of strings to display
 */
void guiUpdateComboBox(QComboBox&, const std::vector<std::string>&);

/**
 * @brief guiGetText - get line edit text if available, otherwise grab placeholder text
 * @return
 */
std::string guiGetText(const QLineEdit&);
#endif // FUNCTIONINTERFACE_HPP
