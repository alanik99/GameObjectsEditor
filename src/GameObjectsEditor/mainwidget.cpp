#include "mainwidget.h"

#include "model.h"
#include "controller.h"
#include "aligningdelegate.h"
#include "common.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>

namespace GameObjectsEditor
{
    MainWidget::MainWidget(QWidget *parent)
        : QWidget(parent)
        , view   ( new QTableView() )
        , model  ( new Model() )
        , addBtn ( new QPushButton(toUni("Добавить")) )
        , editBtn( new QPushButton(toUni("Изменить")) )
        , delBtn ( new QPushButton(toUni("Удалить")) )
    {
        controller = new Controller(model);

        view->setModel(model);

        setView();

        initLayout();

        makeConnections();

        updateButtons( view->currentIndex() );
    }

    MainWidget::~MainWidget()
    {
        delete view;
        delete model;
    }

    void MainWidget::initLayout()
    {
        QHBoxLayout * btnLO = new QHBoxLayout();
        btnLO->addWidget(addBtn);
        btnLO->addWidget(editBtn);
        btnLO->addWidget(delBtn);

        QVBoxLayout * boxLO = new QVBoxLayout();
        boxLO->addWidget(view);
        boxLO->addLayout(btnLO);

        QGroupBox * box = new QGroupBox(toUni("Редактор объектов"));
        box->setLayout(boxLO);

        QVBoxLayout * mainLO = new QVBoxLayout();
        mainLO->addWidget(box);
        setLayout(mainLO);
    }

    void MainWidget::makeConnections()
    {
        connect(addBtn,    &QPushButton::clicked,
                this,      &MainWidget::addItem);

        connect(delBtn,    &QPushButton::clicked,
                this,      &MainWidget::remItem);

        connect(editBtn,   &QPushButton::clicked,
                this,      &MainWidget::editItem);

        connect(view->selectionModel(),  &QItemSelectionModel::currentChanged,
                this,                    &MainWidget::onCurrentIndexChanged);
    }

    void MainWidget::updateButtons(const QModelIndex &current)
    {
        bool buttonsEnabled = false;

        if ( model->getObject(current) )
            buttonsEnabled = true;

        editBtn->setEnabled(buttonsEnabled);
        delBtn ->setEnabled(buttonsEnabled);
    }

    void MainWidget::selectItem(const int index)
    {
        view->selectionModel()->setCurrentIndex( model->fromListIndex(index),
                                                 QItemSelectionModel::Select );
    }

    void MainWidget::addItem()
    {
        if ( controller->addItem(this) )
        {
            selectItem( model->count()-1 );
        }
    }

    void MainWidget::editItem()
    {
        controller->editItem( this, view->currentIndex() );
    }

    void MainWidget::remItem()
    {
        if ( controller->remItem(this, view->currentIndex()) )
        {
            selectItem(0);
        }
    }

    void MainWidget::onCurrentIndexChanged(const QModelIndex &current,
                                                  const QModelIndex &previous)
    {
        Q_UNUSED(previous);
        updateButtons(current);
    }

    void MainWidget::setView()
    {
        view->setSelectionMode(QAbstractItemView::SingleSelection);

        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->verticalHeader()  ->setSectionResizeMode(QHeaderView::Stretch);

        view->horizontalHeader()->hide();
        view->verticalHeader()  ->hide();

        view->setItemDelegate(new AligningDelegate(view));

        selectItem(0);
    }
}
