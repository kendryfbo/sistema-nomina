#include "empresamodel.h"

const QString TABLE_EMPRESA="empresa";
const QString CODIGO_EMPRESA="001";

EmpresaModel::EmpresaModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}

EmpresaModel::EmpresaModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

EmpresaModel::EmpresaModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

EmpresaModel::~EmpresaModel()
{
    delete query;
}

EmpresaModel::update(EmpresaModel::Empresa empresa)
{
    query->prepare("UPDATE "+TABLE_EMPRESA+" SET descripcion=:descripcion,rif=:rif,direccion=:direccion,tlf1=:tlf1,tlf2=:tlf2,"
                                           "director=:director,cedula:=cedula,mensaje=:mensaje WHERE codigo=:codigo");

    query->bindValue(":descripcion",empresa.descripcion);
    query->bindValue(":rif",empresa.rif);
    query->bindValue(":direccion",empresa.direccion);
    query->bindValue(":tlf1",empresa.tlf1);
    query->bindValue(":tlf2",empresa.tlf2);
    query->bindValue(":director",empresa.director);
    query->bindValue(":cedula",empresa.cedula);
    query->bindValue(":mensaje",empresa.mensaje);
    query->bindValue(":codigo",CODIGO_EMPRESA);

    if (!query->exec()){
        status = "Error al Actualizar Datos de Empresa: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Empresa Actualizada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

EmpresaModel::Empresa EmpresaModel::findEmpresa()
{
    query->prepare("SELECT * FROM empresa where codigo=:codigo");
    query->bindValue(":codigo",CODIGO_EMPRESA);

    if (!query->exec())
    {
        status = "Error al Buscar Datos de Empresa: " + query->lastError().text();
        debugMessage(status);
    }else if (!query->next())
    {
        status = "Empresa Codigo: "+CODIGO_EMPRESA+" No existe.";
        debugMessage(status);
    }else
    {
        Empresa empresa;
        empresa.descripcion = query->value("descripcion").toString();
        empresa.rif = query->value("rif").toString();
        empresa.direccion = query->value("direccion").toString();
        empresa.tlf1 = query->value("tlf1").toString();
        empresa.tlf2 = query->value("tlf2").toString();
        empresa.director = query->value("director").toString();
        empresa.cedula = query->value("cedula").toString();
        empresa.mensaje = query->value("mensaje").toString();

        status = "Empresa código:"+CODIGO_EMPRESA+" Encontrada...";
        debugMessage(status);

        return empresa;
    }
    return Empresa();
}
