#include "asignacionmodel.h"

const QString TABLE_ASIGNACION = "asignacionconcepto";
const QString TABLE_FORMA = "forma";
const QString TABLE_FORMULA = "asignacionformula";

AsignacionModel::AsignacionModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

AsignacionModel::AsignacionModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AsignacionModel::AsignacionModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    debug = true;
    connect();
    query = new QSqlQuery(conexion.db);
}

AsignacionModel::~AsignacionModel()
{
    delete query;
}

bool AsignacionModel::insertAsignacion (Asignacion asignacion)
{

    query->prepare("INSERT INTO "+TABLE_ASIGNACION+" ("
                                      "codigo,descripcion,forma,valor,prima,activo,fechacreac) "
                                      "Values (:codigo,:descripcion,:forma,:valor,:prima,:activo,CURDATE());");

    query->bindValue(":codigo",asignacion.getCodigo());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":forma",asignacion.getForma());
    query->bindValue(":valor",asignacion.getValor());
    query->bindValue(":prima",asignacion.hasPrima());
    query->bindValue(":activo",asignacion.isActivo());

    if (!query->exec()){
        status = "Error al Insertar Concepto de Asignación: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignación Insertado Exitosamente...";
        debugMessage(status);
        return true;
        }
}

bool AsignacionModel::updateAsignacion(Asignacion asignacion)
{

    query->prepare("UPDATE "+TABLE_ASIGNACION+" SET "
                                  "descripcion=:descripcion,forma=:forma,valor=:valor,formula=:formula,prima=:prima,activo=:activo "
                                  "WHERE codigo=:codigo;");

    query->bindValue(":codigo",asignacion.getCodigo());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":forma",asignacion.getForma());
    query->bindValue(":valor",asignacion.getValor());
    query->bindValue(":formula",asignacion.getFormula());
    query->bindValue(":prima",asignacion.hasPrima());
    query->bindValue(":activo",asignacion.isActivo());

    if (!query->exec()){
        status = "Error al Actualizar Concepto de Asignación: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignación Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AsignacionModel::DeleteAsignacion(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_ASIGNACION+" WHERE codigo='"+codigo+"';");

    if (!query->exec()){
        status = "Error al Eliminar Concepto de Asignación: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignación Eliminado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AsignacionModel::asignacionExist(QString codigo)
{
    Asignacion asignacion(findAsignacion(codigo));
    if (asignacion.getCodigo() == "")
        return false;
    else
        return true;
}

Asignacion AsignacionModel::findAsignacion(QString codigo)
{
    Asignacion asignacion;

    query->prepare("SELECT * FROM "+TABLE_ASIGNACION+" WHERE codigo =:codigo");
    query->bindValue(":codigo",codigo);
    if(!query->exec())
    {
        status = "Error al buscar Asignación código:"+codigo+" :" + query->lastError().text();
        debugMessage(status);
    } else if (!query->next()){
        status = "Asignación código:"+codigo+" No existe";
        debugMessage(status);
    } else {
        asignacion  = Asignacion(query->value("codigo").toString(),
                            query->value("descripcion").toString(),
                            query->value("forma").toString(),
                            query->value("valor").toDouble(),
                            query->value("formula").toString(),
                            query->value("prima").toBool(),
                            query->value("activo").toBool(),
                            query->value("fechacreac").toString());

        status = "Asignación código:"+codigo+" Encontrada...";
        debugMessage(status);
    }
    return asignacion;
}

QSqlQuery AsignacionModel::findAsignaciones(QString str, bool activo, AsignacionModel::Campo campo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT codigo,descripcion,forma,valor FROM "+TABLE_ASIGNACION+" WHERE codigo LIKE ('"+str+"')";
    if (campo == Campo::descripcion)
        sql = "SELECT codigo,descripcion,forma,valor FROM "+TABLE_ASIGNACION+" WHERE descripcion LIKE ('"+str+"')";
    if (activo)
        sql = sql + " AND activo=true";

     query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Asignación: " + query->lastError().text();
         debugMessage(status);
         //debugMessage(query->executedQuery());
     }else {
         status = "Busqueda de Asignación Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

QSqlQuery AsignacionModel::findForma(QString str, bool activo, AsignacionModel::Campo campo, bool ini, bool fin)
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
         status = "Error al Realizar Busqueda de Forma de Asignación: " + query->lastError().text();
         debugMessage(status);
     }else {
         status = "Busqueda de Forma de Asignación Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

QStringList AsignacionModel::findFormulas(QString str, bool activo, AsignacionModel::Campo campo, bool ini, bool fin)
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
         status = "Error al Realizar Busqueda de Formula de Asignación: " + query->lastError().text();
         debugMessage(status);
         debugMessage(query->executedQuery());
     }else{
         while (query->next()){
             list << query->value("descripcion").toString();
         }
         status = "Busqueda de Formula de Asignación Realizada Exitosamente...";
         debugMessage(status);
     }
     return list;
}

