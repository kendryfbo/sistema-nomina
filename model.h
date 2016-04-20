#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QDebug>
#include "conndb.h"

class Model
{
public:
    //CONSTRUCTORES
    Model();
    Model(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    Model(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    ~Model();
    // CONECTAR A LA BASE DE DATOS
    bool connect();
    void disconnect();
    bool isConected();

    // OBTENER  STATUS DEL MODELO
    QString getStatusMessage();

    bool debugMessage(QString msg);
    // TRANSACTIONS
    bool startTransaction();
    bool rollBack();
    bool Commit();

    void setDebug(bool value);

protected:
    //PROTECTED MEMBERS
    // PRIVATE VARIABLES
    QSqlQuery* query;
    connDB conexion;
    bool debug;
    bool connected;
    QString status;
};

#endif // MODEL_H
