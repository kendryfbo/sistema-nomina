#include "aportefaovmodel.h"


const QString TABLE_APORTEPREST = "aporteprestacion";
const QString TABLE_APORTEPRESTVIEW = "aporteprestacionview";
const QString TABLE_APORTEPRESTRESUMVIEW = "aporteprestacionresumview";

AporteFaovModel::AporteFaovModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}
AporteFaovModel::AporteFaovModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);

}

AporteFaovModel::AporteFaovModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AporteFaovModel::~AporteFaovModel()
{
    delete query;
}


bool AporteFaovModel::insertAporte(QString cedulaEmp, QString descripcion, double aporte, double nominaNum)
{
    query->prepare("INSERT INTO "+TABLE_APORTEPREST+" (numero,ced_empleado,descripcion,aporte,fecha_creac)"
                                                   " VALUES (NULL,:ced_empleado,:descripcion,:aporte,CURDATE())");
    query->bindValue(":ced_empleado",cedulaEmp);
    query->bindValue(":descripcion",descripcion);
    query->bindValue(":aporte",aporte);
    query->bindValue(":nomina",nominaNum);

    if (!query->exec())
    {
        status = "Error al Insertar Aporte de Prestacion ERROR: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Aporte de Prestacion Insertado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AporteFaovModel::updateAporte(int numeroAporte, QString cedulaEmp, QString descripcion, double aporte, double nominaNum)
{
    query->prepare("UPDATE "+TABLE_APORTEPREST+" SET ,descripcion=:descripcion,ced_empleado=:ced_empleado,,aporte=:aporte, fecha_creac=CURDATE())"
                                              " WHERE numero=:numero AND cedula=:cedula");

    query->bindValue(":numero",numeroAporte);
    query->bindValue(":ced_empleado",cedulaEmp);
    query->bindValue(":descripcion",descripcion);
    query->bindValue(":aporte",aporte);
    query->bindValue(":nomina",nominaNum);

    if (!query->exec())
    {
        status = "Error al Actualizar Aporte de Prestacion. ERROR: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Aporte de Faov Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AporteFaovModel::deleteAporte(int numeroAporte, QString cedulaEmp)
{
    query->prepare("DELETE FROM "+TABLE_APORTEPREST+" WHERE numero=:numero AND ced_empleado=:ced_empleado");

    query->bindValue(":numero",numeroAporte);
    query->bindValue(":ced_empleado",cedulaEmp);

    if (!query->exec())
    {
        status = "Error al Eliminar Aporte de Prestacion. ERROR: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Aporte de Faov Eliminado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

QSqlQuery AporteFaovModel::findAportesEmpleado(QString cedulaEmp)
{
    query->prepare("SELECT * FROM "+TABLE_APORTEPREST+" WHERE ced_empleado=:ced_empleado");

    query->bindValue(":ced_empleado",cedulaEmp);

    if (!query->exec())
    {
        status = "Error al Buscar Aporte de Prestacion empleado. ERROR: " + query->lastError().text();
        debugMessage(status);
    } else if (!query->next())
    {
        status = "Empleado no posee Aporte de Prestacion.";
        debugMessage(status);

    } else {
        status = "Busqueda de Aporte de Prestacion Empleado Realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}
