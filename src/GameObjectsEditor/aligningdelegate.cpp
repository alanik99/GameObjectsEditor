#include "aligningdelegate.h"

#include <QPainter>

namespace GameObjectsEditor
{
    AligningDelegate::AligningDelegate(QObject * parent) :
        QStyledItemDelegate(parent)
    {

    }

    void AligningDelegate::paint(QPainter * painter,
                                 const QStyleOptionViewItem & option,
                                 const QModelIndex & index) const
    {
        QRect rect = option.rect;
        QPixmap pix = qvariant_cast<QPixmap>(index.data(Qt::DecorationRole));

        QPoint p = QPoint((rect.width() - pix.width())/2, (rect.height() - pix.height())/2);
        painter->drawPixmap(rect.topLeft() + p, pix);

        if ( option.state & QStyle::State_Selected )
        {
            QBrush brush = option.palette.highlight();

            QPen pen(brush.color());
            pen.setWidth(2);

            painter->setPen(pen);
            painter->drawRect(option.rect);
        }
    }
}


