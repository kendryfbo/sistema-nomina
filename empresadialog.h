#ifndef EMPRESADIALOG_H
#define EMPRESADIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "empresamodel.h"

namespace Ui {
class empresaDialog;
}

class empresaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit empresaDialog(QWidget *parent = 0);
    ~empresaDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::empresaDialog *ui;

    EmpresaModel* model;

    void prepareWidget();
    void descargarDatos();
    void cargarDatos();
};

#endif // EMPRESADIALOG_H
