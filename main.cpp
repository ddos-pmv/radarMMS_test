#include <QApplication>
#include <QDebug>

#include  "include/MainWindow.h"
#include "include/InterfaceManager.h"
#include "include/InputDialog.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    MainWindow window;
    window.setMinimumSize(800,600);
    window.show();

    InputDialog inputDialog;
    inputDialog.show();


    return QCoreApplication::exec();
}
