#include "asignacionmodel.h"

const QString TABLE_ASIGNACION = "asignacionconcepto";

AsignacionModel::AsignacionModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
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
                                      "codigo,descripcion,forma,valor,cod_campo) "
                                      "Values (:codigo,:descripcion,:forma,:valor);");

    query->bindValue(":codigo",asignacion.getCodigo());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":forma",asignacion.getForma());
    query->bindValue(":valor",asignacion.getValor());

    if (!query->exec()){
        status = "Error al Insertar Concepto de Asignacion: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de asignacion Insertado Exitosamente...";
        debugMessage(status);
        return true;
        }
}

bool AsignacionModel::updateAsignacion(Asignacion asignacion)
{

    query->prepare("UPDATE "+TABLE_ASIGNACION+" SET "
                                  "descripcion=:descripcion,forma=:forma,valor=:valor "
                                  "WHERE codigo=:codigo;");

    query->bindValue(":codigo",asignacion.getCodigo());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":forma",asignacion.getForma());
    query->bindValue(":valor",asignacion.getValor());

    if (!query->exec()){
        status = "Error al Actualizar Concepto de Asignacion: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignacion Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AsignacionModel::DeleteAsignacion(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_ASIGNACION+" WHERE codigo='"+codigo+"';");

    if (!query->exec()){
        status = "Error al Eliminar Concepto de Asignacion: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignacion Eliminado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

