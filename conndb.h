#ifndef CONNDB_H
#define CONNDB_H

#include <QtSql>
#include <QString>
#include <QDebug>


class connDB
{
public:

    // CONSTRUCTORES
    connDB();
     connDB(QString xhostName,QString xdbName,QString xdbUserName,QString xdbUserPassword,int xdbPort);
     connDB(QString xconnName, QString xhostName, QString xdbName, QString xdbUserName, QString xdbUserPassword, int xdbPort);

public:

     // VARIABLE PUBLICAS
    QSqlDatabase db;

    // PROCEDIMIENTOS PUBLICOS
    void connClose();
    bool connOpen();
    bool isConected();

    // TO STRING
    QString toString();

private:

    // VARIABLES PRIVADAS
    QString connName;
    QString hostName;
    QString dbName;
    QString dbUserName;
    QString dbUserPassword;
    int dbPort;

};

#endif // CONNDB_H
