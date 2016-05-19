#ifndef NOMINACARGADAWIDGET_H
#define NOMINACARGADAWIDGET_H

#include <QWidget>
#include <QMessageBox>

#include "nominamodel.h"

namespace Ui {
class NominaCargadaWidget;
}

class NominaCargadaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NominaCargadaWidget(int nominaNum,QWidget *parent = 0);
    ~NominaCargadaWidget();

private slots:

    void empleadoTableViewSelectionChange();

    void on_agregarAsignacionPpushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_procesarNominaPushButton_clicked();

    void on_eliminarNominaPushButton_clicked();

private:
    Ui::NominaCargadaWidget *ui;
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

    void eliminarNominaCargada();
    bool procesarNomina();

};

#endif // NOMINACARGADAWIDGET_H
