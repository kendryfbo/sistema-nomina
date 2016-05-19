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
#include "LimeReport"

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

private:
    Ui::MainWindow *ui;

    LoginDialog* login;
    Usuario usuario;

    NominaModel* model;
    QLabel* userLabel;

    QSqlQueryModel* nominaCargadaModel;
    QSqlQueryModel* nominaProcesadaModel;

    void prepareWindow();
    void cargarStyleSheet();

    void updateNominaCargadaTableView();
    void updateNominaProcesadaTableView();
    void loadDatosEmpleados();

    void nominaCargadaWidget();
    void nominaProcesadaWidget();
};

#endif // MAINWINDOW_H
