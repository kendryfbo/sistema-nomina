#ifndef EMPLEADOMODEL_H
#define EMPLEADOMODEL_H

#include <QtCore>
#include <QtSql>
#include <QDebug>
#include <QString>

#include "deduccionmodel.h"
#include "asignacionmodel.h"
#include "model.h"
#include "empleado.h"
#include "areamodel.h"

class EmpleadoModel : public Model
{
    friend class AreaModel;

public:

    enum Campo {cedula,nombre,apellido};
    enum Campo2 {codigo,descripcion};
    enum Status {general,activo,inactivo,vacacion,reposo};
    enum Tipo{fija,eventual};

    EmpleadoModel(connDB conn);
    EmpleadoModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    EmpleadoModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~EmpleadoModel();

    bool insertEmpleado(Empleado empleado);
    bool updateEmpleado(Empleado empleado);
    bool deleteEmpleado(QString cedula);

    bool empleadoExist(QString cedula);
    Empleado findEmpleado(QString cedula);
    QSqlQuery findEmpleados(QString str = "", Campo campo = Campo::cedula, Status empStatus=Status::general, bool ini = true , bool fin = true);

    bool insertDeduccion(QString codigo,QString cedulaEmp, QString tipo, int cantidad=1);
    bool eliminarDeduccion(QString codigo, QString cedulaEmp);
    QSqlQuery findDeduccion(QString codigo,QString cedulaEmp);
    QSqlQuery findDeducciones(QString cedulaEmp, QString deduccion = "", Tipo tipo = Tipo::fija, bool ini = true , bool fin = true);

    bool insertAsignacion(QString codigo,QString cedulaEmp, QString tipo, int cantidad=1);
    bool eliminarAsignacion(QString codigo, QString cedulaEmp);
    QSqlQuery findAsignacion(QString codigo,QString cedulaEmp);
    QSqlQuery findAsignaciones(QString cedulaEmp, QString asignacion = "", Tipo tipo = Tipo::fija, bool ini = true ,bool fin = true);

    //FALTA POR DETERMIANR SI EXISTIRA UNA TABLA DE DETALLE DE NOMINA DONDE APAREZCA EL EMPLEADO.
    QSqlQuery findNominaProcesada(QString cedulaEmp, QString str = "", bool ini = true ,bool fin = true);


    QSqlQuery findAreas();
    Clasificacion findClasificacion(QString codigo);
    QSqlQuery findClasificaciones(QString area);


    // MODULO - REGISTRO DE APORTE DE PRESTACIONES SOCIALES

    bool insertAporte(QString cedulaEmp,QString descripcion,double aporte);
    bool updateAporte(int numeroAporte,QString cedulaEmp,QString descripcion,double aporte);
    bool deleteAporte(int numeroAporte,QString cedulaEmp);

    QSqlQuery findAportesEmpleado(QString cedulaEmp);
    QSqlQuery findResumAporteEmpleado(QString cedulaEmp);



private:

};

#endif // EMPLEADOMODEL_H
