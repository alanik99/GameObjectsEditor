#include "editdialog.h"

#include "common.h"

#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

namespace GameObjectsEditor
{
    EditDialog::EditDialog(QWidget * parent,
                           const bool isComboBoxEnabled,
                           const int index)
        : QDialog(parent)
    {
        initGui(isComboBoxEnabled, index);
    }

    int EditDialog::getCurrentIndex() const
    {
        return objTypeBox->currentIndex();
    }

    QIcon EditDialog::getCurrentIcon() const
    {
        if      ( iconRadio1->isChecked() ) return iconRadio1->icon();
        else if ( iconRadio2->isChecked() ) return iconRadio2->icon();
        else                                return QIcon();
    }

    IconId EditDialog::getCurrentIconId() const
    {
        if      ( iconRadio1->isChecked() ) return IconId::ICON_1;
        else if ( iconRadio2->isChecked() ) return IconId::ICON_2;
        else                                return IconId::INVALID;
    }

    void EditDialog::setCurrentIconId(const IconId iconId)
    {
        if ( iconId == IconId::ICON_1 )
        {
            iconRadio1->setChecked(true);
            iconRadio2->setChecked(false);
        }

        if ( iconId == IconId::ICON_2 )
        {
            iconRadio1->setChecked(false);
            iconRadio2->setChecked(true);
        }
    }

    Wall::Type EditDialog::getWallType() const
    {
        if      ( wallRadio1->isChecked() ) return Wall::BREAKABLE;
        else if ( wallRadio2->isChecked() ) return Wall::UNBREAKABLE;
        else                                return Wall::INVALID;
    }

    void EditDialog::setWallType(const Wall::Type type)
    {
        if ( type == Wall::BREAKABLE )
        {
            wallRadio1->setChecked(true);
            wallRadio2->setChecked(false);
        }

        if ( type == Wall::UNBREAKABLE )
        {
            wallRadio1->setChecked(false);
            wallRadio2->setChecked(true);
        }
    }

    float EditDialog::getSpeed() const
    {
        return speedSb->value();
    }

    void EditDialog::setSpeed(const float speed)
    {
        speedSb->setValue(speed);
    }

    void EditDialog::onIndexChanged(int index)
    {
        if ( index == ObjectIndex::PLAYER )
        {
            iconRadio1->setIcon(QIcon(IconPaths::Player1));
            iconRadio2->setIcon(QIcon(IconPaths::Player2));

            wallTypeBox->setVisible(false);
            speedLbl->setVisible(false);
            speedSb ->setVisible(false);
        }

        if ( index == ObjectIndex::WALL )
        {
            iconRadio1->setIcon(QIcon(IconPaths::Wall1));
            iconRadio2->setIcon(QIcon(IconPaths::Wall2));

            wallTypeBox->setVisible(true);
            speedLbl->setVisible(false);
            speedSb ->setVisible(false);
        }

        if ( index == ObjectIndex::STAIRS )
        {
            iconRadio1->setIcon(QIcon(IconPaths::Stairs1));
            iconRadio2->setIcon(QIcon(IconPaths::Stairs2));

            wallTypeBox->setVisible(false);
            speedLbl->setVisible(true);
            speedSb ->setVisible(true);
        }
    }

    void EditDialog::initGui(const bool isComboBoxEnabled, const int index)
    {
        // Object type combo box
        objTypeBox = new QComboBox();
        objTypeBox->addItem(toUni("Игрок"));
        objTypeBox->addItem(toUni("Стена"));
        objTypeBox->addItem(toUni("Лестница"));

        connect(objTypeBox,  QOverload<int>::of(&QComboBox::currentIndexChanged),
                this,        &EditDialog::onIndexChanged);

        // Icon group box
        QGroupBox * iconBox = new QGroupBox(toUni("Иконка"));

        iconRadio1 = new QRadioButton();
        iconRadio2 = new QRadioButton();
        iconRadio1->setChecked(true);

        iconRadio1->setIcon(QIcon(IconPaths::Player1));
        iconRadio2->setIcon(QIcon(IconPaths::Player2));

        const int pix = 40;
        iconRadio1->setIconSize(QSize(pix, pix));
        iconRadio2->setIconSize(QSize(pix, pix));

        QHBoxLayout * hbox = new QHBoxLayout();
        hbox->addWidget(iconRadio1);
        hbox->addWidget(iconRadio2);
        iconBox->setLayout(hbox);

        // Wall type group box
        wallTypeBox = new QGroupBox(toUni("Тип стены"));
        wallTypeBox->setVisible(false);

        wallRadio1  = new QRadioButton(toUni("Обычная"));
        wallRadio2  = new QRadioButton(toUni("Неразрушимая"));
        wallRadio1->setChecked(true);

        QVBoxLayout * vbox = new QVBoxLayout();
        vbox->addWidget(wallRadio1);
        vbox->addWidget(wallRadio2);
        wallTypeBox->setLayout(vbox);

        // Lifting speed layout
        QHBoxLayout * speedLO = new QHBoxLayout();

        speedLbl = new QLabel(toUni("Скорость подъема"));
        speedLbl->setVisible(false);

        speedSb  = new QDoubleSpinBox();
        speedSb->setRange(1.0, 3.0);
        speedSb->setVisible(false);

        speedLO->addWidget(speedLbl);
        speedLO->addWidget(speedSb);

        // Buttons layout
        QHBoxLayout * btnLO = new QHBoxLayout();

        QPushButton * okBtn     = new QPushButton(toUni("Ок"));
        QPushButton * cancelBtn = new QPushButton(toUni("Отмена"));

        btnLO->addWidget(okBtn);
        btnLO->addWidget(cancelBtn);

        connect(okBtn,     &QPushButton::clicked,
                this,      &QDialog::accept);

        connect(cancelBtn, &QPushButton::clicked,
                this,      &QDialog::reject);

        // Main layout
        QVBoxLayout * mainLO = new QVBoxLayout();
        mainLO->addWidget(objTypeBox);
        mainLO->addWidget(iconBox);
        mainLO->addWidget(wallTypeBox);
        mainLO->addLayout(speedLO);
        mainLO->addLayout(btnLO);

        mainLO->setSizeConstraint(QLayout::SetFixedSize);
        setLayout(mainLO);

        // for editing mode
        objTypeBox->setEnabled(isComboBoxEnabled);
        objTypeBox->setCurrentIndex(index);
    }
}
