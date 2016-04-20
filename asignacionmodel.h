#ifndef ASIGNACIONMODEL_H
#define ASIGNACIONMODEL_H

#include <QtSql>
#include <QString>
#include <QDebug>

#include "model.h"
#include "asignacion.h"

class AsignacionModel : public Model
{
public:

    AsignacionModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    AsignacionModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

     ~AsignacionModel();

    bool insertAsignacion(Asignacion deduccion);
    bool updateAsignacion(Asignacion deduccion);
    bool DeleteAsignacion(QString  codigo);
};
#endif // ASIGNACIONMODEL_H
