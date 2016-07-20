#ifndef ANTICIPOLISTADIALOG_H
#define ANTICIPOLISTADIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "anticipomodel.h"

namespace Ui {
class AnticipoListaDialog;
}

class AnticipoListaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnticipoListaDialog(QWidget *parent = 0);
    ~AnticipoListaDialog();

    int getAnticipoId() const;

private slots:

    void on_busquedaLineEdit_textChanged(const QString &arg1);

    void on_aceptarPushButton_clicked();

    void on_cancelarPushButton_clicked();

private:
    Ui::AnticipoListaDialog *ui;

    AnticipoModel* model;

    QSqlQueryModel* anticipoModel;

    void prepareWidget();

    void updateTableAnticipo(QString descripcion="");

    void procesarAnticipo();

    int anticipoId;
};

#endif // ANTICIPOLISTADIALOG_H
