#include "clasificacion.h"

Clasificacion::Clasificacion()
{
    xcodigo = "";
    xdescripcion = "DEFAULT";
    xarea = "DEFAULT";
    xformaPago = "HORA";
    xvalor = 47.40;
    xactivo = true;
}

Clasificacion::Clasificacion(QString codigo, QString descripcion, QString area, QString formaPago, double valor, bool activo)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xarea = area;
    xformaPago = formaPago;
    xvalor = valor;
    xactivo = activo;
}

Clasificacion::Clasificacion(QString codigo, QString descripcion, QString area, QString formaPago, double valor, bool activo, QString fecha)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xarea = area;
    xformaPago = formaPago;
    xvalor = valor;
    xactivo = activo;
    xfecha = fecha;
}

QString Clasificacion::getCodigo() const
{
    return xcodigo;
}

QString Clasificacion::getDescripcion() const
{
    return xdescripcion;
}

void Clasificacion::setDescripcion(const QString &value)
{
    xdescripcion = value;
}

QString Clasificacion::getArea() const
{
    return xarea;
}

void Clasificacion::setArea(const QString &value)
{
    xarea = value;
}

QString Clasificacion::getFormaPago() const
{
    return xformaPago;
}

void Clasificacion::setFormaPago(const QString &value)
{
    xformaPago = value;
}

double Clasificacion::getValor() const
{
    return xvalor;
}

void Clasificacion::setValor(double value)
{
    xvalor = value;
}

bool Clasificacion::isActivo() const
{
    return xactivo;
}

void Clasificacion::setActivo(bool value)
{
    xactivo = value;
}

QString Clasificacion::getFecha() const
{
    return xfecha;
}
