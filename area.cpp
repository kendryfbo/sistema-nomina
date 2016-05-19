#include "area.h"

Area::Area()
{

}

Area::Area(QString codigo, QString descripcion,bool activo)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xactivo = activo;
}

Area::Area(QString codigo, QString descripcion,bool activo, QString fecha)
{
    xcodigo = codigo;
    xdescripcion = descripcion;
    xactivo = activo;
    xfecha = fecha;
}

QString Area::getCodigo() const
{
    return xcodigo;
}

QString Area::getDescripcion() const
{
    return xdescripcion;
}

void Area::setDescripcion(const QString &value)
{
    xdescripcion = value;
}

bool Area::isActivo() const
{
    return xactivo;
}

void Area::setActivo(bool value)
{
    xactivo = value;
}

QString Area::getFecha() const
{
    return xfecha;
}
