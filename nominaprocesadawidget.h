#ifndef NOMINAPROCESADAWIDGET_H
#define NOMINAPROCESADAWIDGET_H

#include <QWidget>
#include <QMessageBox>

#include "nominamodel.h"
#include "reportmodel.h"
namespace Ui {
class NominaProcesadaWidget;
}

class NominaProcesadaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NominaProcesadaWidget(int nominaNum, QWidget *parent = 0);
    ~NominaProcesadaWidget();

private slots:

    void empleadoTableViewSelectionChange();

    void on_impirmirNominaPushButton_clicked();

    void on_imprimirReciboPushButton_clicked();

    void on_ImprimirRecibosPushButton_clicked();

private:
    Ui::NominaProcesadaWidget *ui;

    NominaModel* model;
    Nomina nomina;

    QSqlQueryModel* empTableModel;
    QSqlQueryModel* asignTableModel;
    QSqlQueryModel* deducTableModel;


    bool cargarNomina(int numero);

    void updateEmpleadosTableView(QString str = "");
    void updateAsignacionesTableView(QString cedulaEmp);
    void updateDeduccionesTableView(QString cedulaEmp);

    void prepareWidget();

    void eliminarNominaProcesada();
};

#endif // NOMINAPROCESADAWIDGET_H
