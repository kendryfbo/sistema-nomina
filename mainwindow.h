#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logindialog.h"
#include "empleadowidget.h"
#include "deduccionwidget.h"
#include "asignacionwidget.h"
#include "areawidget.h"
#include "nominawidget.h"
#include "nominamodel.h"
#include "nominacargadawidget.h"
#include "nominaprocesadawidget.h"
#include "nominacargardialog.h"
#include "reportmodel.h"
#include "empresadialog.h"
#include "anticipowidget.h"
#include "anticipomodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void cargarDatosUsuario(Usuario user);

private slots:
    void on_actionDeduccion_triggered();

    void on_actionEmpleados_triggered();

    void on_actionAsignaciones_triggered();

    void on_actionClasificaciones_triggered();

    void on_actionNomina_triggered();

    void on_detalleNomProcPushButton_clicked();

    void on_ModificarNomCargadaPushButton_clicked();

    void on_imprimirNomProcPushButton_clicked();

    void on_nominaCargadaTableView_doubleClicked(const QModelIndex &index);

    void on_nominaProcesadaTableView_doubleClicked(const QModelIndex &index);

    void on_CargarNomPushButton_clicked();

    void updateTables();

    void on_EliminarNomProcPushButton_clicked();

    void on_actionConfiguracion_triggered();

    void on_generarAnticipoPushButton_clicked();

    void on_verAnticipoPushButton_clicked();

    void on_anticipoTableView_doubleClicked(const QModelIndex &index);

    void on_CargarNomPushButton_4_clicked();

    void on_eliminarAnticipoPushButton_clicked();

    void on_eliminarNomCargadaPushButton_clicked();

private:
    Ui::MainWindow *ui;

    LoginDialog* login;
    Usuario usuario;

    NominaModel* model;

    QLabel* userLabel;

    NominaCargadaWidget* NomCargadaW;
    NominaProcesadaWidget* nomProcesadaW;
    AnticipoWidget* anticipoW;

    QSqlQueryModel* nominaCargadaModel;
    QSqlQueryModel* nominaProcesadaModel;
    QSqlQueryModel* anticipoModel;

    void prepareWindow();
    void cargarStyleSheet();

    void updateNominaCargadaTableView();
    void updateNominaProcesadaTableView();
    void updateAnticipoTableView();
    void loadDatosEmpleados();

    void nominaCargadaWidget();
    void nominaProcesadaWidget();

    void imprimirNomina();

    void eliminarNominaProcesada();
    void eliminarNominaCargada();
};

#endif // MAINWINDOW_H
