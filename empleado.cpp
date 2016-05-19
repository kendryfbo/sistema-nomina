#include "empleado.h"

Empleado::Empleado()
{
    xCedula = "19017070";
    xNombres = "nombres";
    xApellidos = "apellidos";
    xRif = "rif";
    xFechaNac = "2016-10-10";
    xLugarNac = "lugarNac";
    xEmail = "email";
    xEdoCivil = "edoCivil";
    xNumHijos = 0;
    xDireccion = "direccion";
    xTlf1= "tlf1";
    xTlf2 ="tlf2";
    xNivelAcad = "nivelAcad";
    xEspec = "espec";
    xNivelAcadSup = false;
    xTitulo = "titulo";
    xArea =  "area";
    xClasificacion = Clasificacion();
    xNivel = "DEFAULT";
    xHoras = 0;
    xContrato = "DEFAULT";
    xFechaIngrEduc = "2016-10-10";
    xFechaIngrEducPriv = "2016-10-10";
    xFechaIng = "2016-10-10";
    xStatus = "status";
    xAntiguedad = 1;
    xSalarioHora = 119.75;
    xSalarioDia = 718.5;
    xSalarioSemana =5029.5;
    xSalarioMes = 20118;

}

Empleado::Empleado(QString cedula, QString nombres, QString apellidos, QString rif, QString fechaNac,
                   QString lugarNac, QString email, QString edoCivil, int numHijos, QString direccion, QString tlf1,
                   QString tlf2, QString nivelAcad, QString espec, bool nivelAcadSup, QString titulo)
{
     xCedula = cedula;
     xNombres = nombres;
     xApellidos = apellidos;
     xRif = rif;
     xFechaNac = fechaNac;
     xLugarNac = lugarNac;
     xEmail = email;
     xEdoCivil = edoCivil;
     xNumHijos = numHijos;
     xDireccion = direccion;
     xTlf1= tlf1;
     xTlf2 =tlf2;
     xNivelAcad = nivelAcad;
     xEspec = espec;
     xNivelAcadSup = nivelAcadSup;
     xTitulo = titulo;
}

Empleado::Empleado(QString cedula, QString nombres, QString apellidos, QString rif, QString fechaNac,
                   QString lugarNac, QString email, QString edoCivil, int numHijos, QString direccion, QString tlf1,
                   QString tlf2, QString nivelAcad, QString espec, bool nivelAcadSup, QString titulo, QString fechaIngrEduc,
                   QString fechaIngrEducPriv, QString fechaIng, QString status, QString area, Clasificacion clasificacion, QString nivel, int horas, QString contrato)
{
    xCedula = cedula;
    xNombres = nombres;
    xApellidos = apellidos;
    xRif = rif;
    xFechaNac = fechaNac;
    xLugarNac = lugarNac;
    xEmail = email;
    xEdoCivil = edoCivil;
    xNumHijos = numHijos;
    xDireccion = direccion;
    xTlf1= tlf1;
    xTlf2 =tlf2;
    xNivelAcad = nivelAcad;
    xEspec = espec;
    xNivelAcadSup = nivelAcadSup;
    xTitulo = titulo;
    xFechaIngrEduc = fechaIngrEduc;
    xFechaIngrEducPriv = fechaIngrEducPriv;
    xFechaIng = fechaIng;
    xStatus = status;
    xArea = area;
    xClasificacion = clasificacion;
    xNivel = nivel;
    xHoras = horas;
    xContrato = contrato;
}

Empleado::Empleado(QString cedula, QString nombres, QString apellidos, QString rif, QString fechaNac,
                   QString lugarNac, QString email, QString edoCivil, int numHijos, QString direccion, QString tlf1,
                   QString tlf2, QString nivelAcad, QString espec, bool nivelAcadSup, QString titulo, QString fechaIngrEduc,
                   QString fechaIngrEducPriv, QString fechaIng, QString status, QString area, Clasificacion clasificacion, QString nivel,
                   int horas, double salarioHora, double salarioDia, double salarioSemana, double salarioMes, QString contrato, int antiguedad)
{
    xCedula = cedula;
    xNombres = nombres;
    xApellidos = apellidos;
    xRif = rif;
    xFechaNac = fechaNac;
    xLugarNac = lugarNac;
    xEmail = email;
    xEdoCivil = edoCivil;
    xNumHijos = numHijos;
    xDireccion = direccion;
    xTlf1= tlf1;
    xTlf2 =tlf2;
    xNivelAcad = nivelAcad;
    xEspec = espec;
    xNivelAcadSup = nivelAcadSup;
    xTitulo = titulo;
    xFechaIngrEduc = fechaIngrEduc;
    xFechaIngrEducPriv = fechaIngrEducPriv;
    xFechaIng = fechaIng;
    xStatus = status;
    xArea = area;
    xClasificacion = clasificacion;
    xNivel = nivel;
    xHoras = horas;
    xSalarioHora = salarioHora;
    xSalarioDia = salarioDia;
    xSalarioSemana = salarioSemana;
    xSalarioMes = salarioMes;
    xContrato = contrato;
    xAntiguedad = antiguedad;
}

QString Empleado::getCedula() const
{
    return xCedula;
}

QString Empleado::getNombres() const
{
    return xNombres;
}

void Empleado::setNombres(const QString &value)
{
    xNombres = value;
}

QString Empleado::getApellidos() const
{
    return xApellidos;
}

void Empleado::setApellidos(const QString &value)
{
    xApellidos = value;
}

QString Empleado::getRif() const
{
    return xRif;
}

void Empleado::setRif(const QString &value)
{
    xRif = value;
}

QString Empleado::getFechaNac() const
{
    return xFechaNac;
}

void Empleado::setFechaNac(const QString &value)
{
    xFechaNac = value;
}

QString Empleado::getLugarNac() const
{
    return xLugarNac;
}

void Empleado::setLugarNac(const QString &value)
{
    xLugarNac = value;
}

QString Empleado::getEmail() const
{
    return xEmail;
}

void Empleado::setEmail(const QString &value)
{
    xEmail = value;
}

QString Empleado::getEdoCivil() const
{
    return xEdoCivil;
}

void Empleado::setEdoCivil(const QString &value)
{
    xEdoCivil = value;
}

int Empleado::getNumHijos() const
{
    return xNumHijos;
}

void Empleado::setNumHijos(int value)
{
    xNumHijos = value;
}

QString Empleado::getDireccion() const
{
    return xDireccion;
}

void Empleado::setDireccion(const QString &value)
{
    xDireccion = value;
}

QString Empleado::getTlf1() const
{
    return xTlf1;
}

void Empleado::setTlf1(const QString &value)
{
    xTlf1 = value;
}

QString Empleado::getTlf2() const
{
    return xTlf2;
}

void Empleado::setTlf2(const QString &value)
{
    xTlf2 = value;
}

QString Empleado::getNivelAcad() const
{
    return xNivelAcad;
}

void Empleado::setNivelAcad(const QString &value)
{
    xNivelAcad = value;
}

QString Empleado::getEspec() const
{
    return xEspec;
}

void Empleado::setEspec(const QString &value)
{
    xEspec = value;
}

bool Empleado::getNivelAcadSup() const
{
    return xNivelAcadSup;
}

void Empleado::setNivelAcadSup(const bool &value)
{
    xNivelAcadSup = value;
}

QString Empleado::getTitulo() const
{
    return xTitulo;
}

void Empleado::setTitulo(const QString &value)
{
    xTitulo = value;
}

QString Empleado::getArea() const
{
    return xArea;
}

void Empleado::setArea(const QString &value)
{
    xArea = value;
}

Clasificacion Empleado::getClasificacion() const
{
    return xClasificacion;
}

void Empleado::setClasificacion(const Clasificacion &value)
{
    xClasificacion = value;
}

QString Empleado::getNivel() const
{
    return xNivel;
}

void Empleado::setNivel(const QString &value)
{
    xNivel = value;
}

int Empleado::getHoras() const
{
    return xHoras;
}

void Empleado::setHoras(int value)
{
    xHoras = value;
}

QString Empleado::getContrato() const
{
    return xContrato;
}
void Empleado::setContrato(const QString &value)
{
    xContrato = value;
}

QString Empleado::getFechaIngrEduc() const
{
    return xFechaIngrEduc;
}
void Empleado::setFechaIngrEduc(const QString &value)
{
    xFechaIngrEduc = value;
}

QString Empleado::getFechaIngrEducPriv() const
{
    return xFechaIngrEducPriv;
}

void Empleado::setFechaIngrEducPriv(const QString &value)
{
    xFechaIngrEducPriv = value;
}

QString Empleado::getFechaIng() const
{
    return xFechaIng;
}
void Empleado::setFechaIng(const QString &value)
{
    xFechaIng = value;
}

QString Empleado::getStatus() const
{
    return xStatus;
}
void Empleado::setStatus(const QString &value)
{
    xStatus = value;
}

int Empleado::getAntiguedad() const
{
    return xAntiguedad;
}

void Empleado::setAntiguedad(int value)
{
    xAntiguedad = value;
}

double Empleado::getSalarioHora() const
{
    return xSalarioHora;
}

double Empleado::getSalarioDia() const
{
    return xSalarioDia;
}

double Empleado::getSalarioSemana() const
{
    return xSalarioSemana;
}

double Empleado::getSalarioMes() const
{
    return xSalarioMes;
}
