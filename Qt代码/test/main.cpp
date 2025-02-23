#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog L;
    L.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
