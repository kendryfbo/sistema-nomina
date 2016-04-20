#include "deduccionmodel.h"

const QString TABLE_DEDUCCION = "deduccionconcepto";


DeduccionModel::DeduccionModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}
DeduccionModel::DeduccionModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    debug = true;
    connect();
    query = new QSqlQuery(conexion.db);
}

DeduccionModel::~DeduccionModel()
{
    delete query;
}

bool DeduccionModel::insertDeduccion(Deduccion deduccion)
{
    query->prepare("INSERT INTO "+TABLE_DEDUCCION+" ("
                                      "codigo,descripcion,forma,valor,activo,fechacreac) "
                                      "Values (:codigo,:descripcion,:forma,:valor,:activo,CURDATE());");

    query->bindValue(":codigo",deduccion.getCodigo());
    query->bindValue(":descripcion",deduccion.getDescripcion());
    query->bindValue(":forma",deduccion.getForma());
    query->bindValue(":valor",deduccion.getValor());
    query->bindValue(":activo",deduccion.isActivo());

    if (!query->exec()){
        status = "Error al Insertar Concepto de Deducción: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Deducción Insertado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool DeduccionModel::updateDeduccion(Deduccion deduccion)
{

    query->prepare("UPDATE "+TABLE_DEDUCCION+" SET "
                                  "descripcion=:descripcion,forma=:forma,valor=:valor,activo=:activo "
                                  "WHERE codigo=:codigo;");

    query->bindValue(":codigo",deduccion.getCodigo());
    query->bindValue(":descripcion",deduccion.getDescripcion());
    query->bindValue(":forma",deduccion.getForma());
    query->bindValue(":valor",deduccion.getValor());
    query->bindValue(":activo",deduccion.isActivo());

    if (!query->exec()){
        status = "Error al Actualizar Concepto de Deducción: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Deducción Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool DeduccionModel::DeleteDeduccion(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_DEDUCCION+" WHERE codigo='"+codigo+"';");

    if (!query->exec()){
        status = "Error al Eliminar Concepto de Deducción: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Deducción Eliminado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

Deduccion DeduccionModel::findDeduccion(QString codigo)
{
    Deduccion deduccion;

    query->prepare("SELECT * FROM "+TABLE_DEDUCCION+" WHERE codigo ='"+codigo+"'");

    if(!query->exec())
    {
        status = "Error al buscar Deducción código:"+codigo+" :" + query->lastError().text();
        debugMessage(status);
    } else if (!query->next()){
        status = "Deducción código:"+codigo+" No existe";
        debugMessage(status);
    } else {
        deduccion  = Deduccion(query->value("codigo").toString(),
                            query->value("descripcion").toString(),
                            query->value("forma").toString(),
                            query->value("valor").toDouble(),
                            query->value("fechacreac").toString(),
                            query->value("activo").toBool());

        status = "Deducción código:"+codigo+" Encontrada...";
        debugMessage(status);
    }
    return deduccion;
}

QSqlQuery DeduccionModel::findDeducciones(QString str, DeduccionModel::Campo campo, bool ini, bool fin)
{
    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        query->prepare("SELECT codigo,descripcion FROM "+TABLE_DEDUCCION+" WHERE codigo LIKE ('"+str+"')");
     if (campo == Campo::descripcion)
         query->prepare("SELECT codigo,descripcion FROM "+TABLE_DEDUCCION+" WHERE descripcion LIKE ('"+str+"')");

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Deducción: " + query->lastError().text();
         debugMessage(status);
         //debugMessage(query->executedQuery());
     }else {
         status = "Busqueda de Deducción Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

