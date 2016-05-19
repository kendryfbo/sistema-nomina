#ifndef AREAWIDGET_H
#define AREAWIDGET_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#include "areamodel.h"
#include "coduppercasevalidator.h"
#include "uppercasevalidator.h"

namespace Ui {
class AreaWidget;
}

class AreaWidget : public QWidget
{
    Q_OBJECT

public:
    enum class State{agregar,modificar,inicial};

    explicit AreaWidget(QWidget *parent = 0);
    ~AreaWidget();

    CodUpperCaseValidator codigoValidador;
    UpperCaseValidator upperCaseValidador;

private slots:

    void clasificacionTableViewSelectionChange();

    void on_agregarPushButton_clicked();

    void on_modificarPushButton_clicked();

    void on_cancelarPushButton_clicked();

    void on_accionPushButton_clicked();

    void on_eliminarPushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_codigoLineEdit_editingFinished();

private:
    Ui::AreaWidget *ui;

    State state;

    AreaModel* model;
    QSqlQueryModel* tableModel;
    QSqlQueryModel* areaModel;
    QSqlQueryModel* tipoModel;


    Clasificacion clasificacion;

    void prepareWidget();
    void setState(State xstate);
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();

    void agregarClasificacion();
    void modificarClasificacion();
    void eliminarClasificacion();

    void updateTableView(QString str="");
    void UpdateAreaBusqComboBox();
    void updateAreaComboBox(QString str="");
    void cargarClasificacion(Clasificacion clasificacion);
    Clasificacion descargarClasificacion();

    void setValidadores();
    bool validarDatos();
};

#endif // AREAWIDGET_H
