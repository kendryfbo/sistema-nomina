#include "nomina.h"

Nomina::Nomina()
{
    xdescripcion = "";
    xdias = 0;
    xfechaPago = "2016-04-24";
    xfechaDesde  = "2016-04-01";
    xfechaHasta  = "2016-04-24";
    xuserId  = "userId";
}

Nomina::Nomina(QString descripcion, int dias, double salario, double deduccion, double asignacion, QString fechaPago, QString fechaDesde, QString fechaHasta, QString userId)
{
    xdescripcion = descripcion;
    xdias = dias;
    xfechaPago = fechaPago;
    xfechaDesde  = fechaDesde;
    xfechaHasta  = fechaHasta;
    xuserId  = userId;
    xsalario = salario;
    xdeduccion = deduccion;
    xasignacion = asignacion;

}

Nomina::Nomina( int numero, QString descripcion, int dias, double salario, double deduccion, double asignacion, QString fechaPago, QString fechaDesde, QString fechaHasta, QString userId, QString fecha)
{
    xnumero = numero;
    xdescripcion = descripcion;
    xdias = dias;
    xfechaPago = fechaPago;
    xfechaDesde  = fechaDesde;
    xfechaHasta  = fechaHasta;
    xuserId  = userId;
    xfecha = fecha;
    xsalario = salario;
    xdeduccion = deduccion;
    xasignacion = asignacion;
}

int Nomina::getNumero() const
{
    return xnumero;
}

QString Nomina::getDescripcion() const
{
    return xdescripcion;
}

int Nomina::getDias() const
{
    return xdias;
}

QString Nomina::getFechaPago() const
{
    return xfechaPago;
}

QString Nomina::getFechaDesde() const
{
    return xfechaDesde;
}

QString Nomina::getFechaHasta() const
{
    return xfechaHasta;
}

QString Nomina::getUserId() const
{
    return xuserId;
}

QString Nomina::getFecha() const
{
    return xfecha;
}

double Nomina::getSalario() const
{
    return xsalario;
}

double Nomina::getDeduccion() const
{
    return xdeduccion;
}

double Nomina::getAsignacion() const
{
    return xasignacion;
}
