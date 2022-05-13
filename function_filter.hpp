#ifndef FUNCTIONFILTER_HPP
#define FUNCTIONFILTER_HPP

#include <QComboBox>
#include <QLineEdit>
#include <QToolButton>

/**
 * @brief filterComboBox - custom filter for QComboBox events
 * @param QComboBox - ui element
 * @param QEvent - event
 * @return
 */
bool filterComboBox(QComboBox*, QEvent*);

/**
 * @brief filterLineEdit - custom filter for QLineEdit events, mostly for custom controls
 * @param QLineEdit - ui element
 * @param QEvent - event
 * @return
 */
bool filterLineEdit(QLineEdit*, QEvent*);

/**
 * @brief filterToolButton - custom filter for QToolButton events
 * @param QToolButton - ui element
 * @param QEvent - event
 * @return
 */
bool filterToolButton(QToolButton*, QEvent*);

#endif // FUNCTIONFILTER_HPP
