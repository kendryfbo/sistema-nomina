#include "nominaprocesadawidget.h"
#include "ui_nominaprocesadawidget.h"
#include "LimeReport"
NominaProcesadaWidget::NominaProcesadaWidget(int nominaNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NominaProcesadaWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new NominaModel("nominaProcesada","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);

    if (!cargarNomina(nominaNum)){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    prepareWidget();


}

NominaProcesadaWidget::~NominaProcesadaWidget()
{
    delete model;
    delete ui;
}

void NominaProcesadaWidget::empleadoTableViewSelectionChange()
{
    QModelIndex myIndex= ui->empleadoTableView->model()->index(ui->empleadoTableView->currentIndex().row(),1);
    QString cedula = ui->empleadoTableView->model()->data(myIndex).toString();
    QString nombres = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("nombres").toString();
    QString apellidos = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("apellidos").toString();

    double salario = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("salario").toDouble();
    double deduccion = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("deduccion").toDouble();
    double asignacion = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("asignacion").toDouble();
    double pago = empTableModel->record(ui->empleadoTableView->currentIndex().row()).value("pago").toDouble();

    ui->cedulaLineEdit->setText(cedula);
    ui->nombresLineEdit->setText(nombres);
    ui->apellidosLineEdit->setText(apellidos);
    ui->numeroNominaLineEdit->setText("0000"+QString::number(nomina.getNumero()));
    ui->salarioDoubleSpinBox->setValue(salario);
    ui->deduccionDoubleSpinBox->setValue(deduccion);
    ui->asignaccionDoubleSpinBox->setValue(asignacion);
    ui->totalDoubleSpinBox->setValue(pago);

    updateAsignacionesTableView(cedula);
    updateDeduccionesTableView(cedula);
}

bool NominaProcesadaWidget::cargarNomina(int numero)
{
    if (model->nominaProcesadaExiste(numero))
    {
        nomina = model->findNominaProcesada(numero);
        return true;
    } else {
        return false;
    }
}

void NominaProcesadaWidget::updateEmpleadosTableView(QString str)
{
    if (ui->busquedaCampoComboBox->currentIndex() == 0)
        empTableModel->setQuery(model->findEmpleadosFromNominaProcesada(nomina.getNumero(),str,NominaModel::CampoEmp::cedula));
    else if (ui->busquedaCampoComboBox->currentIndex() == 1)
        empTableModel->setQuery(model->findEmpleadosFromNominaProcesada(nomina.getNumero(),str,NominaModel::CampoEmp::nombres));
    else if (ui->busquedaCampoComboBox->currentIndex() == 2)
        empTableModel->setQuery(model->findEmpleadosFromNominaProcesada(nomina.getNumero(),str,NominaModel::CampoEmp::apellidos));
    else
        empTableModel->setQuery(model->findEmpleadosFromNominaProcesada(nomina.getNumero(),str,NominaModel::CampoEmp::cedula));

    ui->empleadoTableView->setModel(empTableModel);
    ui->empleadoTableView->hideColumn(4);
    ui->empleadoTableView->hideColumn(5);
    ui->empleadoTableView->hideColumn(6);
    ui->empleadoTableView->hideColumn(7);

    ui->empleadoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(ui->empleadoTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(empleadoTableViewSelectionChange()));
}

void NominaProcesadaWidget::updateAsignacionesTableView(QString cedulaEmp)
{
    asignTableModel->setQuery(model->findAsignNomProcesadaFromEmp(nomina.getNumero(),cedulaEmp));
    ui->asignacionTableView->setModel(asignTableModel);
    ui->asignacionTableView->hideColumn(0);
    ui->asignacionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void NominaProcesadaWidget::updateDeduccionesTableView(QString cedulaEmp)
{
    deducTableModel->setQuery(model->findDeduccNomProcesadaCargadasFromEmp(nomina.getNumero(),cedulaEmp));
    ui->deduccionTableView->setModel(deducTableModel);
    ui->deduccionTableView->hideColumn(0);
    ui->deduccionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void NominaProcesadaWidget::prepareWidget()
{
    empTableModel = new QSqlQueryModel(this);
    asignTableModel = new QSqlQueryModel(this);
    deducTableModel = new QSqlQueryModel(this);
    updateEmpleadosTableView();
    ui->empleadoTableView->selectRow(0);
}

void NominaProcesadaWidget::eliminarNominaProcesada()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    if (msg.question(this,"Advertencia","¿Desea Eliminar Nomina Procesada? ") == QMessageBox::Yes){

        if (model->deleteNominaProcesada(nomina.getNumero()))
        {
            QMessageBox::information(this,"Información",model->getStatusMessage(),QMessageBox::Ok);
            this->close();
        }
        else
            QMessageBox::critical(this,"Error",model->getStatusMessage(),QMessageBox::Ok);
    }
}

void NominaProcesadaWidget::on_impirmirNominaPushButton_clicked()
{
    ReportModel report;

    report.nomina(nomina.getNumero());
}

void NominaProcesadaWidget::on_imprimirReciboPushButton_clicked()
{
    ReportModel report;

    report.reciboEmpleado(nomina.getNumero(),ui->cedulaLineEdit->text());
}

void NominaProcesadaWidget::on_ImprimirRecibosPushButton_clicked()
{
    ReportModel report;

    report.recibosEmpleados(nomina.getNumero());
}

void NominaProcesadaWidget::on_eliminarNominaPushButton_clicked()
{

}

void NominaProcesadaWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateEmpleadosTableView(arg1);
}
