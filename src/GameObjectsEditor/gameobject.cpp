#include "gameobject.h"

namespace GameObjectsEditor
{
    GameObject::GameObject(const QIcon & icon, const IconId iconId)
        : icon(icon)
        , iconId(iconId)
    {

    }

    QIcon GameObject::getIcon() const
    {
        return icon;
    }

    void GameObject::setIcon(const QIcon & value)
    {
        icon = value;
    }

    IconId GameObject::getIconId() const
    {
        return iconId;
    }

    void GameObject::setIconId(const IconId value)
    {
        iconId = value;
    }
}
