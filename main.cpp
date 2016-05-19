#include "mainwindow.h"
#include <QApplication>

#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;
    if (login.exec() != QDialog::Accepted){
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
