#include "deducciondialog.h"
#include "ui_deducciondialog.h"

DeduccionDialog::DeduccionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeduccionDialog)
{
    ui->setupUi(this);

    model = new DeduccionModel("deduccionDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

DeduccionDialog::~DeduccionDialog()
{
    delete model;
    delete ui;
}

void DeduccionDialog::deduccionTableViewSelectionChange()
{
    QModelIndex myIndex= ui->deduccionTableView->model()->index(ui->deduccionTableView->currentIndex().row(),0);
    QString codigo = ui->deduccionTableView->model()->data(myIndex).toString();
    deduccion = Deduccion(model->findDeduccion(codigo));

    if (!(deduccion.getCodigo() == "DEFAULT")) {
        ui->codigoLineEdit->setText(deduccion.getCodigo());
        ui->descripcionLineEdit->setText(deduccion.getDescripcion());
    }
}

void DeduccionDialog::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    updateTableView();
}

void DeduccionDialog::updateTableView(QString str)
{
    if (ui->busquedaComboBox->currentIndex() == 0)
        tableModel->setQuery(model->findDeducciones(str,false,DeduccionModel::Campo::descripcion));
    else if (ui->busquedaComboBox->currentIndex() == 1)
        tableModel->setQuery(model->findDeducciones(str,false,DeduccionModel::Campo::codigo));
    else
        tableModel->setQuery(model->findDeducciones(str,false,DeduccionModel::Campo::descripcion));

    ui->deduccionTableView->setModel(tableModel);
    QObject::connect(ui->deduccionTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(deduccionTableViewSelectionChange()));
}

bool DeduccionDialog::validarDatos()
{
    QString advertencias = "";

    if (ui->cantidadSpinBox->value()==0)
    {
        advertencias = "- <b>Campo Cantidad debe ser mayor a 0 <b> \n"+ advertencias;
        ui->cantidadSpinBox->setFocus();
        ui->cantidadSpinBox->selectAll();
    }
     if (ui->descripcionLineEdit->text().isEmpty())
     {
         advertencias = "- <b>Campo Descripción no Puede estar en Blanco<b> \n"+ advertencias;
         ui->busquedaLineEdit->setFocus();
     }
    if (ui->codigoLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Código no Puede estar en Blanco<b> \n"+ advertencias;
        ui->busquedaLineEdit->setFocus();
    }
    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void DeduccionDialog::on_aceptarPushButton_clicked()
{
    if (validarDatos())
    {
        codigo = ui->codigoLineEdit->text();
        cantidad = ui->cantidadSpinBox->value();
        accept();
    }
}

void DeduccionDialog::on_CancelarPushButton_clicked()
{
    reject();
}

int DeduccionDialog::getCantidad() const
{
    return cantidad;
}

QString DeduccionDialog::getCodigo() const
{
    return codigo;
}

void DeduccionDialog::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableView(arg1);
}

void DeduccionDialog::on_deduccionTableView_doubleClicked(const QModelIndex &index)
{
    (void) index;
    ui->cantidadSpinBox->setFocus();
    ui->cantidadSpinBox->selectAll();
}

void DeduccionDialog::on_deduccionTableView_entered(const QModelIndex &index)
{
    (void) index;
    ui->cantidadSpinBox->setFocus();
    ui->cantidadSpinBox->selectAll();
}
