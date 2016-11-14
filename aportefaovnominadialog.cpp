#include "aportefaovnominadialog.h"
#include "ui_aportefaovnominadialog.h"

aporteFaovNominaDialog::aporteFaovNominaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aporteFaovNominaDialog)
{
    ui->setupUi(this);
    model = new AporteFaovModel("empleado","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
}

aporteFaovNominaDialog::~aporteFaovNominaDialog()
{
    delete ui;
}

bool aporteFaovNominaDialog::validarDatos()
{
    QString advertencias = "";


    if (ui->descripcionLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Descripcion no Puede estar en Blanco<b> \n "+ advertencias;
        ui->descripcionLineEdit->setFocus();
    }
    if (ui->porcentajeDoubleSpinBox->value() <= 0)
    {
        advertencias = "- <b>Campo Porcentaje debe ser mayor a 0<b> \n "+ advertencias;
        ui->porcentajeDoubleSpinBox->setFocus();
    }
    if (ui->cantidadSpinBox->value() <= 0)
    {
        advertencias = "- <b>Campo Cantidad debe ser mayor a 0<b> \n "+ advertencias;
        ui->cantidadSpinBox->setFocus();
    }

    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void aporteFaovNominaDialog::on_aceptarPushButton_clicked()
{
    if (validarDatos())
    {

    }


}










