#include <QtGui/QApplication>
#include "mainwindow.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    
    a.setStyleSheet(
        "QToolBox::tab {"
        " background-color: rgb(90,90, 90);"
        " color: rgb(255, 255, 255);"
        "}"
        ""
        "QToolBox {"
        " background-color: white;"
        "}"
        ""
        "QWidget#toolContainer {"
        " background-color: white;"
        "}"
        
        );

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return a.exec();
}
