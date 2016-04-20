#include "model.h"

 //CONSTRUCTORES
Model::Model() : connected(false){}
Model::Model(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort)
{
    conexion =connDB(hostName,dbName,dbUserName,dbUserPassword,dbPort);
    connect();
    status="";
}
Model::Model(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion =connDB(connName,hostName,dbName,dbUserName,dbUserPassword,dbPort);
    connect();
    status="";
}

Model::~Model()
{
    delete query;
    conexion.connClose();
}
// CONECTAR A LA BASE DE DATOS
bool Model::connect()
{
    if (!conexion.connOpen()){
        status = "ERROR: Model No pudo Conectarse a la Base de datos";
        connected = false;
    } else {
        status = "Model: Conetado a Base de datos";
        connected = true;
    }
    debugMessage(status);
    return connected;
}
// VERIFICAR SI EXISTE CONEXION A LA BASE DE DATOS
bool Model::isConected()
{
    if (conexion.isConected())
        status = "Conexion a la Base de Datos se encuentra ABIERTA";
    else status = "Conexion a la Base de Datos se encuentra CERRADA";

    return conexion.isConected();
}
// DESCONECTARSE A LA BASE DE DATOS
void Model::disconnect(){
    conexion.connClose();
    status = "Conexion a la Base de Datos ha sido Cerrada";
}

bool Model::startTransaction()
{
query->prepare("START TRANSACTION;");
if (!query->exec())
{
    status = "Error al Ejecutar TRANSACCION: " + query->lastError().text() + "\n" + query->executedQuery();
    debugMessage(status);
    return false;
} else
    return true;
}
bool Model::rollBack()
{
    query->prepare("ROLLBACK;");
    if (!query->exec())
    {
        status = "Error al Ejecutar ROLLBACK: " + query->lastError().text() + "\n" + query->executedQuery();
        debugMessage(status);
        query->clear();
        return false;
    } else {
        query->clear();
        return true;
    }

}
bool Model::Commit()
{
    query->prepare("COMMIT;");
    if (!query->exec())
    {
        status = "Error al Ejecutar COMMIT: " + query->lastError().text() + "\n" + query->executedQuery();
        debugMessage(status);
        query->clear();
        return false;
    } else {
        query->clear();
        return true;
    }
}

void Model::setDebug(bool value)
{
    debug = value;
}

// OBTENER  STATUS DEL MODELO
QString Model::getStatusMessage()
{
    return status;
}

bool Model::debugMessage(QString msg)
{
    if (debug)
        qDebug() << msg;

    return true;
}

