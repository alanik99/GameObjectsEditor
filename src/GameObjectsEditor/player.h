#pragma once

#include "gameobject.h"

namespace GameObjectsEditor
{
    //!
    //! \brief The Player class Игрок
    //!
    class Player : public GameObject
    {
    public:
        Player(const QIcon & icon, const IconId iconId);
    };
}

