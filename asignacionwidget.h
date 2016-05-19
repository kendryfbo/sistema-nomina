#ifndef ASIGNACIONWIDGET_H
#define ASIGNACIONWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtSql>
#include <QMessageBox>

#include "asignacionmodel.h"
#include "coduppercasevalidator.h"
#include "uppercasevalidator.h"

namespace Ui {
class AsignacionWidget;
}

class AsignacionWidget : public QWidget
{
    Q_OBJECT

public:

    enum class State{agregar,modificar,inicial};

    explicit AsignacionWidget(QWidget *parent = 0);
    ~AsignacionWidget();

    CodUpperCaseValidator codigoValidador;
    UpperCaseValidator upperCaseValidador;

private slots:

    void asignacionTableViewSelectionChange();

    void on_agregarPushButton_clicked();
    void on_modificarPushButton_clicked();
    void on_eliminarPushButton_clicked();

    void on_accionPushButton_clicked();


    void on_FormaComboBox_currentIndexChanged(int index);

    void on_busquedaLineEdit_textChanged(const QString &arg1);


    void on_codigoLineEdit_editingFinished();

    void on_cancelarPushButton_clicked();

private:
    Ui::AsignacionWidget *ui;

    State state;

    AsignacionModel* model;
    QSqlQueryModel* tableModel;
    QSqlQueryModel* formaModel;

    Asignacion asignacion;

    void prepareWidget();
    void setState(State xstate);
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();

    void agregarAsignacion();
    void modificarAsignacion();
    void eliminarAsignacion();

    void updateTableView(QString str="");
    void updateFormaComboBox(QString str="");
    void updateFormulaCombobox(QString str="");
    void cargarAsignacion(Asignacion asignacion);
    Asignacion descargarAsignacion();

    void updateFormaParameters();

    void setValidadores();
    bool validarDatos();

};

#endif // ASIGNACIONWIDGET_H
