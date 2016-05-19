#ifndef DEDUCCIONDIALOG_H
#define DEDUCCIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "deduccionmodel.h"

namespace Ui {
class DeduccionDialog;
}

class DeduccionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeduccionDialog(QWidget *parent = 0);
    ~DeduccionDialog();



    QString getCodigo() const;
    int getCantidad() const;

private slots:

    void deduccionTableViewSelectionChange();

    void on_aceptarPushButton_clicked();

    void on_CancelarPushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_deduccionTableView_doubleClicked(const QModelIndex &index);

    void on_deduccionTableView_entered(const QModelIndex &index);

private:
    Ui::DeduccionDialog *ui;

    DeduccionModel* model;
    Deduccion deduccion;
    QSqlQueryModel* tableModel;
    QString codigo;
    int cantidad;


    void prepareWidget();

    void updateTableView(QString str="");

    bool validarDatos();
};

#endif // DEDUCCIONDIALOG_H
