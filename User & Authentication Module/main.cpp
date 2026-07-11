#include "applicationmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    applicationmanager appManager;
    appManager.initialize();

    return a.exec();
}