#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    auto path = app.applicationDirPath();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}