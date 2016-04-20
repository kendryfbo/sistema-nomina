#include "deduccion.h"

Deduccion::Deduccion()
{
    xcodigo = "DEFAULT";
    xdescripcion = "descripcion";
    xforma = "forma";
    xvalor = 0;
}

Deduccion::Deduccion(QString codigo, QString descripcion, QString forma, double valor, bool activo)
{
     xcodigo = codigo;
     xdescripcion = descripcion;
     xforma = forma;
     xvalor = valor;
     xactivo = activo;
}

Deduccion::Deduccion(QString codigo, QString descripcion, QString forma, double valor, QString fecha, bool activo)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xforma = forma;
    xvalor = valor;
    xfecha = fecha;
    xactivo = activo;
}

QString Deduccion::getCodigo() const
{
    return xcodigo;
}

void Deduccion::setCodigo(const QString &value)
{
    xcodigo = value;
}

QString Deduccion::getDescripcion() const
{
    return xdescripcion;
}

void Deduccion::setDescripcion(const QString &value)
{
    xdescripcion = value;
}

// Deshabilitado
/*
QString Deduccion::getTipo() const
{
    return xtipo;
}

void Deduccion::setTipo(const QString &value)
{
    xtipo = value;
}

QString Deduccion::tipoToString(Deduccion::Tipo tipo)
{
    if (tipo == Tipo::fijo)
        return "FIJO";
    if (tipo == Tipo::opcional)
        return "OPCIONAL";
    else
        return "OPCIONAL";
}

Deduccion::Tipo Deduccion::stringToTipo(QString tipo)
{
    if (tipo == "FIJO")
        return Tipo::fijo;
    if (tipo == "OPCIONAL")
        return Tipo::opcional;
    else
        return Tipo::opcional;
}
*/

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
