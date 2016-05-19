#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario
{
public:

    struct Perfil {

    public:
        Perfil(){}
        Perfil(QString codigo,QString descripcion,bool empleados,bool deduccion,bool asignacion,bool nomina,bool reportes,bool consultas,bool usuarios,bool perfiles,bool activo)
        {
            xcodigo = codigo;
            xdescripcion = descripcion;
            xempleados = empleados;
            xdeduccion = deduccion;
            xasignacion = asignacion;
            xnomina = nomina;
            xreportes = reportes;
            xconsultas = consultas;
            xusuarios = usuarios;
            xperfiles =perfiles;
            xactivo = activo;
        }
        Perfil(QString codigo,QString descripcion,bool empleados,bool deduccion,bool asignacion,bool nomina,bool reportes,bool consultas,bool usuarios,bool perfiles,bool activo,QString fecha)
        {
            xcodigo = codigo;
            xdescripcion = descripcion;
            xempleados = empleados;
            xdeduccion = deduccion;
            xasignacion = asignacion;
            xnomina = nomina;
            xreportes = reportes;
            xconsultas = consultas;
            xusuarios = usuarios;
            xperfiles =perfiles;
            xactivo = activo;
            xfecha = fecha;
        }

        QString getCodigo(){
            return xcodigo;
        }
        QString getDescripcion(){
             return xdescripcion;
         }
        bool hasEmpleados(){
             return xempleados;
         }
        bool hasDeduccion(){
             return xdeduccion;
         }
        bool hasAsignacion(){
             return xasignacion;
         }
        bool hasNomina(){
             return xnomina;
         }
        bool hasReportes(){
             return xreportes;
         }
        bool hasConsultas(){
             return xconsultas;
         }
        bool hasUsuarios(){
             return xusuarios;
         }
        bool hasPerfiles(){
             return xperfiles;
         }
        bool isActivo(){
             return xactivo;
         }
        QString getFecha(){
             return xfecha;
         }

    private:
        QString xcodigo;
        QString xdescripcion;
        bool xempleados;
        bool xdeduccion;
        bool xasignacion;
        bool xnomina;
        bool xreportes;
        bool xconsultas;
        bool xusuarios;
        bool xperfiles;
        bool xactivo;
        QString xfecha;
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
    Usuario::Perfil xperfil;
    bool xactivo;
    QString xfecha;

};

#endif // USUARIO_H
