#ifndef APORTEFAOVMODEL_H
#define APORTEFAOVMODEL_H

#include "model.h"

class AporteFaovModel : public Model
{
public:
    // CONSTRUCTORS
    AporteFaovModel(connDB conn);
    AporteFaovModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    AporteFaovModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    //DESTRUCTOR
    ~AporteFaovModel();


    // MODULO - REGISTRO DE APORTE DE PRESTACIONES SOCIALES
    bool insertAporte(QString cedulaEmp,QString descripcion,double aporte,double nominaNum = 0);
    bool updateAporte(int numeroAporte,QString cedulaEmp,QString descripcion,double aporte, double nominaNum = 0);
    bool deleteAporte(int numeroAporte,QString cedulaEmp);

    QSqlQuery findAportesEmpleado(QString cedulaEmp);
    QSqlQuery findResumAporteEmpleado(QString cedulaEmp);
};

#endif // APORTEFAOVMODEL_H
