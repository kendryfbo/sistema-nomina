#include "nominamodeldialog.h"
#include "ui_nominamodeldialog.h"

NominaModelDialog::NominaModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NominaModelDialog)
{
    ui->setupUi(this);
    model = new NominaModel("nominaModelDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareDialog();
}

NominaModelDialog::NominaModelDialog(QString codigo)
{
    model = new NominaModel("nominaModelDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }else {
        QSqlQuery myQuery = model->findNominaModel(codigo);
        if (!(codigo == "")) {
            codigo = myQuery.value("codigo").toString();
            descripcion = myQuery.value("descripcion").toString();
            salario = myQuery.value("sueldo_porc").toDouble();
            deduccion = myQuery.value("deducc_porc").toDouble();
            asignacion = myQuery.value("asignac_porc").toDouble();
            accepted();
        }else
            rejected();
    }
}

NominaModelDialog::~NominaModelDialog()
{
    delete model;
    delete ui;
}

void NominaModelDialog::nominaModelTableViewSelectionChange()
{
    QModelIndex myIndex= ui->nominaModelTableView->model()->index(ui->nominaModelTableView->currentIndex().row(),0);
    QString xcodigo = ui->nominaModelTableView->model()->data(myIndex).toString();
    QSqlQuery myQuery = model->findNominaModel(xcodigo);
    if (!(xcodigo == "")) {
        codigo = myQuery.value("codigo").toString();
        descripcion = myQuery.value("descripcion").toString();
        dias = myQuery.value("dias").toInt();
        salario = myQuery.value("sueldo_porc").toDouble();
        deduccion = myQuery.value("deducc_porc").toDouble();
        asignacion = myQuery.value("asignac_porc").toDouble();
    }
}

void NominaModelDialog::updateNominaModelTableView(QString str)
{
    tableModel->setQuery(model->findNominasModel(str));

    ui->nominaModelTableView->setModel(tableModel);
    ui->nominaModelTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(ui->nominaModelTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(nominaModelTableViewSelectionChange()));
}

void NominaModelDialog::inicializarVariables()
{
    codigo = "";
    descripcion = "";
    dias = 0;
    salario=0;
    deduccion=0;
    asignacion=0;
}

void NominaModelDialog::on_aceptarPushButton_clicked()
{
    accept();
}

void NominaModelDialog::prepareDialog()
{
    tableModel = new QSqlQueryModel(this);
    inicializarVariables();
    updateNominaModelTableView();
    ui->nominaModelTableView->selectRow(0);
}

void NominaModelDialog::on_cancelarPushButton_clicked()
{
    reject();
}

double NominaModelDialog::getAsignacion() const
{
    return asignacion;
}

void NominaModelDialog::buscarCodigoModeloNomina(QString codigo)
{
    if (!model->nominaModelExist(codigo))
        reject();
    else {
        QSqlQuery myQuery = model->findNominaModel(codigo);
        codigo = myQuery.value("codigo").toString();
        descripcion = myQuery.value("descripcion").toString();
        salario = myQuery.value("sueldo_porc").toDouble();
        deduccion = myQuery.value("deducc_porc").toDouble();
        asignacion = myQuery.value("asignac_porc").toDouble();
        accept();
    }
}

double NominaModelDialog::getDeduccion() const
{
    return deduccion;
}

double NominaModelDialog::getSalario() const
{
    return salario;
}

int NominaModelDialog::getDias() const
{
    return dias;
}

QString NominaModelDialog::getDescripcion() const
{
    return descripcion;
}

QString NominaModelDialog::getCodigo() const
{
    return codigo;
}
