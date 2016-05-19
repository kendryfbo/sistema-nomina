#include "deduccion.h"

Deduccion::Deduccion()
{
    xcodigo = "";
    xdescripcion = "descripcion";
    xforma = "forma";
    xvalor = 0;
}

Deduccion::Deduccion(QString codigo, QString descripcion, QString forma, double valor, QString formula, bool activo)
{
     xcodigo = codigo;
     xdescripcion = descripcion;
     xforma = forma;
     xvalor = valor;
     xformula = formula;
     xactivo = activo;
}

Deduccion::Deduccion(QString codigo, QString descripcion, QString forma, double valor, QString formula, QString fecha, bool activo)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xforma = forma;
    xvalor = valor;
    xformula = formula;
    xfecha = fecha;
    xactivo = activo;
}

QString Deduccion::getCodigo() const
{
    return xcodigo;
}

QString Deduccion::getDescripcion() const
{
    return xdescripcion;
}

void Deduccion::setDescripcion(const QString &value)
{
    xdescripcion = value;
}

QString Deduccion::getForma() const
{
    return xforma;
}

void Deduccion::setForma(const QString &value)
{
    xforma = value;
}

QString Deduccion::formaToString(Deduccion::Forma forma)
{
    if (forma == Forma::monto)
        return "MONTO";
    if (forma == Forma::porcentaje)
        return "PORCENTAJE";
    else
        return "MONTO";
}

Deduccion::Forma Deduccion::stringToForma(QString forma)
{
    if (forma == "MONTO")
        return Forma::monto;
    if (forma == "PORCENTAJE")
        return Forma::porcentaje;
    else
        return Forma::porcentaje;
}

double Deduccion::getValor() const
{
    return xvalor;
}

void Deduccion::setValor(double value)
{
    xvalor = value;
}

// Deshabilitado
/*
QStringList Deduccion::getCodCampo() const
{
    return xcodCampo;
}

void Deduccion::setCodCampo(const QStringList &value)
{
    xcodCampo = value;
}
*/

QString Deduccion::getFecha() const
{
    return xfecha;
}

bool Deduccion::isActivo() const
{
    return xactivo;
}

void Deduccion::setActivo(bool value)
{
    xactivo = value;
}

QString Deduccion::toString()
{
    QString str = getCodigo()+","+
            getDescripcion()+","+
            getForma()+","+
            QString::number(getValor());

    return str;
}

QString Deduccion::getFormula() const
{
    return xformula;
}

void Deduccion::setFormula(const QString &value)
{
    xformula = value;
}
