#include <QPainter>
#include <QTextDocument>

#include "object_html.hpp"

void ObjectHTML::paint(QPainter* painter_in, const QStyleOptionViewItem& option_in, const QModelIndex& index_in) const {
  QStyleOptionViewItem options = option_in;
  initStyleOption(&options, index_in);

  painter_in->save();

  QTextDocument doc;
  doc.setDefaultFont(options.font);
  doc.setHtml(options.text);

  options.text = "";
  options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter_in, options.widget);

  /*Shift text right to make icon visible*/
  QSize iconSize = options.icon.actualSize(options.rect.size());
  painter_in->translate(options.rect.left()+iconSize.width(), options.rect.top());
  QRect clip(0, 0, options.rect.width()+iconSize.width(), options.rect.height());

  doc.drawContents(painter_in, clip);

  painter_in->restore();
}

QSize ObjectHTML::sizeHint(const QStyleOptionViewItem& option_in, const QModelIndex& index_in) const {
  QStyleOptionViewItem options = option_in;
  initStyleOption(&options, index_in);

  QTextDocument doc;
  doc.setDefaultFont(options.font);
  doc.setHtml(options.text);
  doc.setTextWidth(options.rect.width());
  return QSize(doc.idealWidth(), doc.size().height());
}
