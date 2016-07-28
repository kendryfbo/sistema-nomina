#include "aportefaovinsertdialog.h"
#include "ui_aportefaovinsertdialog.h"

aporteFaovInsertDialog::aporteFaovInsertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aporteFaovInsertDialog)
{
    ui->setupUi(this);
}

aporteFaovInsertDialog::~aporteFaovInsertDialog()
{
    delete ui;
}

QString aporteFaovInsertDialog::getDescripcion() const
{
    return descripcion;
}

double aporteFaovInsertDialog::getAporte() const
{
    return aporte;
}

void aporteFaovInsertDialog::on_aceptarPushButton_clicked()
{
    if (validarDatos())
    {
        descripcion = ui->descripcionLineEdit->text();
        aporte = ui->aporteEmpDoubleSpinBox->value();
        accept();
    }
}

void aporteFaovInsertDialog::on_cancelarPushButton_clicked()
{
    reject();
}

bool aporteFaovInsertDialog::validarDatos()
{
    QString advertencias = "";

    if (ui->descripcionLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Descripcion no Puede estar en Blanco<b> \n "+ advertencias;
        ui->descripcionLineEdit->setFocus();
    }

    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}