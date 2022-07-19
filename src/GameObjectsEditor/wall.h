#pragma once

#include "gameobject.h"

namespace GameObjectsEditor
{
    //!
    //! \brief The Wall class Стена
    //!
    class Wall : public GameObject
    {
    public:
        enum Type
        {
            BREAKABLE
            , UNBREAKABLE
            , INVALID = -1
        };

        Wall(const QIcon & icon,
             const IconId iconId,
             const Type type = BREAKABLE);

        Type getType() const;
        void setType(const Type value);

    private:
        Type type;
    };
}

