#pragma once

#include <QObject>

namespace GameObjectsEditor
{
    class Model;
    class GameObject;

    //!
    //! \brief The Controller class Контроллер
    //!
    class Controller : public QObject
    {
        Q_OBJECT

    public:
        explicit Controller(Model * model, QObject * parent = nullptr);

    public slots:
        bool addItem(QWidget * parent);
        bool editItem(QWidget * parent, const QModelIndex & index);
        bool remItem(QWidget * parent, const QModelIndex & index);

    private:
        Model * model;
    };
}

