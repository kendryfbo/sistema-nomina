#include "mainwindow.h"
#include <QApplication>


#include "deduccionwidget.h"
#include "empleado.h"
#include "empleadomodel.h"
#include "deduccion.h"
#include "deduccionmodel.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;
    login.show();
/*
    DeduccionWidget deduccionW;
    deduccionW.show();
*/
/*
    Empleado emp;
    EmpleadoModel model("test","127.0.0.1","nomina","root","19017070",3306);
    model.insertEmpleado(emp);
    model.updateEmpleado(emp);

    Deduccion deduccion;
    DeduccionModel modelD("test","127.0.0.1","nomina","root","19017070",3306);
    deduccion.setValor(50.40);
    modelD.DeleteDeduccion(deduccion.getCodigo());
*/
    //modelD.updateDeduccion(deduccion);
    //modelD.insertDeduccion(deduccion);

    //MainWindow w;
    //w.show();

    return a.exec();
}
