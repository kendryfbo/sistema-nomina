#ifndef NOMINAMODELDIALOG_H
#define NOMINAMODELDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "nominamodel.h"

namespace Ui {
class NominaModelDialog;
}

class NominaModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NominaModelDialog(QWidget *parent = 0);

    explicit NominaModelDialog(QString codigo);
    ~NominaModelDialog();

    QString getCodigo() const;
    QString getDescripcion() const;
    int getDias() const;
    double getSalario() const;
    double getDeduccion() const;
    double getAsignacion() const;


    void buscarCodigoModeloNomina(QString codigo);

private slots:
    
    void nominaModelTableViewSelectionChange();
    
    void on_aceptarPushButton_clicked();
    
    void on_cancelarPushButton_clicked();

private:
    Ui::NominaModelDialog *ui;

    NominaModel* model;
    QSqlQueryModel* tableModel;


    QString codigo;
    QString descripcion;
    int dias;
    double salario;
    double deduccion;
    double asignacion;
    
    
    void prepareDialog();
    void inicializarVariables();
    void updateNominaModelTableView(QString str = "");

};

#endif // NOMINAMODELDIALOG_H
