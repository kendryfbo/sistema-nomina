#ifndef EMPLEADOMODEL_H
#define EMPLEADOMODEL_H

#include <QtSql>
#include <QDebug>
#include <QString>

#include "model.h"
#include "empleado.h"

class EmpleadoModel : public Model
{
public:
    EmpleadoModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    EmpleadoModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~EmpleadoModel();

    bool insertEmpleado(Empleado empleado);
    bool updateEmpleado(Empleado empleado);

    bool InsertDeducible(QString codDeducible,QString cedulaEmp);
private:

};

#endif // EMPLEADOMODEL_H
