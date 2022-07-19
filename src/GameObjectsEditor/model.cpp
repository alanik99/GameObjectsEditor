#include "model.h"

#include "common.h"
#include "gameobject.h"
#include "player.h"
#include "wall.h"
#include "stairs.h"

#include <QDebug>

namespace GameObjectsEditor
{
    Model::Model(QObject * parent) : QAbstractTableModel(parent)
    {
        initList();
    }

    Model::~Model()
    {
        qDeleteAll(list);
    }

    int Model::count() const
    {
        return list.size();
    }

    GameObject * Model::getObject(const QModelIndex & index) const
    {
        int i = toListIndex(index);

        return isValidIndex(i) ? list.at(i) : nullptr;
    }

    int Model::toListIndex(const QModelIndex &index) const
    {
        return index.row() * columnCount(QModelIndex()) + index.column();
    }

    QModelIndex Model::fromListIndex(const int index) const
    {
        if ( isValidIndex(index) )
        {
            int row = index / columnCount(QModelIndex());
            int col = index - row * columnCount(QModelIndex());

            return createIndex(row, col);
        }

        return createIndex(0, 0); // by default, - in case of invalid index
    }

    bool Model::addItem(GameObject * item)
    {
        beginResetModel();

        list.append(item);

        endResetModel();

        return true;
    }

    bool Model::remItem(const QModelIndex & index)
    {
        int i = toListIndex(index);

        if ( isValidIndex(i) )
        {
            beginResetModel();

            delete list.at(i);
            list.removeAt(i);

            endResetModel();

            return true;
        }
        return false;
    }

    int Model::rowCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return (list.size()-1) / columnCount(QModelIndex()) + 1;
    }

    int Model::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return 3;
    }

    QVariant Model::data(const QModelIndex & index, int role) const
    {
        if (role == Qt::DecorationRole)
        {
            const int i = toListIndex(index);

            if ( isValidIndex(i) )
            {
                return list.at(i)->getIcon().pixmap(QSize(40, 40));
            }
            else
            {
                return QVariant();
            }
        }

        return QVariant();
    }

    void Model::initList()
    {
        list = {
            new Player  (QIcon(IconPaths::Player1), IconId::ICON_1)
            , new Wall  (QIcon(IconPaths::Wall1)  , IconId::ICON_1)
            , new Stairs(QIcon(IconPaths::Stairs1), IconId::ICON_1)

            , new Player(QIcon(IconPaths::Player2), IconId::ICON_2)
            , new Wall  (QIcon(IconPaths::Wall2)  , IconId::ICON_2)
            , new Stairs(QIcon(IconPaths::Stairs2), IconId::ICON_2)
        };
    }

    bool Model::isValidIndex(const int index) const
    {
        return index >= 0 && index < list.size();
    }
}
