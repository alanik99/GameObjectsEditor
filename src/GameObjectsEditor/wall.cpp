#include "wall.h"

namespace GameObjectsEditor
{
    Wall::Wall(const QIcon &icon,
               const IconId iconId,
               const Type type)
        : GameObject(icon, iconId)
        , type(type)
    {

    }

    Wall::Type Wall::getType() const
    {
        return type;
    }

    void Wall::setType(const Type value)
    {
        type = value;
    }
}
