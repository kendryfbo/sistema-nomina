#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include <QtCore>

class Clasificacion
{

public:

    Clasificacion();
    Clasificacion(QString codigo,QString descripcion,QString area,QString formaPago,double valor,bool activo);
    Clasificacion(QString codigo,QString descripcion,QString area,QString formaPago,double valor,bool activo,QString fecha);


    QString getCodigo() const;

    QString getDescripcion() const;
    void setDescripcion(const QString &value);

    QString getArea() const;
    void setArea(const QString &value);

    QString getFormaPago() const;
    void setFormaPago(const QString &value);

    double getValor() const;
    void setValor(double value);

    bool isActivo() const;
    void setActivo(bool value);

    QString getFecha() const;

private:

    QString xcodigo;
    QString xdescripcion;
    QString xarea;
    QString xformaPago;
    double xvalor;
    bool xactivo;
    QString xfecha;


};

#endif // CLASIFICACION_H
