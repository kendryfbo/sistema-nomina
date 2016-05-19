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

    enum class Campo{codigo,descripcion};
    AsignacionModel(connDB conn);
    AsignacionModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    AsignacionModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

     ~AsignacionModel();

    bool insertAsignacion(Asignacion deduccion);
    bool updateAsignacion(Asignacion deduccion);
    bool DeleteAsignacion(QString  codigo);


    bool asignacionExist(QString codigo);
    Asignacion findAsignacion(QString codigo);
    QSqlQuery findAsignaciones(QString str = "", bool activo=true, Campo campo = Campo::descripcion,bool ini = true ,bool fin = true);

    QSqlQuery findForma(QString str = "", bool activo=true, Campo campo = Campo::descripcion, bool ini = true , bool fin = true);

    QStringList findFormulas(QString str = "", bool activo=true, Campo campo = Campo::descripcion, bool ini = true , bool fin = true);


};
#endif // ASIGNACIONMODEL_H
