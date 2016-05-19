#include "asignaciondialog.h"
#include "ui_asignaciondialog.h"

AsignacionDialog::AsignacionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsignacionDialog)
{
    ui->setupUi(this);

    model = new AsignacionModel("asignacionDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

AsignacionDialog::~AsignacionDialog()
{
    delete model;
    delete ui;
}

void AsignacionDialog::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    updateTableView();
}

void AsignacionDialog::updateTableView(QString str)
{
    if (ui->busquedaComboBox->currentIndex() == 0)
        tableModel->setQuery(model->findAsignaciones(str,false,AsignacionModel::Campo::descripcion));
    else if (ui->busquedaComboBox->currentIndex() == 1)
        tableModel->setQuery(model->findAsignaciones(str,false,AsignacionModel::Campo::codigo));
    else
        tableModel->setQuery(model->findAsignaciones(str,false,AsignacionModel::Campo::descripcion));

    ui->asignacionTableView->setModel(tableModel);
    QObject::connect(ui->asignacionTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(asignacionTableViewSelectionChange()));
}

bool AsignacionDialog::validarDatos()
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

void AsignacionDialog::on_aceptarPushButton_clicked()
{
    if (validarDatos())
    {
        codigo = ui->codigoLineEdit->text();
        cantidad = ui->cantidadSpinBox->value();
        accept();
    }
}

void AsignacionDialog::on_CancelarPushButton_clicked()
{
    reject();
}

void AsignacionDialog::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableView(arg1);
}

void AsignacionDialog::on_asignacionTableView_doubleClicked(const QModelIndex &index)
{
    (void) index;
    ui->cantidadSpinBox->setFocus();
    ui->cantidadSpinBox->selectAll();
}

void AsignacionDialog::on_asignacionTableView_entered(const QModelIndex &index)
{
    (void) index;
    ui->cantidadSpinBox->setFocus();
    ui->cantidadSpinBox->selectAll();
}

int AsignacionDialog::getCantidad() const
{
    return cantidad;
}

void AsignacionDialog::asignacionTableViewSelectionChange()
{
    QModelIndex myIndex= ui->asignacionTableView->model()->index(ui->asignacionTableView->currentIndex().row(),0);
    QString codigo = ui->asignacionTableView->model()->data(myIndex).toString();
    asignacion = Asignacion(model->findAsignacion(codigo));

    if (!(asignacion.getCodigo() == "DEFAULT")) {
        ui->codigoLineEdit->setText(asignacion.getCodigo());
        ui->descripcionLineEdit->setText(asignacion.getDescripcion());
    }
}

QString AsignacionDialog::getCodigo() const
{
    return codigo;
}
