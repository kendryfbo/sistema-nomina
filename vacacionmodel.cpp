#include "vacacionmodel.h"

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

double VacacionModel::getBonoIntegral(int vacacionNum, QString empleadoCed)
{
    double bonoVacacional = getBonoVacacional(vacacionNum,empleadoCed);
    double ajusteSalario = getajusteSalario(vacacionNum,empleadoCed);

    double BonoIntegral = bonoVacacional + ajusteSalario;

    return BonoIntegral;
}
