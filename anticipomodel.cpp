#include "anticipomodel.h"

const QString TABLE_EMPLEADO = "empleado";
const QString TABLE_ANTICIPOTEMP = "anticipotemp";
const QString TABLE_ANTICIPO = "anticipo";
const QString TABLE_ANTICIPOVIEW = "anticipoview";
const QString TABLE_ANTICIPODETALLE = "anticipodetalle";
const QString TABLE_ANTICIPOTEMPVIEW = "anticipotempview";
const QString TABLE_ANTICIPODETALLEVIEW = "anticipodetalleview";

AnticipoModel::AnticipoModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

AnticipoModel::AnticipoModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AnticipoModel::AnticipoModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

AnticipoModel::~AnticipoModel()
{
    delete query;
}

bool AnticipoModel::generarAnticiposTemp(QString area, int dias, double porcentaje)
{
    EmpleadoModel empModel(conexion);
    QStringList listaDeCedulas = findCedulaEmpleadosFromArea(area);
    for (int i=0; i< listaDeCedulas.size(); i++)
    {
        Empleado emp = empModel.findEmpleado(listaDeCedulas[i]);
       double monto = calcAnticipo(emp,dias,porcentaje);
       if (!insertAnticipoTemporal(emp.getCedula(),monto))
           return false;
    }
    return true;
}

QSqlQuery AnticipoModel::findAnticipoTempView()
{
    query->prepare("SELECT * FROM "+TABLE_ANTICIPOTEMPVIEW);

    if (!query->exec())
    {
        status = "ERROR al buscar Anticipos Temporal view, Error: " +query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Anticipos temporal View exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QStringList AnticipoModel::findCedulaEmpleadosFromArea(QString area)
{
    QStringList cedulaList;

    query->prepare("SELECT * FROM "+TABLE_EMPLEADO+" WHERE cod_area=:area AND status=:status");
    query->bindValue(":status","ACTIVO");
    query->bindValue(":area",area);

    if (!query->exec())
    {
        status = "ERROR al buscar Cedula de Empleados en Area, Error: " +query->lastError().text();
        debugMessage(status);
    }
    while (query->next())
    {
        cedulaList << query->value("cedula").toString();
    }
    return cedulaList;
}

bool AnticipoModel::insertAnticipoDetalle(int id,QString cedula, double monto)
{
    query->prepare("INSERT INTO "+TABLE_ANTICIPODETALLE+" (id,cedula,monto,procesado) VALUES "
                                                             "(:id,:cedula,:monto,:procesado)");

    query->bindValue(":id",id);
    query->bindValue(":cedula",cedula);
    query->bindValue(":monto",monto);
    query->bindValue(":procesado",false);

    if (!query->exec())
    {
        status = "ERROR al insertar datos en Anticipo Detalle. ERROR: "+query->lastError().text();
        debugMessage(status);
        query->exec("ROLLBACK;");
        return false;
    } else
    {
        status = "Anticipo detalle Insertado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AnticipoModel::updateAnticipoDetalle(int id, QString cedula, bool procesado)
{
    query->prepare("UPDATE "+TABLE_ANTICIPOTEMP+" SET procesado=:procesado WHERE cedula=:cedula AND id=:id");

    query->bindValue(":cedula",cedula);
    query->bindValue(":id",id);
    query->bindValue(":procesado",procesado);

    if (!query->exec())
    {
        status = "ERROR al Actualizar Anticipo Detalle, Error: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status = "Anticipo detalle Actualizado exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AnticipoModel::deleteAnticipo(int anticipoId)
{
    query->prepare("DELETE FROM "+TABLE_ANTICIPO+" WHERE id=:id");

    query->bindValue(":id",anticipoId);

    if (!query->exec())
    {
        status = "ERROR al Eliminar Anticipo. Error: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status = "Anticipo Eliminado exitosamente...";
        debugMessage(status);
        return true;
    }
}

double AnticipoModel::calcAnticipo(Empleado emp, int dias, double porcentaje)
{
    double anticipo = (emp.getSalarioDia() * dias) * (porcentaje/100);
    return anticipo;
}

bool AnticipoModel::insertAnticipoTemporal(QString cedula, double valor)
{
    query->prepare("INSERT INTO "+TABLE_ANTICIPOTEMP+" (cedula,monto) VALUES (:cedula,:monto)");

    query->bindValue(":cedula",cedula);
    query->bindValue(":monto",valor);

    if (!query->exec())
    {
        status = "ERROR al Insertar Anticipo temporal, Error: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status = "Anticipo temporal insertado exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AnticipoModel::updateAnticipoTemp(QString cedula, double valor)
{
    query->prepare("UPDATE "+TABLE_ANTICIPOTEMP+" SET monto=:monto WHERE cedula=:cedula");

    query->bindValue(":cedula",cedula);
    query->bindValue(":monto",valor);

    if (!query->exec())
    {
        status = "ERROR al Actualizar Anticipo temporal, Error: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status = "Anticipo temporal Actualizado exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool AnticipoModel::clearAnticipoTemp()
{
    query->prepare("TRUNCATE TABLE "+TABLE_ANTICIPOTEMP);

    if (!query->exec())
    {
        status = "ERROR al Vaciar Anticipo temporal, Error: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status = "Anticipo temporal Vaciado exitosamente...";
        debugMessage(status);
        return true;
    }

}

bool AnticipoModel::insertAnticipo(QString descripcion,QString area,int dias,double porcentaje)
{
    int idAnticipo = 0;
    query->exec("START TRANSACTION;");

    query->prepare("INSERT INTO "+TABLE_ANTICIPO+" (descripcion,area,dias,porcentaje,fecha) VALUES"
                                    "(:descripcion,:area,:dias,:porcentaje,CURDATE())");

    query->bindValue(":descripcion",descripcion);
    query->bindValue(":area",area);
    query->bindValue(":dias",dias);
    query->bindValue(":porcentaje",porcentaje);

    if (!query->exec())
    {
        status = "Error al Insertar Anticipo. Error: "+query->lastError().text();
        debugMessage(status);
        query->exec("ROLLBACK;");
        return false;
    }

    idAnticipo = query->lastInsertId().toInt();

    QSqlQuery tempQuery(conexion.db);
    tempQuery.prepare("SELECT * FROM "+TABLE_ANTICIPOTEMP);

    if (!tempQuery.exec())
    {
        status = "Error al Buscar Lista de Anticipos Temporales. Error: "+tempQuery.lastError().text();
        debugMessage(status);
        query->exec("ROLLBACK;");
    } else
    {
        while (tempQuery.next())
        {
           QString cedula = tempQuery.value("cedula").toString();
           double monto = tempQuery.value("monto").toInt();
           if (!insertAnticipoDetalle(idAnticipo,cedula,monto))
           {
               return false;
               break;
           }
        }
    }
    query->exec("COMMIT;");
    return true;
}

QSqlQuery AnticipoModel::findAnticiposView(QString descripcion)
{

    query->prepare("SELECT * FROM "+TABLE_ANTICIPOVIEW+" WHERE descripcion LIKE('%"+descripcion+"%')");
    if (!query->exec())
    {
        status = "ERROR al realizar busqueda de Anticipos View. ERROR: "+query->lastError().text();
        debugMessage(status);
    } else
        status = "Busqueda de Anticipos View Realizada exitosamente...";
        debugMessage(status);
        return *query;
}

QSqlQuery AnticipoModel::findAnticiposEmpleado(QString cedula, bool procesado)
{
    cedula = "%"+cedula+"%";

    query->prepare("SELECT * FROM "+TABLE_ANTICIPODETALLEVIEW+" WHERE cedula LIKE(:cedula) AND procesado=:procesado");

    query->bindValue(":cedula",cedula);
    query->bindValue(":procesado",procesado);

    if (!query->exec())
    {
        status = "ERROR al realizar busqueda de Anticipos de empleados. ERROR: "+query->lastError().text();
        debugMessage(status);
    } else
        status = "Busqueda de Anticipos de Empleados Realizada exitosamente...";
        debugMessage(status);
        debugMessage(query->executedQuery());
        return *query;
}

