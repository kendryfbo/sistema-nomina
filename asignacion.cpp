#include "asignacion.h"

Asignacion::Asignacion()
{
    xcodigo = "";
    xdescripcion = "descripcion";
    xforma = "forma";
    xvalor = 0;
}

Asignacion::Asignacion(QString codigo, QString descripcion, QString forma, double valor, QString formula, bool prima, bool activo)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xforma = forma;
    xvalor = valor;
    xformula = formula;
    xprima = prima;
    xactivo = activo;

}

Asignacion::Asignacion(QString codigo,QString descripcion,QString forma,double valor, QString formula,bool prima, bool activo,QString fecha)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xforma = forma;
    xvalor = valor;
    xformula = formula;
    xprima = prima;
    xactivo = activo;
    xfecha = fecha;
}

QString Asignacion::getCodigo() const
{
    return xcodigo;
}

QString Asignacion::getDescripcion() const
{
    return xdescripcion;
}

void Asignacion::setDescripcion(const QString &value)
{
    xdescripcion = value;
}

// Deshabilitado
/*
QString Asignacion::getTipo() const
{
    return xtipo;
}

void Asignacion::setTipo(const QString &value)
{
    xtipo = value;
}

QString Asignacion::tipoToString(Asignacion::Tipo tipo)
{
    if (tipo == Tipo::fijo)
        return "FIJO";
    if (tipo == Tipo::opcional)
        return "OPCIONAL";
    else
        return "OPCIONAL";
}

Asignacion::Tipo Asignacion::stringToTipo(QString tipo)
{
    if (tipo == "FIJO")
        return Tipo::fijo;
    if (tipo == "OPCIONAL")
        return Tipo::opcional;
    else
        return Tipo::opcional;
}
*/

QString Asignacion::getForma() const
{
    return xforma;
}

void Asignacion::setForma(const QString &value)
{
    xforma = value;
}

QString Asignacion::formaToString(Asignacion::Forma forma)
{
    if (forma == Forma::monto)
        return "MONTO";
    if (forma == Forma::porcentaje)
        return "PORCENTAJE";
    else
        return "MONTO";
}

Asignacion::Forma Asignacion::stringToForma(QString forma)
{
    if (forma == "MONTO")
        return Forma::monto;
    if (forma == "PORCENTAJE")
        return Forma::porcentaje;
    else
        return Forma::porcentaje;
}

double Asignacion::getValor() const
{
    return xvalor;
}

void Asignacion::setValor(double value)
{
    xvalor = value;
}

QString Asignacion::getFecha() const
{
    return xfecha;
}

bool Asignacion::isActivo() const
{
    return xactivo;
}

void Asignacion::setActivo(bool value)
{
    xactivo = value;
}

bool Asignacion::hasPrima() const
{
    return xprima;
}

void Asignacion::setPrima(bool value)
{
    xprima = value;
}

QString Asignacion::getFormula() const
{
    return xformula;
}

void Asignacion::setFormula(const QString &value)
{
    xformula = value;
}
