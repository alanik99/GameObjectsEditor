#include "controller.h"

#include "editdialog.h"
#include "model.h"
#include "common.h"
#include "player.h"
#include "wall.h"
#include "stairs.h"

#include <QDebug>
#include <QMessageBox>

namespace GameObjectsEditor
{
    Controller::Controller(Model * model, QObject * parent) : QObject(parent)
      , model(model)
    {

    }

    bool Controller::addItem(QWidget * parent)
    {
        EditDialog d(parent);
        d.setWindowTitle(toUni("Добавление"));

        if ( d.exec() == QDialog::Accepted )
        {
            const QIcon icon = d.getCurrentIcon();
            const IconId  id = d.getCurrentIconId();

            GameObject * obj = nullptr;

            switch ( d.getCurrentIndex() )
            {
                case ObjectIndex::PLAYER:  obj = new Player(icon, id);                  break;
                case ObjectIndex::WALL  :  obj = new Wall  (icon, id, d.getWallType()); break;
                case ObjectIndex::STAIRS:  obj = new Stairs(icon, id, d.getSpeed()   ); break;
                default:                                                                break;
            }

            if (obj)
                return model->addItem(obj);
        }
        return false;
    }

    bool Controller::editItem(QWidget * parent, const QModelIndex & index)
    {
        GameObject * obj = model->getObject(index);
        if (!obj) return false;

        Player * player = dynamic_cast<Player*>(obj);
        Wall   *   wall = dynamic_cast<Wall*>  (obj);
        Stairs * stairs = dynamic_cast<Stairs*>(obj);

        int i;

        if      (player) i = ObjectIndex::PLAYER;
        else if (wall)   i = ObjectIndex::WALL;
        else if (stairs) i = ObjectIndex::STAIRS;
        else             return false;

        EditDialog d(parent, false, i);
        d.setWindowTitle(toUni("Изменение"));

        // init dialog params from object
        d.setCurrentIconId( obj->getIconId() );

        if   (wall) d.setWallType( wall->getType() );
        if (stairs) d.setSpeed( stairs->getLiftingSpeed() );

        if ( d.exec() == QDialog::Accepted )
        {
            // set object params from dialog
            obj->setIcon  ( d.getCurrentIcon() );
            obj->setIconId( d.getCurrentIconId() );

            if (wall  ) wall  ->setType( d.getWallType() );
            if (stairs) stairs->setLiftingSpeed( d.getSpeed() );

            return true;
        }
        return false;
    }

    bool Controller::remItem(QWidget * parent, const QModelIndex & index)
    {
        QMessageBox msgBox( QMessageBox::Question,
                            toUni("Удаление"),
                            toUni("Вы уверены, что хотите удалить данный объект?"),
                            QMessageBox::Yes | QMessageBox::No,
                            parent );

        msgBox.setButtonText(QMessageBox::Yes, toUni("Да") );
        msgBox.setButtonText(QMessageBox::No , toUni("Нет"));

        if (msgBox.exec() == QMessageBox::Yes)
        {
            return model->remItem(index);
        }
        return false;
    }
}

