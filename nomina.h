#ifndef NOMINA_H
#define NOMINA_H

#include <QtCore>

class Nomina
{
public:
    Nomina();
    Nomina(QString descripcion, int dias, double salario, double deduccion, double asignacion, QString fechaPago, QString fechaDesde, QString fechaHasta, QString userId);
    Nomina( int numero, QString descripcion, int dias, double salario, double deduccion, double asignacion, QString fechaPago, QString fechaDesde, QString fechaHasta, QString userId, QString fecha);

    int getNumero() const;

    QString getDescripcion() const;

    int getDias() const;

    QString getFechaPago() const;

    QString getFechaDesde() const;

    QString getFechaHasta() const;

    QString getUserId() const;

    QString getFecha() const;

    double getSalario() const;

    double getDeduccion() const;

    double getAsignacion() const;

private:

    int xnumero;
    QString xdescripcion;
    int xdias;
    QString xfechaPago;
    QString xfechaDesde;
    QString xfechaHasta;
    QString xuserId;
    QString xfecha;
    double xsalario;
    double xdeduccion;
    double xasignacion;


};

#endif // NOMINA_H
