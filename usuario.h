#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario
{
public:

    struct Perfil {

    public:

    private:
        QString codigo;
        QString descripcion;
        bool empleados;
        bool deduccion;
        bool asignacion;
        bool nomina;
        bool reportes;
        bool consultas;
        bool usuarios;
        bool perfiles;
        bool activo;
        QString fecha;
    };

    Usuario();
    Usuario(QString user, QString password, QString nombres, QString apellidos, Perfil perfil, bool activo);
    Usuario(QString user, QString password, QString nombres, QString apellidos, Perfil perfil, bool activo, QString fecha);

    QString getUser() const;
    void setUser(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getNombres() const;
    void setNombres(const QString &value);

    QString getApellidos() const;
    void setApellidos(const QString &value);

    Perfil getPerfil() const;
    void setPerfil(const Perfil &value);

    bool getActivo() const;
    void setActivo(bool value);

    QString getFecha() const;

    QString toString();

private:

    QString xuser;
    QString xpassword;
    QString xnombres;
    QString xapellidos;
    Perfil xperfil;
    bool xactivo;
    QString xfecha;

};

#endif // USUARIO_H
