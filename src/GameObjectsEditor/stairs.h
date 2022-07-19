#pragma once

#include "gameobject.h"

namespace GameObjectsEditor
{
    //!
    //! \brief The Stairs class Лестница
    //!
    class Stairs : public GameObject
    {
    public:
        Stairs(const QIcon & icon,
               const IconId iconId,
               const float speed = 1.0f);

        float getLiftingSpeed() const;
        void setLiftingSpeed(float value);

    private:
        float liftingSpeed;
    };
}

