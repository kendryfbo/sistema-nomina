#ifndef EMPLEADOWIDGET_H
#define EMPLEADOWIDGET_H

#include <QtCore>
#include <QWidget>
#include <QMessageBox>

#include "deducciondialog.h"
#include "asignaciondialog.h"
#include "empleadomodel.h"
#include "nominaprocesadawidget.h"
#include "coduppercasevalidator.h"
#include "uppercasevalidator.h"
#include "aportefaovinsertdialog.h"

namespace Ui {
class EmpleadoWidget;
}

class EmpleadoWidget : public QWidget
{
    Q_OBJECT

public:

    enum class State{agregar,modificar,inicial};

    explicit EmpleadoWidget(QWidget *parent = 0);
    ~EmpleadoWidget();

    CodUpperCaseValidator codigoValidador;
    UpperCaseValidator upperCaseValidador;

private slots:

    void empleadoTableViewSelectionChange();

    void on_agregarPushButton_clicked();

    void on_modificarPushButton_clicked();

    void on_CancelarPushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_busquedaComboBox_currentIndexChanged(int index);

    void on_CampoComboBox_currentIndexChanged(int index);

    void on_eliminarDeduccFijaPushButton_clicked();

    void on_clasifcComboBox_currentIndexChanged(int index);

    void on_accionPushButton_clicked();

    void on_ProcNominaPushButton_clicked();

    void on_agrDeduccFijPushButton_clicked();

    void on_eliminarDeduccEventPushButton_clicked();

    void on_agrDeduccEvenPushButton_clicked();

    void on_agrAsignFijPushButton_clicked();

    void on_agrAsignEvenPushButton_clicked();

    void on_EliminarAsignFijaPushButton_clicked();

    void on_EliminarAsignEventPushButton_clicked();

    void on_nominaProcesadaTableView_doubleClicked(const QModelIndex &index);

    void on_cedulaLineEdit_editingFinished();

    void on_aporteFaovAgregarPushButton_clicked();

    void on_aporteFaovEliminarPushButton_clicked();

private:
    Ui::EmpleadoWidget *ui;
    State state;
    EmpleadoModel *model;
    Empleado empleado;

    QSqlQueryModel* empTableModel;
    QSqlQueryModel* campoModel;
    QSqlQueryModel* clasificModel;
    QSqlQueryModel* deducFijaModel;
    QSqlQueryModel* deducEventModel;
    QSqlQueryModel* asignFijaModel;
    QSqlQueryModel* asignEventModel;
    QSqlQueryModel* nominaModel;
    QSqlQueryModel* aporteFaovModel;


    void prepareWidget();
    void setState(State xstate);
    void setValidators();
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();

    void cargarEmpleado();
    void cargarDatosEmpleado();
    void cargarInfoLaboral();
    void cargarDeduccionesEmpelado();
    void cargarAsignacionesEmpelado();
    void cargarNominasEmpelado();
    void cargarAporteFaovEmpleado();

    Empleado descargarEmpleado();

    void updateEmpleadoTableView(QString str="");

    void updateDeduccFijaTableView();
    void updateDeduccEventTableView();
    void updateAsignFijaTableView();
    void updateAsignEventTableView();
    void updateNomProcTableView();
    void updateAporteFaovTableView();

    void updateCamposComboBox();
    void updateClasificacionComboBox();
    void updateFormaPago();
    void deleteDeduccion(QString codigo);
    void deleteAsignacion(QString codigo);

    void agregarEmpleado();
    void modificarEmpleado();
    void elimianrEmpleado();

    void setValidadores();
    bool validarDatos();

    void botonesDeTabla(bool sentinela);

    void nominaProcesadaWidget(int nominaNum);
};

#endif // EMPLEADOWIDGET_H
