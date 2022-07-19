#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameObjectsEditor::MainWidget editor;
    editor.show();

    return a.exec();
}
