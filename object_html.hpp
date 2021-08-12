#ifndef OBJECTHTML_HPP
#define OBJECTHTML_HPP

#include <QStyledItemDelegate>

class ObjectHTML : public QStyledItemDelegate {
protected:
    void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const;
};

#endif // OBJECTHTML_HPP
