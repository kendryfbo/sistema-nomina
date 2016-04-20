#include "asignacion.h"

Asignacion::Asignacion()
{
    xcodigo = "codigo";
    xdescripcion = "descripcion";
    xforma = "forma";
    xvalor = 0;
}

Asignacion::Asignacion(QString codigo, QString descripcion, QString forma, double valor)
{
     xcodigo = codigo;
     xdescripcion = descripcion;
     xforma = forma;
     xvalor = valor;
}

QString Asignacion::getCodigo() const
{
    return xcodigo;
}

void Asignacion::setCodigo(const QString &value)
{
    xcodigo = value;
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
// Deshabilitado
/*
QStringList Asignacion::getCodCampo() const
{
    return xcodCampo;
}

void Asignacion::setCodCampo(const QStringList &value)
{
    xcodCampo = value;
}
*/
