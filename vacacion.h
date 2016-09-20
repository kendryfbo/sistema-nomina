#ifndef VACACION_H
#define VACACION_H

#include <QString>
#include <QDate>

class Vacacion
{
public:
    // CONSTRUCTORS
    Vacacion(QString xDescripcion,QString xArea,QString xFechaPago);
    Vacacion(int xNumero,QString xDescripcion,QString xArea,QString xFechaPago,QString xFechaCreacion);

    // ATTR GETTERS
    int getNumero() const;
    QString getDescripcion() const;
    QString getArea() const;
    QString getFechaPago() const;
    QString getFechaCreacion() const;

private:

    int numero;
    QString descripcion;
    QString area;
    QString fechaPago;
    QString fechaCreacion;
};

#endif // VACACION_H
