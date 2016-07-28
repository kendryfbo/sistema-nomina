#ifndef ANTICIPOMODEL_H
#define ANTICIPOMODEL_H

#include <QString>
#include <QStandardItemModel>

#include "model.h"
#include "empleadomodel.h"

class AnticipoModel : public Model
{
     friend class EmpleadoModel;

public:
    AnticipoModel(connDB conn);
    AnticipoModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    AnticipoModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~AnticipoModel();

    bool generarAnticiposTemp(QString area,int dias,double porcentaje);
    QSqlQuery findAnticipoTempView();
    bool insertAnticipoTemporal(QString cedula,double valor);
    bool updateAnticipoTemp(QString cedula,double valor);
    bool clearAnticipoTemp();


    bool insertAnticipo(QString descripcion,QString area,int dias=0,double porcentaje=100);
    bool updateAnticipoDetalle(int id,QString cedula,bool procesado);
    bool deleteAnticipo(int anticipoId);

    QSqlQuery findAnticiposView(QString descripcion="");
    QSqlQuery findAnticiposEmpleado(QString cedula="",bool procesado=false);

    QStringList findEmpleadosFromAnticipo(int anticipoID);

private:

    QStringList findCedulaEmpleadosFromArea(QString area);
    bool insertAnticipoDetalle(int id,QString cedula,double monto);
    bool insertDediccionAnticipo();
    double calcAnticipo (Empleado emp,int dias,double porcentaje);

    QSqlQuery* query;
};

#endif // ANTICIPOMODEL_H
