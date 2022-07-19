#include "stairs.h"

namespace GameObjectsEditor
{
    Stairs::Stairs(const QIcon & icon,
                   const IconId iconId,
                   const float speed)
        : GameObject(icon, iconId)
        , liftingSpeed(speed)
    {

    }

    float Stairs::getLiftingSpeed() const
    {
        return liftingSpeed;
    }

    void Stairs::setLiftingSpeed(float value)
    {
        static const float min = 1.0f;
        static const float max = 3.0f;

        if (value < min) value = min;
        if (value > max) value = max;

        liftingSpeed = value;
    }
}
