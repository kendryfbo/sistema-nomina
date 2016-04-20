#include "usuario.h"

Usuario::Usuario()
{
     xuser = "DEFAULT";
     xpassword = "DEFAULT";
     xnombres = "DEFAULT";
     xapellidos = "DEFAULT";;
     xperfil = Perfil();
     xactivo = false;
}

Usuario::Usuario(QString user, QString password, QString nombres, QString apellidos, Usuario::Perfil perfil, bool activo)
{
    xuser = user;
    xpassword = password;
    xnombres = nombres;
    xapellidos = apellidos;
    xperfil = perfil;
    xactivo =activo;
}

Usuario::Usuario(QString user, QString password, QString nombres, QString apellidos, Usuario::Perfil perfil, bool activo, QString fecha)
{
     xuser = user;
     xpassword = password;
     xnombres = nombres;
     xapellidos = apellidos;
     xperfil = perfil;
     xactivo =activo;
     xfecha = fecha;
}

QString Usuario::getUser() const
{
    return xuser;
}

void Usuario::setUser(const QString &value)
{
    xuser = value;
}

QString Usuario::getPassword() const
{
    return xpassword;
}

void Usuario::setPassword(const QString &value)
{
    xpassword = value;
}

QString Usuario::getNombres() const
{
    return xnombres;
}

void Usuario::setNombres(const QString &value)
{
    xnombres = value;
}

QString Usuario::getApellidos() const
{
    return xapellidos;
}

void Usuario::setApellidos(const QString &value)
{
    xapellidos = value;
}

Usuario::Perfil Usuario::getPerfil() const
{
    return xperfil;
}

void Usuario::setPerfil(const Perfil &value)
{
    xperfil = value;
}

bool Usuario::getActivo() const
{
    return xactivo;
}

void Usuario::setActivo(bool value)
{
    xactivo = value;
}

QString Usuario::getFecha() const
{
    return xfecha;
}
