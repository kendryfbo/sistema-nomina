#ifndef DEDUCCION_H
#define DEDUCCION_H

#include <QString>
#include <QStringList>

class Deduccion
{
    // enum class Tipo {fijo,opcional};
    enum class Forma {porcentaje,monto};

public:

    Deduccion();
    Deduccion(QString codigo,QString descripcion,QString forma,double valor,bool activo);
    Deduccion(QString codigo,QString descripcion,QString forma,double valor,QString fecha,bool activo);


    QString getCodigo() const;
    void setCodigo(const QString &value);

    QString getDescripcion() const;
    void setDescripcion(const QString &value);

    // Deshabilitado
    /*
    QString getTipo() const;
    void setTipo(const QString &value);
    QString tipoToString(Tipo tipo);
    Tipo stringToTipo(QString tipo);
    */
    QString getForma() const;
    void setForma(const QString &value);
    QString formaToString(Forma forma);
    Forma stringToForma(QString forma);

    double getValor() const;
    void setValor(double value);

    QString getFecha() const;
    
    bool isActivo() const;
    void setActivo(bool value);
    
    // Deshabilitado
    /*
    QStringList getCodCampo() const;
    void setCodCampo(const QStringList &value);
    */
    
    QString toString();
    
private:
    QString xcodigo;
    QString xdescripcion;
    // QString xtipo;
    QString xforma;
    double xvalor;
    QString xfecha;
    bool xactivo;
    // QStringList xcodCampo;
};

#endif // DEDUCCION_H
