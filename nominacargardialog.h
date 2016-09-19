#ifndef NOMINACARGARDIALOG_H
#define NOMINACARGARDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "nominamodeldialog.h"
#include "nominamodel.h"
#include "areamodel.h"
#include "uppercasevalidator.h"
#include "coduppercasevalidator.h"

namespace Ui {
class NominaCargarDialog;
}

class NominaCargarDialog : public QDialog
{
    Q_OBJECT

public:

    enum class State{inactive,active};

    explicit NominaCargarDialog(QWidget *parent = 0);
    ~NominaCargarDialog();


    UpperCaseValidator upperCaseValidador;

private slots:

    void on_pushButton_clicked();

    void on_cancelarPushButton_clicked();

    void on_cargarNominaPushButton_clicked();

private:
    Ui::NominaCargarDialog *ui;
    State state;
    NominaModelDialog* nominaModelDialog;
    QSqlQueryModel* areaModel;
    bool NominaModeloIsCargada;

    AreaModel* area;

    void setState(State xstate);

    void stateInactive();
    void stateActive();

    void prepareDialog();

    void updateAreaComboBox();
    void buscarNominaModel();
    void cargarDatosNominaModel();

    void cargarNomina();

    bool validarDatos();
    void setValidadores();
};

#endif // NOMINACARGARDIALOG_H
