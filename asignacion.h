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
    Asignacion(QString codigo,QString descripcion,QString forma,double valor);


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

    // Deshabilitado
    /*
    QStringList getCodCampo() const;
    void setCodCampo(const QStringList &value);
    */
private:
    QString xcodigo;
    QString xdescripcion;
    // QString xtipo;
    QString xforma;
    double xvalor;
    // QStringList xcodCampo;
};

#endif // ASIGNACION_H
