#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QString>


class Empleado
{
public:

    enum class Contrato {determinado,indeterminado};

    struct AreaDeTrabajo {
        QString codigo;
        QString Descripcion;
    };
    struct Clasificacion {
        QString codigo;
        QString Descripcion;
    };
    struct Status {
        QString codigo;
        QString descripcion;
    };

    Empleado();
    Empleado(QString cedula, QString nombres, QString apellidos, QString rif,
    QString fechaNac, QString lugarNac, QString email, QString edoCivil, int numHijos,
    QString direccion, QString tlf1, QString tlf2, QString nivelAcad, QString espec,
    bool nivelAcadSup, QString titulo);

    QString getCedula() const;
    void setCedula(const QString &value);

    QString getNombres() const;
    void setNombres(const QString &value);

    QString getApellidos() const;
    void setApellidos(const QString &value);

    QString getRif() const;
    void setRif(const QString &value);

    QString getFechaNac() const;
    void setFechaNac(const QString &value);

    QString getLugarNac() const;
    void setLugarNac(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getEdoCivil() const;
    void setEdoCivil(const QString &value);

    int getNumHijos() const;
    void setNumHijos(int value);

    QString getDireccion() const;
    void setDireccion(const QString &value);

    QString getTlf1() const;
    void setTlf1(const QString &value);

    QString getTlf2() const;
    void setTlf2(const QString &value);

    QString getNivelAcad() const;
    void setNivelAcad(const QString &value);

    QString getEspec() const;
    void setEspec(const QString &value);

    bool getNivelAcadSup() const;
    void setNivelAcadSup(const bool &value);

    QString getTitulo() const;
    void setTitulo(const QString &value);

    AreaDeTrabajo getArea() const;
    void setArea(const AreaDeTrabajo &value);

    Clasificacion getClasificacion() const;
    void setClasificacion(const Clasificacion &value);

    QString getNivel() const;
    void setNivel(const QString &value);

    int getHoras() const;
    void setHoras(int value);

    QString getContrato() const;
    void setContrato(Contrato &value);




    QString contratoToString( Contrato &value);
    Contrato stringToContrato( QString &value);

    QString getFechaIngrEduc() const;
    void setFechaIngrEduc(const QString &value);

    QString getFechaIngrEducPriv() const;
    void setFechaIngrEducPriv(const QString &value);

    QString getFechaIng() const;
    void setFechaIng(const QString &value);

    Status getStatus() const;
    void setStatus(const Status &value);

    int getAntiguedad() const;

private:

    QString xCedula;
    QString xNombres;
    QString xApellidos;
    QString xRif;
    QString xFechaNac;
    QString xLugarNac;
    QString xEmail;
    QString xEdoCivil;
    int xNumHijos;
    QString xDireccion;
    QString xTlf1;
    QString xTlf2;
    QString xNivelAcad; // Nivel academico
    QString xEspec; // especialidad
    bool xNivelAcadSup; // Nivel academico superior
    QString xTitulo;

// DATOS ACADEMICOS
    AreaDeTrabajo xArea;
    Clasificacion xClasificacion;
    QString xNivel;
    int  xHoras;
    QString xContrato;
    QString xFechaIngrEduc;
    QString xFechaIngrEducPriv;
    QString xFechaIng;
    Status xStatus;
    int xAntiguedad;

};

#endif // EMPLEADO_H
