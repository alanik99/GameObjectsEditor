#pragma once

#include "common.h"

#include <QIcon>

namespace GameObjectsEditor
{
    //!
    //! \brief The GameObject class Базовый класс игрового объекта
    //!
    class GameObject
    {
    public:
        GameObject(const QIcon & icon, const IconId iconId);
        virtual ~GameObject() {}

        QIcon getIcon() const;
        void setIcon(const QIcon & value);

        IconId getIconId() const;
        void setIconId(const IconId value);

    protected:
        QIcon icon;
        IconId iconId;
    };
}

