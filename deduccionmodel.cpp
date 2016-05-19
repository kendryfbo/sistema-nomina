#include "deduccionmodel.h"

const QString TABLE_DEDUCCION = "deduccionconcepto";
const QString TABLE_FORMA = "forma";
const QString TABLE_FORMULA = "deduccionformula";



DeduccionModel::DeduccionModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

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
                                      "codigo,descripcion,forma,valor,formula,activo,fechacreac) "
                                      "Values (:codigo,:descripcion,:forma,:valor,:formula,:activo,CURDATE());");

    query->bindValue(":codigo",deduccion.getCodigo());
    query->bindValue(":descripcion",deduccion.getDescripcion());
    query->bindValue(":forma",deduccion.getForma());
    query->bindValue(":valor",deduccion.getValor());
    query->bindValue(":formula",deduccion.getFormula());
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
                                  "descripcion=:descripcion,forma=:forma,valor=:valor,formula=:formula,activo=:activo "
                                  "WHERE codigo=:codigo;");

    query->bindValue(":codigo",deduccion.getCodigo());
    query->bindValue(":descripcion",deduccion.getDescripcion());
    query->bindValue(":forma",deduccion.getForma());
    query->bindValue(":valor",deduccion.getValor());
    query->bindValue(":formula",deduccion.getFormula());
    query->bindValue(":activo",deduccion.isActivo());

    if (!query->exec()){
        status = "Error al Actualizar Concepto de Deducción: " + query->lastError().text();
        debugMessage(status);
        //debugMessage(query->executedQuery());
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

bool DeduccionModel::deduccionExist(QString codigo)
{
    Deduccion deduccion(findDeduccion(codigo));

    if (deduccion.getCodigo() == "")
        return false;
    else
        return true;
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
                            query->value("formula").toString(),
                            query->value("fechacreac").toString(),
                            query->value("activo").toBool());

        status = "Deducción código:"+codigo+" Encontrada...";
        debugMessage(status);
    }
    return deduccion;
}

QSqlQuery DeduccionModel::findDeducciones(QString str,bool activo, DeduccionModel::Campo campo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT codigo,descripcion,forma,valor FROM "+TABLE_DEDUCCION+" WHERE codigo LIKE ('"+str+"')";
    if (campo == Campo::descripcion)
        sql = "SELECT codigo,descripcion,forma,valor FROM "+TABLE_DEDUCCION+" WHERE descripcion LIKE ('"+str+"')";
    if (activo)
        sql = sql + " AND activo=true";

     query->prepare(sql);

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

QSqlQuery DeduccionModel::findForma(QString str, bool activo, DeduccionModel::Campo campo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT * FROM "+TABLE_FORMA+" WHERE codigo LIKE ('"+str+"')";
     if (campo == Campo::descripcion)
        sql = "SELECT * FROM "+TABLE_FORMA+" WHERE descripcion LIKE ('"+str+"')";
    if (activo)
        sql = sql + " AND activo=true";

    query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Forma de Deducción: " + query->lastError().text();
         debugMessage(status);
     }else {
         status = "Busqueda de Forma de Deducción Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

QStringList DeduccionModel::findFormulas(QString str, bool activo, DeduccionModel::Campo campo, bool ini, bool fin)
{
    QString sql;
    QStringList list;
    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT descripcion FROM "+TABLE_FORMULA+" WHERE codigo LIKE ('"+str+"')";
     if (campo == Campo::descripcion)
        sql = "SELECT descripcion FROM "+TABLE_FORMULA+" WHERE descripcion LIKE ('"+str+"')";
    if (activo)
        sql = sql + " AND activo=true";

    query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Formula de Deducción: " + query->lastError().text();
         debugMessage(status);
         debugMessage(query->executedQuery());
     }else{
         debugMessage(query->executedQuery());
         while (query->next()){
             list << query->value("descripcion").toString();
         }

         status = "Busqueda de Formula de Deducción Realizada Exitosamente...";
         debugMessage(status);
     }
     return list;
}

