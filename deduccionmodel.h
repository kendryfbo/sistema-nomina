#ifndef DEDUCCIONMODEL_H
#define DEDUCCIONMODEL_H

#include <QtSql>
#include <QString>
#include <QDebug>

#include "model.h"
#include "deduccion.h"

class DeduccionModel : public Model
{
public:

    enum class Campo{codigo,descripcion};

    DeduccionModel(connDB conn);
    DeduccionModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    DeduccionModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

     ~DeduccionModel();

    bool insertDeduccion(Deduccion deduccion);
    bool updateDeduccion(Deduccion deduccion);
    bool DeleteDeduccion(QString  codigo);

    bool deduccionExist(QString codigo);
    Deduccion findDeduccion(QString codigo);
    QSqlQuery findDeducciones(QString str = "", bool activo=true, Campo campo = Campo::descripcion,bool ini = true ,bool fin = true);

    QSqlQuery findForma(QString str = "", bool activo=true, Campo campo = Campo::descripcion, bool ini = true , bool fin = true);

    QStringList findFormulas(QString str = "", bool activo=true, Campo campo = Campo::descripcion, bool ini = true , bool fin = true);

};

#endif // DEDUCCIONMODEL_H
