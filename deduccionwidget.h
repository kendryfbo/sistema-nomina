#ifndef DEDUCCIONWIDGET_H
#define DEDUCCIONWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtSql>
#include <QMessageBox>

#include "deduccionmodel.h"

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

private slots:

    void deduccionTableViewSelectionChange();

    void on_cancelarPushButton_clicked();
    void on_agregarPushButton_clicked();
    void on_modificarPushButton_clicked();
    void on_eliminarPushButton_clicked();
    void on_accionPushButton_clicked();

    void on_FormaComboBox_currentIndexChanged(int index);

private:
    Ui::DeduccionWidget *ui;

    State state;
    DeduccionModel* model;
    QSqlQueryModel* tableModel;

    Deduccion deduccion;

    void prepareWidget();
    void setState(State xstate);
    void setValidators();
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();
    void agregarDeduccion();
    void modificarDeduccion();
    void eliminarDeduccion();

    void updateTableView(QString str="");

    void cargarDeduccion(Deduccion deduccion);
    Deduccion descargarDeduccion();

    void updateValorDoubleSpinBoxParameters(int index);
};

#endif // DEDUCCIONWIDGET_H
