#pragma once

#include "wall.h"

#include <QDialog>

class QComboBox;
class QGroupBox;
class QDoubleSpinBox;
class QLabel;
class QRadioButton;

namespace GameObjectsEditor
{
    //!
    //! \brief The EditDialog class Диалог редактирования объекта
    //!
    class EditDialog : public QDialog
    {
        Q_OBJECT

    public:
        EditDialog(QWidget * parent = nullptr,
                   const bool isComboBoxEnabled = true,
                   const int index = 0);

        int getCurrentIndex() const;

        QIcon getCurrentIcon() const;

        IconId getCurrentIconId() const;
        void setCurrentIconId(const IconId iconId);

        Wall::Type getWallType() const;
        void setWallType(const Wall::Type type);

        float getSpeed() const;
        void setSpeed(const float speed);

    private slots:
        void onIndexChanged(int index);

    private:
        void initGui(const bool isComboBoxEnabled, const int index);

        QComboBox * objTypeBox;

        QRadioButton * iconRadio1;
        QRadioButton * iconRadio2;

        QGroupBox    * wallTypeBox;
        QRadioButton * wallRadio1;
        QRadioButton * wallRadio2;

        QLabel         * speedLbl;
        QDoubleSpinBox * speedSb;
    };
}

