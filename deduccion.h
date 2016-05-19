#ifndef DEDUCCION_H
#define DEDUCCION_H

#include <QString>
#include <QStringList>

class Deduccion
{

    enum class Forma {porcentaje,monto};

public:

    Deduccion();
    Deduccion(QString codigo, QString descripcion, QString forma, double valor, QString formula, bool activo);
    Deduccion(QString codigo,QString descripcion,QString forma,double valor, QString formula, QString fecha,bool activo);


    QString getCodigo() const;

    QString getDescripcion() const;
    void setDescripcion(const QString &value);

    QString getForma() const;
    void setForma(const QString &value);

    QString formaToString(Forma forma);
    Forma stringToForma(QString forma);

    double getValor() const;
    void setValor(double value);

    QString getFecha() const;
    
    bool isActivo() const;
    void setActivo(bool value);
    
    QString getFormula() const;
    void setFormula(const QString &value);

    QString toString();

private:
    QString xcodigo;
    QString xdescripcion;
    QString xforma;
    double xvalor;
    QString xformula;
    QString xfecha;
    bool xactivo;
};

#endif // DEDUCCION_H
