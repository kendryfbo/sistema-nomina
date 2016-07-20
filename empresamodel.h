#ifndef EMPRESAMODEL_H
#define EMPRESAMODEL_H

#include <QString>

#include "model.h"

class EmpresaModel : public Model
{
public:

    struct Empresa{
        QString descripcion;
        QString rif;
        QString direccion;
        QString tlf1;
        QString tlf2;
        QString director;
        QString cedula;
        QString logo;
        QString mensaje;
    };

    EmpresaModel(connDB conn);
    EmpresaModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    EmpresaModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~EmpresaModel();

    update(Empresa empresa);

    Empresa findEmpresa();


};

#endif // EMPRESAMODEL_H
