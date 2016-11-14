#ifndef APORTEFAOVNOMINADIALOG_H
#define APORTEFAOVNOMINADIALOG_H

#include <QDialog>
#include "aportefaovmodel.h"
#include <QMessageBox>
namespace Ui {
class aporteFaovNominaDialog;
}

class aporteFaovNominaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aporteFaovNominaDialog(QWidget *parent = 0);
    ~aporteFaovNominaDialog();

private slots:



    void on_aceptarPushButton_clicked();

private:
    Ui::aporteFaovNominaDialog *ui;

    AporteFaovModel* model;

    bool validarDatos();

};

#endif // APORTEFAOVNOMINADIALOG_H
