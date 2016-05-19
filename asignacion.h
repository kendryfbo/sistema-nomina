#ifndef ASIGNACION_H
#define ASIGNACION_H

#include <QString>
#include <QStringList>

class Asignacion
{
    // enum class Tipo {fijo,opcional};
    enum class Forma {porcentaje,monto};

public:

    Asignacion();
    Asignacion(QString codigo, QString descripcion, QString forma, double valor, QString formula,bool prima, bool activo);
    Asignacion(QString codigo,QString descripcion,QString forma,double valor, QString formula,bool prima, bool activo,QString fecha);

    QString getCodigo() const;

    QString getDescripcion() const;
    void setDescripcion(const QString &value);

    QString getForma() const;
    void setForma(const QString &value);
    QString formaToString(Forma forma);
    Forma stringToForma(QString forma);

    double getValor() const;
    void setValor(double value);

    QString getFormula() const;
    void setFormula(const QString &value);

    QString getFecha() const;

    bool isActivo() const;
    void setActivo(bool value);

    bool hasPrima() const;
    void setPrima(bool value);

private:
    QString xcodigo;
    QString xdescripcion;
    QString xforma;
    double xvalor;
    QString xformula;
    QString xfecha;
    bool xprima;
    bool xactivo;
};
#endif // ASIGNACION_H
