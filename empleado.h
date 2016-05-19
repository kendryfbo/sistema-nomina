#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QtCore>
#include <QString>

#include "clasificacion.h"

class Empleado
{
public:

    Empleado();

    Empleado(QString cedula, QString nombres, QString apellidos, QString rif,
    QString fechaNac, QString lugarNac, QString email, QString edoCivil, int numHijos,
    QString direccion, QString tlf1, QString tlf2, QString nivelAcad, QString espec,
    bool nivelAcadSup, QString titulo);

    Empleado(QString cedula, QString nombres, QString apellidos, QString rif,
    QString fechaNac, QString lugarNac, QString email, QString edoCivil, int numHijos,
    QString direccion, QString tlf1, QString tlf2, QString nivelAcad, QString espec,
    bool nivelAcadSup, QString titulo, QString fechaIngrEduc, QString fechaIngrEducPriv,
    QString fechaIng, QString status, QString area, Clasificacion clasificacion, QString nivel, int  horas,QString contrato);

    Empleado(QString cedula, QString nombres, QString apellidos, QString rif,
    QString fechaNac, QString lugarNac, QString email, QString edoCivil, int numHijos,
    QString direccion, QString tlf1, QString tlf2, QString nivelAcad, QString espec,
    bool nivelAcadSup, QString titulo, QString fechaIngrEduc, QString fechaIngrEducPriv,
    QString fechaIng, QString status, QString area, Clasificacion clasificacion, QString nivel, int horas,
    double salarioHora, double salarioDia, double salarioSemana, double salarioMes, QString contrato, int antiguedad);

    QString getCedula() const;

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

    QString getArea() const;
    void setArea(const QString &value);

    Clasificacion getClasificacion() const;
    void setClasificacion(const Clasificacion &value);

    QString getNivel() const;
    void setNivel(const QString &value);

    int getHoras() const;
    void setHoras(int value);

    QString getContrato() const;
    void setContrato(const QString &value);

    QString getFechaIngrEduc() const;
    void setFechaIngrEduc(const QString &value);

    QString getFechaIngrEducPriv() const;
    void setFechaIngrEducPriv(const QString &value);

    QString getFechaIng() const;
    void setFechaIng(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    int getAntiguedad() const;
    void setAntiguedad(int value);

    double getSalarioHora() const;

    double getSalarioDia() const;

    double getSalarioSemana() const;

    double getSalarioMes() const;

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

// DATOS LABORALES
    QString xFechaIngrEduc;
    QString xFechaIngrEducPriv;
    QString xFechaIng;
    QString xStatus;
    QString xArea;
    Clasificacion xClasificacion;
    QString xNivel;
    int  xHoras;
    double xSalarioHora;
    double xSalarioDia;
    double xSalarioSemana;
    double xSalarioMes;
    QString xContrato;
    int xAntiguedad;

};

#endif // EMPLEADO_H
