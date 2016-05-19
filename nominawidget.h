#ifndef NOMINAWIDGET_H
#define NOMINAWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "nominamodel.h"

namespace Ui {
class NominaWidget;
}

class NominaWidget : public QWidget
{
    Q_OBJECT

public:

    enum class State{agregar,modificar,inicial};

    explicit NominaWidget(QWidget *parent = 0);
    ~NominaWidget();

private slots:

    void nominaTableViewSelectionChange();

    void on_accionPushButton_clicked();

    void on_agregarPushButton_clicked();

    void on_modificarPushButton_clicked();

    void on_EliminarPushButton_clicked();

    void on_cancelarPushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

private:
    Ui::NominaWidget *ui;

     State state;

    NominaModel* model;
    QSqlQueryModel* tableModel;

    void prepareWidget();
    void setState(State xstate);
    void setValidators();
    void stateAgregar();
    void stateModificar();
    void stateInicial();
    void cancelar();
    void status();

    void agregarNomina();
    void ModificarNomina();
    void eliminarNomina();

    void updateNominaTableView(QString str="");

    void setValidadores();
    bool validarDatos();
};

#endif // NOMINAWIDGET_H
