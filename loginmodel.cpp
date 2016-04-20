#include "loginmodel.h"

const QString TABLE_USUARIO = "usuario";

LoginModel::LoginModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

LoginModel::LoginModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB(connName, hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

LoginModel::~LoginModel()
{
    delete query;
}

bool LoginModel::existUsuario(QString user)
{
    query->prepare("SELECT user FROM "+TABLE_USUARIO+" WHERE user='"+user+"';");

    if (!query->exec())
    {
        status = "ERROR al Verificar Existencia de Usuario : " + query->lastError().text() ;
        debugMessage(status);
        return false;
    }
    else if (!query->next())
    {
        status = "Usuario No Existe...";
        debugMessage(status);
        return false;
    } else
    {
        status = "Usuario: "+user+" Encontrado...";
        debugMessage(status);
        return true;
    }

}

bool LoginModel::matchUserPassword(QString user,QString password)
{
    query->prepare("SELECT SHA('"+password+"')");
    query->exec();
    query->next();
    password= query->value(0).toString();
    query->prepare("SELECT user,password FROM "+TABLE_USUARIO+" where user='"+user+"' and password='"+password+"';");

    if (!query->exec())
    {
        status = "ERROR al Verificar Usuario y contraseña : " + query->lastError().text() ;
        debugMessage(status);
        return false;
    }
    else if (!query->next())
    {
        status = "Usuario o contraseña INCORRECTO.";
        debugMessage(status);
        return false;
    } else
    {
        status = "Usuario y Contraseña Correcta...";
        debugMessage(status);
        return true;
    }

}

