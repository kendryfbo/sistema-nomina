#include "areamodel.h"

const QString TABLE_AREA = "area";
const QString TABLE_CLASIFICACION = "clasificacion";

AreaModel::AreaModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

AreaModel::AreaModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AreaModel::AreaModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AreaModel::~AreaModel()
{
    delete query;
}

bool AreaModel::insertArea(Area area)
{
    query->prepare("INSERT INTO "+TABLE_AREA+" ("
                   "codigo,descripcion,activo,fechacreac) VALUES ("
                   ":codigo,:descripcion,:activo,CURDATE())");

    query->bindValue(":codigo",area.getCodigo());
    query->bindValue(":descripcion",area.getDescripcion());
    query->bindValue(":activo",area.isActivo());

    if (!query->exec()){
        status = "Error al Insertar Área: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Área Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AreaModel::updateArea(Area area)
{
    query->prepare("UPDATE "+TABLE_AREA+" SET descripcion=:descripcion,activo=:activo WHERE codigo=:codigo");

    query->bindValue(":codigo",area.getCodigo());
    query->bindValue(":descripcion",area.getDescripcion());
    query->bindValue(":activo",area.isActivo());

    if (!query->exec()){
        status = "Error al Actualizar Área: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Área Actualizada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AreaModel::deleteArea(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_AREA+" WHERE codigo=:codigo");

    query->bindValue(":codigo",codigo);

    if (!query->exec()){
        status = "Error al Eliminar Área: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Área Eliminada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

Area AreaModel::FindArea(QString codigo)
{

    query->prepare("SELECT * FROM "+TABLE_AREA+" WHERE codigo=:codigo");
    query->bindValue(":codigo",codigo);

    if (!query->exec())
    {
        status = "Error al Buscar Área: " + query->lastError().text();
        debugMessage(status);
    }else if (!query->next())
    {
        status = "Area Codigo: "+codigo+" No existe.";
        debugMessage(status);
    }else
    {
        Area area(
                    query->value("codigo").toString(),
                    query->value("descripcion").toString(),
                    query->value("activo").toBool(),
                    query->value("fechacreac").toString()
                    );

        status = "Area código:"+codigo+" Encontrada...";
        debugMessage(status);

        return area;
    }
    return Area();
}

QSqlQuery AreaModel::findAreas(QString str, bool activo, Campo campo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT * FROM "+TABLE_AREA+" WHERE codigo LIKE ('"+str+"')";
    if (campo == Campo::descripcion)
        sql = "SELECT * FROM "+TABLE_AREA+" WHERE descripcion LIKE ('"+str+"')";
    if (activo)
        sql = sql + " AND activo=true";

     query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Área: " + query->lastError().text();
         debugMessage(status);
     }else {
         status = "Busqueda de Área Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

bool AreaModel::insertClasificacion(Clasificacion clasificacion)
{
    query->prepare("INSERT INTO "+TABLE_CLASIFICACION+" ("
                   "codigo,descripcion,cod_area,formapago,valor,activo,fechacreac) VALUES ("
                   ":codigo,:descripcion,:cod_area,:formapago,:valor,:activo,CURDATE())");

    query->bindValue(":codigo",clasificacion.getCodigo());
    query->bindValue(":descripcion",clasificacion.getDescripcion());
    query->bindValue(":cod_area",clasificacion.getArea());
    query->bindValue(":formapago",clasificacion.getFormaPago());
    query->bindValue(":valor",clasificacion.getValor());
    query->bindValue(":activo",clasificacion.isActivo());

    if (!query->exec()){
        status = "Error al Insertar Clasificación: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Clasificación Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AreaModel::updateClasificacione(Clasificacion clasificacion)
{
    query->prepare("UPDATE "+TABLE_CLASIFICACION+" SET "
                   "descripcion=:descripcion,cod_area=:cod_area,formapago=:formapago,"
                   "valor=:valor,activo=:activo WHERE codigo=:codigo");

    query->bindValue(":codigo",clasificacion.getCodigo());
    query->bindValue(":descripcion",clasificacion.getDescripcion());
    query->bindValue(":cod_area",clasificacion.getArea());
    query->bindValue(":formapago",clasificacion.getFormaPago());
    query->bindValue(":valor",clasificacion.getValor());
    query->bindValue(":activo",clasificacion.isActivo());

    if (!query->exec()){
        status = "Error al Actualizar Clasificación: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Clasificación Actualizada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AreaModel::deleteClasificacion(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_CLASIFICACION+" WHERE codigo=:codigo");

    query->bindValue(":codigo",codigo);

    if (!query->exec()){
        status = "Error al Eliminar Clasificación: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Clasificación Eliminada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AreaModel::clasificacionExiste(QString codigo)
{
    Clasificacion clasificacion(findClasificacion(codigo));
    if (clasificacion.getCodigo() == "")
        return false;
    else
        return true;
}

Clasificacion AreaModel::findClasificacion(QString codigo)
{
    query->prepare("SELECT * FROM "+TABLE_CLASIFICACION+" WHERE codigo=:codigo");
    query->bindValue(":codigo",codigo);

    if (!query->exec())
    {
        status = "Error al Buscar Clasificación: " + query->lastError().text();
        debugMessage(status);
    }else if (!query->next())
    {
        status = "Clasificación Codigo: "+codigo+" No existe.";
        debugMessage(status);
    }else
    {
        Clasificacion clasificacion(
                    query->value("codigo").toString(),
                    query->value("descripcion").toString(),
                    query->value("cod_area").toString(),
                    query->value("formapago").toString(),
                    query->value("valor").toDouble(),
                    query->value("activo").toBool(),
                    query->value("fechacreac").toString()
                    );

        status = "Clasificación código:"+codigo+" Encontrada...";
        debugMessage(status);

        return clasificacion;
    }
    return Clasificacion();
}

QSqlQuery AreaModel::findClasificaciones(QString str, QString area, Campo campo,bool activo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::codigo)
        sql = "SELECT codigo,descripcion,cod_area,formapago FROM "+TABLE_CLASIFICACION+" WHERE codigo LIKE ('"+str+"') AND cod_area LIKE('%"+area+"%') ";
    if (campo == Campo::descripcion)
        sql = "SELECT codigo,descripcion,cod_area,formapago FROM "+TABLE_CLASIFICACION+" WHERE descripcion LIKE ('"+str+"') AND cod_area LIKE('%"+area+"%') ";
    if (activo)
        sql = sql + " AND activo=true";

     query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Clasificación: " + query->lastError().text();
         debugMessage(status);
     }else {
         status = "Busqueda de Clasificación Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}
