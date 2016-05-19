#ifndef ASIGNACIONDIALOG_H
#define ASIGNACIONDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "asignacionmodel.h"
namespace Ui {
class AsignacionDialog;
}

class AsignacionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AsignacionDialog(QWidget *parent = 0);
    ~AsignacionDialog();

    QString getCodigo() const;
    int getCantidad() const;

private slots:

    void asignacionTableViewSelectionChange();

    void on_aceptarPushButton_clicked();

    void on_CancelarPushButton_clicked();

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_asignacionTableView_doubleClicked(const QModelIndex &index);

    void on_asignacionTableView_entered(const QModelIndex &index);

private:
    Ui::AsignacionDialog *ui;

    AsignacionModel* model;
    Asignacion asignacion;
    QSqlQueryModel* tableModel;

    QString codigo;
    int cantidad;

    void prepareWidget();
    void updateTableView(QString str="");

    bool validarDatos();
};

#endif // ASIGNACIONDIALOG_H
