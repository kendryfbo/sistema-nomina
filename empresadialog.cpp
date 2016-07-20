#include "empresadialog.h"
#include "ui_empresadialog.h"

empresaDialog::empresaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::empresaDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new EmpresaModel("empresa","127.0.0.1","nomina","root","19017070",3306);
    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

empresaDialog::~empresaDialog()
{
    delete model;
    delete ui;
}

void empresaDialog::prepareWidget()
{
    descargarDatos();
}

void empresaDialog::descargarDatos()
{
   EmpresaModel::Empresa empresa;
   empresa = model->findEmpresa();
   ui->rifLineEdit->setText(empresa.rif);
   ui->descripcionLineEdit->setText(empresa.descripcion);
   ui->tlf1LineEdit->setText(empresa.tlf1);
   ui->tlf2LineEdit->setText(empresa.tlf2);
   ui->responsableLineEdit->setText(empresa.director);
   ui->DireccionLineEdit->setText(empresa.direccion);
   ui->cedulaLineEdit->setText(empresa.cedula);
   ui->mensajeLineEdit->setText(empresa.mensaje);
}

void empresaDialog::cargarDatos()
{
    EmpresaModel::Empresa empresa;
    empresa.rif = ui->rifLineEdit->text();
    empresa.descripcion = ui->descripcionLineEdit->text();
    empresa.direccion = ui->DireccionLineEdit->text();
    empresa.director = ui->responsableLineEdit->text();
    empresa.cedula = ui->cedulaLineEdit->text();
    empresa.tlf1 = ui->tlf1LineEdit->text();
    empresa.tlf2 = ui->tlf2LineEdit->text();
    empresa.mensaje = ui->mensajeLineEdit->text();

    model->update(empresa);
}

void empresaDialog::on_buttonBox_accepted()
{
    cargarDatos();
}
