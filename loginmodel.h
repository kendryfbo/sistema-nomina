#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include "model.h"
#include "usuario.h"

class LoginModel : public Model
{
public:

    enum Campo {user,nombre,apellido};

    LoginModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    LoginModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~LoginModel();

    bool insertUsuario(Usuario usuario);
    bool UpdateUsuario(Usuario usuario);
    bool deleteUsuario(QString user);

    Usuario findUsuario(QString str,Campo campo= Campo::user,bool ini=true,bool fin=true);
    QSqlQuery findUsuarios(QString str="",Campo campo= Campo::user,bool ini=true,bool fin=true);
    bool existUsuario(QString user);
    bool matchUserPassword(QString user,QString password);


    bool insertPerfil(Usuario::Perfil perfil);
    bool updatePerfil(Usuario::Perfil perfil);
    bool deletePerfil(Usuario::Perfil perfil);


};

#endif // LOGINMODEL_H
