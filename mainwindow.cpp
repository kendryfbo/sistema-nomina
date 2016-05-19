#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LimeReport"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new NominaModel("MainWindowNomina","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);

    prepareWindow();
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}


void MainWindow::prepareWindow()
{
    //cargarStyleSheet();
    nominaCargadaModel = new QSqlQueryModel(this);
    nominaProcesadaModel = new QSqlQueryModel(this);
    loadDatosEmpleados();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::cargarStyleSheet()
{
    QFile file(":/styleSheet/mainStyleSheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(styleSheet);
}

void MainWindow::updateNominaCargadaTableView()
{
    nominaCargadaModel->setQuery(model->findNominasCargadas());
    ui->nominaCargadaTableView->setModel(nominaCargadaModel);
    //ui->nominaCargadaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateNominaProcesadaTableView()
{
    nominaProcesadaModel->setQuery(model->findNominasProcesadas());
    ui->nominaProcesadaTableView->setModel(nominaProcesadaModel);
    //ui->nominaProcesadaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadDatosEmpleados()
{
    EmpleadoModel modelEmp("MainWindowEmp","127.0.0.1","nomina","root","19017070",3306);
    int empActivo = modelEmp.findEmpleados("",EmpleadoModel::Campo::cedula,EmpleadoModel::Status::activo).size();
    int empInactivo = modelEmp.findEmpleados("",EmpleadoModel::Campo::cedula,EmpleadoModel::Status::inactivo).size();
    int empVacacion = modelEmp.findEmpleados("",EmpleadoModel::Campo::cedula,EmpleadoModel::Status::vacacion).size();
    int empReposo = modelEmp.findEmpleados("",EmpleadoModel::Campo::cedula,EmpleadoModel::Status::reposo).size();

    ui->activoLineEdit->setText(QString::number(empActivo));
    ui->inactivoLineEdit->setText(QString::number(empInactivo));
    ui->vacacionLineEdit->setText(QString::number(empVacacion));
    ui->reposoLineEdit->setText(QString::number(empReposo));
}

void MainWindow::nominaCargadaWidget()
{
    int index = ui->nominaCargadaTableView->currentIndex().row();
    int nominaNum = nominaCargadaModel->record(index).value("numero").toInt();
    NominaCargadaWidget* NomCargadaW = new NominaCargadaWidget(nominaNum,this);
    NomCargadaW->setWindowFlags(Qt::Window);
    NomCargadaW->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::nominaProcesadaWidget()
{
    int index = ui->nominaProcesadaTableView->currentIndex().row();
    int nominaNum = nominaProcesadaModel->record(index).value("numero").toInt();
    NominaProcesadaWidget* nomProcesadaW = new NominaProcesadaWidget(nominaNum,this);
    nomProcesadaW->setWindowFlags(Qt::Window);
    nomProcesadaW->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::cargarDatosUsuario(Usuario user)
{
    usuario = user;
    userLabel = new QLabel(this);
    QString usuario ="Usuario: "+user.getNombres()+ " " + user.getApellidos();
    userLabel->setText(usuario);
    userLabel->setAlignment(Qt::AlignLeft);
    ui->statusBar->addPermanentWidget(userLabel,1);
}

void MainWindow::on_actionDeduccion_triggered()
{
    DeduccionWidget* deduccion = new DeduccionWidget(this);
    deduccion->setWindowFlags(Qt::Window);
    deduccion->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
 }

void MainWindow::on_actionEmpleados_triggered()
{
    EmpleadoWidget* empeladoW = new EmpleadoWidget(this);
    empeladoW->setWindowFlags(Qt::Window);
    empeladoW->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::on_actionAsignaciones_triggered()
{
    AsignacionWidget* asignacion = new AsignacionWidget(this);
    asignacion->setWindowFlags(Qt::Window);
    asignacion->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::on_actionClasificaciones_triggered()
{
    AreaWidget* clasificacion = new AreaWidget(this);
    clasificacion->setWindowFlags(Qt::Window);
    clasificacion->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::on_actionNomina_triggered()
{
    NominaWidget* nominaModel = new NominaWidget(this);
    nominaModel->setWindowFlags(Qt::Window);
    nominaModel->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::on_detalleNomProcPushButton_clicked()
{
    nominaProcesadaWidget();
}

void MainWindow::on_ModificarNomCargadaPushButton_clicked()
{
   nominaCargadaWidget();
}

void MainWindow::on_imprimirNomProcPushButton_clicked()
{

}

void MainWindow::on_nominaCargadaTableView_doubleClicked(const QModelIndex &index)
{
    (void) index;
    nominaCargadaWidget();
}

void MainWindow::on_nominaProcesadaTableView_doubleClicked(const QModelIndex &index)
{
    (void) index;
    nominaProcesadaWidget();
}

void MainWindow::on_CargarNomPushButton_clicked()
{
    NominaCargarDialog* cargarNominaD = new NominaCargarDialog(this);
    cargarNominaD->exec();
    updateNominaCargadaTableView();
}
