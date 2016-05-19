#ifndef AREA_H
#define AREA_H

#include <QtCore>

class Area
{
public:
    Area();
    Area(QString codigo, QString descripcion,bool activo);
    Area(QString codigo, QString descripcion,bool activo, QString fecha);

    QString getCodigo() const;

    QString getDescripcion() const;
    void setDescripcion(const QString &value);

    bool isActivo() const;
    void setActivo(bool value);

    QString getFecha() const;

private:

    QString xcodigo;
    QString xdescripcion;
    bool xactivo;
    QString xfecha;
};

#endif // AREA_H
