#include "vacacion.h"

Vacacion::Vacacion(QString xDescripcion,QString xArea,QString xFechaPago)
{
    descripcion = xDescripcion;
    area = xArea;
    fechaPago = xFechaPago;
}
Vacacion::Vacacion(int xNumero, QString xDescripcion, QString xArea, QString xFechaPago, QString xFechaCreacion)
{
    numero = xNumero;
    descripcion = xDescripcion;
    area = xArea;
    fechaPago = xFechaPago;
    fechaCreacion = xFechaCreacion;
}

int Vacacion::getNumero() const
{
    return numero;
}

QString Vacacion::getDescripcion() const
{
    return descripcion;
}

QString Vacacion::getArea() const
{
    return area;
}

QString Vacacion::getFechaPago() const
{
    return fechaPago;
}

QString Vacacion::getFechaCreacion() const
{
    return fechaCreacion;
}
