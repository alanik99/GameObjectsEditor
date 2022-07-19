#pragma once

#include <QAbstractTableModel>
#include <QList>

namespace GameObjectsEditor
{
    class GameObject;

    //!
    //! \brief The Model class Модель
    //!
    class Model : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit Model(QObject * parent = nullptr);
        ~Model();

        int count() const;

        GameObject * getObject(const QModelIndex & index) const;

        int toListIndex(const QModelIndex & index) const;
        QModelIndex fromListIndex(const int index) const;

        bool addItem(GameObject * item);
        bool remItem(const QModelIndex & index);

    private:
        int rowCount(const QModelIndex & parent) const override;
        int columnCount(const QModelIndex & parent) const override;
        QVariant data(const QModelIndex & index, int role) const override;

        void initList();
        inline bool isValidIndex(const int index) const;

        QList< GameObject* > list;
    };
}

