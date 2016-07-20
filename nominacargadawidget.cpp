#include "nominacargadawidget.h"
#include "ui_nominacargadawidget.h"

NominaCargadaWidget::NominaCargadaWidget(int nominaNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NominaCargadaWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new NominaModel("nominaCargada","127.0.0.1","nomina","root","19017070",3306);

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

NominaCargadaWidget::~NominaCargadaWidget()
{
    delete model;
    delete ui;
}

void NominaCargadaWidget::empleadoTableViewSelectionChange()
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

bool NominaCargadaWidget::cargarNomina(int numero)
{
    if (model->nominaExiste(numero))
    {
        nomina = model->findNominaCargada(numero);
        return true;
    } else {
        return false;
    }
}

void NominaCargadaWidget::updateEmpleadosTableView(QString str)
{

    if (ui->busquedaCampoComboBox->currentIndex() == 0)
        empTableModel->setQuery(model->findEmpleadosFromNominaCargada(nomina.getNumero(),str,NominaModel::CampoEmp::cedula));
    else if (ui->busquedaCampoComboBox->currentIndex() == 1)
        empTableModel->setQuery(model->findEmpleadosFromNominaCargada(nomina.getNumero(),str,NominaModel::CampoEmp::nombres));
    else if (ui->busquedaCampoComboBox->currentIndex() == 2)
        empTableModel->setQuery(model->findEmpleadosFromNominaCargada(nomina.getNumero(),str,NominaModel::CampoEmp::apellidos));
    else
        empTableModel->setQuery(model->findEmpleadosFromNominaCargada(nomina.getNumero(),str,NominaModel::CampoEmp::cedula));

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

void NominaCargadaWidget::updateAsignacionesTableView(QString cedulaEmp)
{
    asignTableModel->setQuery(model->findAsignNomCargadaFromEmp(nomina.getNumero(),cedulaEmp));
    ui->asignacionTableView->setModel(asignTableModel);
    ui->asignacionTableView->hideColumn(0);
    ui->asignacionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void NominaCargadaWidget::updateDeduccionesTableView(QString cedulaEmp)
{
    deducTableModel->setQuery(model->findDeduccNomCargadasFromEmp(nomina.getNumero(),cedulaEmp));
    ui->deduccionTableView->setModel(deducTableModel);
    ui->deduccionTableView->hideColumn(0);
    ui->deduccionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void NominaCargadaWidget::prepareWidget()
{
    empTableModel = new QSqlQueryModel(this);
    asignTableModel = new QSqlQueryModel(this);
    deducTableModel = new QSqlQueryModel(this);
    updateEmpleadosTableView();
    ui->empleadoTableView->selectRow(0);
}

void NominaCargadaWidget::eliminarNominaCargada()
{
        QMessageBox msg;
        msg.setModal(true);
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        if (msg.question(this,"Advertencia","¿Desea Eliminar Nomina Cargada? ") == QMessageBox::Yes){
            model->deleteNominaCargada(nomina.getNumero());
            QMessageBox::information(this,"Información",model->getStatusMessage(),QMessageBox::Ok);
            this->close();
        }
}

bool NominaCargadaWidget::procesarNomina()
{
    if (model->procesarNomina(nomina.getNumero()))
    {
        QMessageBox::information(this,"Nomina","Nomina procesada Exitosamente",QMessageBox::Ok);
        this->close();
        return true;
    }
    QMessageBox::critical(this,"ERROR Nomina",model->getStatusMessage(),QMessageBox::Ok);
    return false;
}

void NominaCargadaWidget::agregarDeduccion()
{
    DeduccionDialog* deduccD = new DeduccionDialog(this);

    if (deduccD->exec() == QDialog::Accepted)
    {
        QString empCedula = ui->cedulaLineEdit->text();
        model->agregarDeduccionEmpleado(deduccD->getCodigo(),empCedula,nomina.getNumero(),deduccD->getCantidad());

        int position = ui->empleadoTableView->currentIndex().row();
        updateEmpleadosTableView();
        ui->empleadoTableView->selectRow(position);
    }
}

void NominaCargadaWidget::AgregarAsignacion()
{
    AsignacionDialog* asignD = new AsignacionDialog(this);

    if (asignD->exec() == QDialog::Accepted)
    {
        QString empCedula = ui->cedulaLineEdit->text();
        model->agregarASignacionEmpleado(asignD->getCodigo(),empCedula,nomina.getNumero(),asignD->getCantidad());

        int position = ui->empleadoTableView->currentIndex().row();
        updateEmpleadosTableView();
        ui->empleadoTableView->selectRow(position);
    }
}

void NominaCargadaWidget::eliminarDeduccion()
{
    int row = ui->deduccionTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = deducTableModel->record(row).value("codigo").toString();
        QString empCedula = ui->cedulaLineEdit->text();
        model->eliminarDeduccionEmpleado(codigo,empCedula,nomina.getNumero());

        int position = ui->empleadoTableView->currentIndex().row();
        updateEmpleadosTableView();
        ui->empleadoTableView->selectRow(position);
    }
}

void NominaCargadaWidget::eliminarAsignacion()
{
    int row = ui->asignacionTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = asignTableModel->record(row).value("codigo").toString();
        QString empCedula = ui->cedulaLineEdit->text();
        model->eliminarASignacionEmpleado(codigo,empCedula,nomina.getNumero());

        int position = ui->empleadoTableView->currentIndex().row();
        updateEmpleadosTableView();
        ui->empleadoTableView->selectRow(position);
    }
}

void NominaCargadaWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateEmpleadosTableView(arg1);
}

void NominaCargadaWidget::on_procesarNominaPushButton_clicked()
{
    procesarNomina();
}

void NominaCargadaWidget::on_eliminarNominaPushButton_clicked()
{
    eliminarNominaCargada();
}

void NominaCargadaWidget::on_agregarAsignacionPpushButton_clicked()
{
    AgregarAsignacion();
}

void NominaCargadaWidget::on_eliminarAsignacionPushButton_clicked()
{
    eliminarAsignacion();
}

void NominaCargadaWidget::on_agregarDeduccionPushButton_clicked()
{
    agregarDeduccion();
}

void NominaCargadaWidget::on_eliminarDeduccionPushButton_clicked()
{
    eliminarDeduccion();
}

void NominaCargadaWidget::on_anticipoPushButton_clicked()
{
    AnticipoListaDialog* anticipoDialog = new AnticipoListaDialog(this);

    if (anticipoDialog->exec()){
        if (!model->cargarAnticipos(anticipoDialog->getAnticipoId(),nomina.getNumero())){
                QMessageBox::warning(this,"ERROR",model->getStatusMessage());
        }
    }
}
