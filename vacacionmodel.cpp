#include "vacacionmodel.h"

// CONSTANTES

// Nombres de Tablas

//**Vacaciones Cargadas**//
const QString TABLE_VACACIONCARGADA = "vacacioncargada";
const QString TABLE_VACACIONDEDUCCTEMP = "vacaciondeducctemp";
const QString TABLE_VACACIONCARGADADETALLE = "vacacioncargadadetalle";
const QString TABLE_VACACIONCARGADADEDUCCION = "vacacioncargadadeduccion";
//**Vacaciones Procesadas**//
const QString TABLE_VACACIONPROCESADA = "vacacionprocesada";
const QString TABLE_VACACIONPROCESADADETALLE = "vacacionprocesadadetalle";
const QString TABLE_VACACIONPROCESADADEDUCCION = "vacacionprocesadadeduccion";

// Nombres de Vistas

//**Vacaciones Cargadas**//
const QString TABLEVIEW_VACACIONCARGADADETALLERESUMVIEW = "vacacioncargadadetalleresumview";
const QString TABLEVIEW_VACACIONCARGADARESUMVIEW = "vacacioncargadaresumview";
//**Vacaciones Procesadas**//
const QString TABLEVIEW_VACACIONPROCESADADETALLERESUMVIEW = "vacacionprocesadadetalleresumview";
const QString TABLEVIEW_VACACIONPROCESADARESUMVIEW = "vacacionprocesadaresumview";


VacacionModel::VacacionModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

VacacionModel::VacacionModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

VacacionModel::VacacionModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    debug = true;
    connect();
    query = new QSqlQuery(conexion.db);
}

VacacionModel::~VacacionModel()
{
    delete query;
}

bool VacacionModel::generateVacacion(Vacacion vacacion, int diasBono, int diasAjuste)
{
    startTransaction();

    if (!insertVacacionCargada(vacacion))
    {
        status = "ERROR al Generar vacacion:"+status;
        debugMessage(status);
        rollBack();
        return false;
    }

    vacacion = findVacacionCargada(query->lastInsertId().toInt());

    if (!insertVacacionCargadaDetalles(vacacion,diasBono,diasAjuste))
    {
        status = "ERROR al Generar vacacion:"+status;
        debugMessage(status);
        rollBack();
        return false;
    }

    // falta insertar deducciones

    Commit();
    return true;
}

bool VacacionModel::insertDeduccionEnVacacion(QString deduccionCod, int cantidad)
{
    query->prepare("INSERT INTO "+TABLE_VACACIONDEDUCCTEMP+" (cod_deduccion,cantidad) VALUES "
                                   "(:codigo,:cantidad)");

    query->bindValue(":codigo",deduccionCod);
    query->bindValue(":cantidad",cantidad);

    if (!query->exec())
    {
        status= "ERROR al insertar Deduccón temporal en Vacacion. ERROR: "+ query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status= "Deducción temporal en Vacacion Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool VacacionModel::insertVacacionCargada(Vacacion vacacion)
{
    query->prepare("INSERT INTO "+TABLE_VACACIONCARGADA+" (numero,descripcion,area,fecha_pago,fecha_creac) VALUES "
                                   "(NULL,:descripcion,:area,:fecha_pago,CURDATE())");

    query->bindValue(":descripcion",vacacion.getDescripcion());
    query->bindValue(":area",vacacion.getArea());
    query->bindValue(":fecha_pago",vacacion.getFechaPago());

    if (!query->exec())
    {
        status= "ERROR al insertar Vacacion Cargada. ERROR: "+ query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status= "Vacacion Cargada Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool VacacionModel::deleteVacacionCargada(int vacacionNum)
{
    query->prepare("DELETE FROM "+TABLE_VACACIONCARGADA+" WHERE numero=numero");

    query->bindValue(":numero",vacacionNum);

    if (!query->exec())
    {
        status= "ERROR al Eliminar Vacacion Cargada. ERROR: "+ query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status= "Vacacion Cargada Eliminada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

Vacacion VacacionModel::findVacacionCargada(int VacacionNum)
{
    query->prepare("SELECT * FROM "+TABLE_VACACIONCARGADA+" WHERE numero=:numero");

    query->bindValue(":numero",VacacionNum);

    if (!query->exec())
    {
        status = "ERROR al buscar Vacacion Numero: "+QString::number(VacacionNum)+". ERROR:"+query->lastError().text();
        debugMessage(status);
    } else if (query->next())
    {
        Vacacion vacacion(query->value("numero").toInt(),
                    query->value("descripcion").toString(),
                    query->value("area").toString(),
                    query->value("fecha_pago").toString(),
                    query->value("fecha_creac").toString());
        return vacacion;
    }

}

bool VacacionModel::insertVacacionCargadaDetalles(Vacacion vacacion, int diasBono, int diasAjuste)
{
    QStringList cedulas;
    query->prepare("SELECT cedula FROM empleado WHERE cod_area=:area");
    query->bindValue(":area",vacacion.getArea());

    if (!query->exec()){
        status = "ERROR al buscar empleados por Area. ERROR: "+query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        while(query->next())
        {
            cedulas << query->value("cedula").toString();
        }
    }

    for (int i=0; i<cedulas.size(); ++i){
        if (!insertVacacionCargadaDetalleEmp(vacacion.getNumero(),cedulas[i],diasBono,diasAjuste))
        {
            status = "ERROR al Insertar Vacacion Cargada detalle: "+ status;
            debugMessage(status);
            return false;
            break;
        }
    }
    return true;
}

bool VacacionModel::insertVacacionCargadaDetalleEmp(int vacacionNum, QString empleadoCed, int diasBono, int diasAjuste)
{
    query->prepare("INSERT INTO "+TABLE_VACACIONCARGADADETALLE+"(numero,ced_empleado,dias_bonovac,dias_ajuste) VALUES "
                                                               "(:numero,:cedula,:bonovac,:ajuste)");

    query->bindValue(":numero",vacacionNum);
    query->bindValue(":cedula",empleadoCed);
    query->bindValue(":bonovac",diasBono);
    query->bindValue(":ajuste",diasAjuste);

    if (!query->exec())
    {
        status= "ERROR al Insertar Vacacion Cargada Detalle. ERROR: "+ query->lastError().text();
        debugMessage(status);
        return false;
    } else
    {
        status= "Vacacion Cargada Detalle Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

double VacacionModel::getBonoVacacional(int vacacionNum, QString empleadoCed)
{

}

double VacacionModel::getajusteSalario(int vacacionNum, QString empleadoCed)
{

}

double VacacionModel::getBonoIntegral(int vacacionNum, QString empleadoCed)
{
    double bonoVacacional = getBonoVacacional(vacacionNum,empleadoCed);
    double ajusteSalario = getajusteSalario(vacacionNum,empleadoCed);

    double BonoIntegral = bonoVacacional + ajusteSalario;

    return BonoIntegral;
}
