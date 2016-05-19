#include "conndb.h"


// CONSTRUCTOR QUE INICIALIZA LAS VARIABLES PARA LA CONEXION CON LA BASE DE DATOS CON VALORES POR DEFECTO
connDB::connDB()
{
    connName = "default";
    hostName = "127.0.0.1";
    dbName = "clinica";
    dbUserName = "root";
    dbUserPassword = "19017070";
    dbPort = 3306;
     //qDebug() << "connDB Creada con Parametros por Defecto";
}
// CONSTRUCTOR QUE INICIALIZA LAS VARIABLES PARA LA CONEXION CON LA BASE DE DATOS CON VALORES SUMINISTRADOS
connDB::connDB(QString xhostName,QString xdbName,QString xdbUserName,QString xdbUserPassword,int xdbPort)
{
    connName = "default";
    hostName = xhostName;
    dbName = xdbName;
    dbUserName = xdbUserName;
    dbUserPassword = xdbUserPassword;
    dbPort = xdbPort;
    //qDebug() << "connDB Creada con Parametros proporcionados";
}
// CONSTRUCTOR CON NOMBRE DE CONEXION INICIALIZA LAS VARIABLES PARA LA CONEXION CON LA BASE DE DATOS CON VALORES SUMINISTRADOS
connDB::connDB(QString xconnName, QString xhostName, QString xdbName, QString xdbUserName, QString xdbUserPassword, int xdbPort)
{
    connName = xconnName ;
    hostName = xhostName;
    dbName = xdbName;
    dbUserName = xdbUserName;
    dbUserPassword = xdbUserPassword;
    dbPort = xdbPort;
}
//CIERRA LA CONEXION CON LA BASE DE DATOS
void connDB::connClose()
{
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connName);
    //qDebug() << "conexion a la base de datos fue CERRADA";
}
// ABRE LA CONEXION CON LA BASE DE DATOS
bool connDB::connOpen()
{
    db = QSqlDatabase::addDatabase("QMYSQL",connName);
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbUserPassword);
    db.setPort(3306);

    if (!db.open()){
         qDebug() << "ConnDB: ERROR de conexion con la base de datos";
        qDebug() << db.lastError().text();
        return false;
    }else {
      qDebug() << "ConnDB: conexion a la base de datos fue ABIERTA EXITOSAMENTE";
      return true;
    }
}
// VERIFICAR CONEXION
bool connDB::isConected()
{
    return db.isOpen();
}
// TO STRING
QString connDB::toString()
{
    QString str =
            "Conection Name:" +connName +"\n"+
            "Host Name:" + hostName +"\n"+
            "Db Name:" + dbName +"\n"+
            "User Name:" + dbUserName +"\n"+
            "Password:" + dbUserPassword +"\n"+
            "Db Port:" + QString::number(dbPort);

    return str;

}
