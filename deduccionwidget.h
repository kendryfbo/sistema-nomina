#ifndef DEDUCCIONWIDGET_H
#define DEDUCCIONWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtSql>
#include <QMessageBox>

#include "deduccionmodel.h"
#include "coduppercasevalidator.h"
#include "uppercasevalidator.h"

namespace Ui {
class DeduccionWidget;
}

class DeduccionWidget : public QWidget
{
    Q_OBJECT

public:

    enum class State{agregar,modificar,inicial};

    explicit DeduccionWidget(QWidget *parent = 0);
    ~DeduccionWidget();


    CodUpperCaseValidator codigoValidador;
    UpperCaseValidator upperCaseValidador;



private slots:

    void deduccionTableViewSelectionChange();

    void on_cancelarPushButton_clicked();
    void on_agregarPushButton_clicked();
    void on_modificarPushButton_clicked();
    void on_eliminarPushButton_clicked();
    void on_accionPushButton_clicked();

    void on_FormaComboBox_currentIndexChanged(int index);

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_codigoLineEdit_editingFinished();

private:
    Ui::DeduccionWidget *ui;

    State state;
    DeduccionModel* model;
    QSqlQueryModel* tableModel;
    QSqlQueryModel* formaModel;

    Deduccion deduccion;

    void prepareWidget();
    void setState(State xstate);
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();
    void agregarDeduccion();
    void modificarDeduccion();
    void eliminarDeduccion();

    void updateTableView(QString str="");
    void updateFormaComboBox(QString str="");
    void updateFormulaCombobox(QString str="");
    void cargarDeduccion(Deduccion deduccion);
    Deduccion descargarDeduccion();

    void updateFormaParameters();

    void setValidadores();
    bool validarDatos();

};

#endif // DEDUCCIONWIDGET_H
