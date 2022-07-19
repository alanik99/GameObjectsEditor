#pragma once

#include <QStyledItemDelegate>

namespace GameObjectsEditor
{
    //!
    //! \brief The AligningDelegate class Делегат для выравнивания иконки по центру ячейки
    //!
    class AligningDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        explicit AligningDelegate(QObject * parent = 0);

        void paint(QPainter * painter,
                   const QStyleOptionViewItem & option,
                   const QModelIndex & index) const;
    };
}

