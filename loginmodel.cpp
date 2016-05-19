#include "loginmodel.h"

const QString TABLE_USUARIO = "usuario";
const QString TABLE_PERFIL = "usuarioperfil";

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

Usuario LoginModel::findUsuario(QString user)
{
    Usuario usuario;
    query->prepare("SELECT * FROM "+TABLE_USUARIO+" WHERE user=:user");
    query->bindValue(":user",user);

    if (!query->exec())
    {
        status = "ERROR al Buscar Usuario: " +query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
    } else if (!query->next())
    {
        status = "Usuario No Encontrado.";
        debugMessage(status);
    } else
    {
        Usuario::Perfil perfil(findPerfilDeUsuario(query->value("cod_perfil").toString()));
        usuario =Usuario(
                    query->value("user").toString(),
                    query->value("password").toString(),
                    query->value("nombres").toString(),
                    query->value("apellidos").toString(),
                    perfil,
                    query->value("activo").toBool(),
                    query->value("fechacreac").toString()
                    );
        status = "Usuario Encontrado...";
        debugMessage(status);
    }
    return usuario;
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

Usuario::Perfil LoginModel::findPerfilDeUsuario(QString codigo)
{

    Usuario::Perfil perfil;

    QSqlQuery query2 = QSqlQuery(conexion.db);

    query2.prepare("SELECT * FROM "+TABLE_PERFIL+" WHERE codigo=:codigo");
    query2.bindValue(":codigo",codigo);

    if (!query2.exec())
    {
        status = "ERROR al Buscar Perfil Usuario: " + query2.lastError().text();
        debugMessage(status);
    } else if (!query2.next())
    {
        status= "Perfil No Encontrado.";
        debugMessage(status);
    } else
    {
        perfil = Usuario::Perfil(
                    query->value("codigo").toString(),
                    query->value("descripcion").toString(),
                    query->value("empleados").toBool(),
                    query->value("deduccion").toBool(),
                    query->value("asignacion").toBool(),
                    query->value("nomina").toBool(),
                    query->value("reportes").toBool(),
                    query->value("consultas").toBool(),
                    query->value("usuarios").toBool(),
                    query->value("perfiles").toBool(),
                    query->value("activo").toBool(),
                    query->value("fechacreac").toString()
                    );
        status= "Perfil Encontrado...";
        debugMessage(status);
    }
    return Usuario::Perfil();
}

