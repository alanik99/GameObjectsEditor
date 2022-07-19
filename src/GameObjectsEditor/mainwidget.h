#pragma once

#include <QWidget>

class QTableView;
class QPushButton;

namespace GameObjectsEditor
{
    class Model;
    class Controller;

    //!
    //! \brief The MainWidget class Редактор библиотеки игровых объектов
    //!
    class MainWidget : public QWidget
    {
        Q_OBJECT

    public:
        MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

    private slots:
        void addItem();
        void editItem();
        void remItem();
        void onCurrentIndexChanged(const QModelIndex &current,
                                   const QModelIndex &previous);
    private:
        void setView();
        void initLayout();
        void makeConnections();
        void updateButtons(const QModelIndex &current);
        inline void selectItem(const int index);

        QTableView * view;
        Controller * controller;
        Model      * model;

        QPushButton * addBtn;
        QPushButton * editBtn;
        QPushButton * delBtn;
    };
}
