#pragma once

#include <QString>

namespace GameObjectsEditor
{
    //! Пути иконок
    namespace IconPaths
    {
        static constexpr char Player1[] = "../imgs/Player.png";
        static constexpr char Player2[] = "../imgs/Player2.png";

        static constexpr char Wall1[]   = "../imgs/Wall.png";
        static constexpr char Wall2[]   = "../imgs/Wall2.png";

        static constexpr char Stairs1[] = "../imgs/Stairs.png";
        static constexpr char Stairs2[] = "../imgs/Stairs2.png";
    }

    //!
    //! \brief The IconId enum Идентификатор иконки
    //!
    enum IconId
    {
        ICON_1
        , ICON_2
        , INVALID = -1
    };

    //!
    //! \brief The ObjectIndex enum Индекс объекта в диалоге редактирования
    //!
    enum ObjectIndex
    {
        PLAYER
        , WALL
        , STAIRS
    };
}

//!
//! \brief toUni Получить QString из кодировки UTF-8
//! \param str Строка в кодировке UTF-8
//! \return QString
//!
inline QString toUni( const char * str )
{
    return QString::fromUtf8(str);
}

