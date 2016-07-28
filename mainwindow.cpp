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
   //QObject::connect(nomProcesadaW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));
   //QObject::connect(NomCargadaW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));
    nominaCargadaModel = new QSqlQueryModel(this);
    nominaProcesadaModel = new QSqlQueryModel(this);
    anticipoModel = new QSqlQueryModel(this);



    loadDatosEmpleados();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
    updateAnticipoTableView();
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
    ui->nominaCargadaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->nominaCargadaTableView->setModel(nominaCargadaModel);
}

void MainWindow::updateNominaProcesadaTableView()
{
    nominaProcesadaModel->setQuery(model->findNominasProcesadas());
    ui->nominaProcesadaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->nominaProcesadaTableView->setModel(nominaProcesadaModel);

}

void MainWindow::updateAnticipoTableView()
{
    anticipoModel->setQuery(model->findAnticiposView());
    ui->anticipoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->anticipoTableView->setModel(anticipoModel);

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
    NomCargadaW = new NominaCargadaWidget(nominaNum,this);
    NomCargadaW->setWindowFlags(Qt::Window);
    NomCargadaW->show();
    QObject::connect(NomCargadaW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));

}

void MainWindow::nominaProcesadaWidget()
{
    int index = ui->nominaProcesadaTableView->currentIndex().row();
    int nominaNum = nominaProcesadaModel->record(index).value("numero").toInt();
    nomProcesadaW = new NominaProcesadaWidget(nominaNum,this);
    nomProcesadaW->setWindowFlags(Qt::Window);
    nomProcesadaW->show();
    QObject::connect(nomProcesadaW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));
}

void MainWindow::imprimirNomina()
{
    int index = ui->nominaCargadaTableView->currentIndex().row();
    int nominaNum = nominaCargadaModel->record(index).value("numero").toInt();

    ReportModel report;
    report.nomina(nominaNum);
}

void MainWindow::eliminarNominaProcesada()
{
    int index = ui->nominaProcesadaTableView->currentIndex().row();
    int nominaNum = nominaProcesadaModel->record(index).value("numero").toInt();

    if (model->nominaProcesadaExiste(nominaNum))
    {
        QMessageBox msg;
        msg.setModal(true);
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        if (msg.question(this,"Advertencia","¿Desea Eliminar Nomina Procesada? ") == QMessageBox::Yes){

            if (model->deleteNominaProcesada(nominaNum))
                QMessageBox::information(this,"Información",model->getStatusMessage(),QMessageBox::Ok);
            else
                QMessageBox::critical(this,"Error",model->getStatusMessage(),QMessageBox::Ok);
        }
        updateTables();
    } else
        QMessageBox::critical(this,"Error","Nomina No Encontrada",QMessageBox::Ok);

}

void MainWindow::eliminarNominaCargada()
{
    int index = ui->nominaCargadaTableView->currentIndex().row();
    int nominaNum = nominaCargadaModel->record(index).value("numero").toInt();

    if (model->nominaExiste(nominaNum))
    {
        QMessageBox msg;
        msg.setModal(true);
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        if (msg.question(this,"Advertencia","¿Desea Eliminar Nomina Cargada? ") == QMessageBox::Yes){

            if (model->deleteNominaCargada(nominaNum))
                QMessageBox::information(this,"Información",model->getStatusMessage(),QMessageBox::Ok);
            else
                QMessageBox::critical(this,"Error",model->getStatusMessage(),QMessageBox::Ok);
        }
        updateTables();
    } else
        QMessageBox::critical(this,"Error","Nomina No Encontrada",QMessageBox::Ok);
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
    QObject::connect(empeladoW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));
}

void MainWindow::on_actionAsignaciones_triggered()
{
    AsignacionWidget* asignacion = new AsignacionWidget(this);
    asignacion->setWindowFlags(Qt::Window);
    asignacion->show();
    updateTables();
}

void MainWindow::on_actionClasificaciones_triggered()
{
    AreaWidget* clasificacion = new AreaWidget(this);
    clasificacion->setWindowFlags(Qt::Window);
    clasificacion->show();
    updateTables();
}

void MainWindow::on_actionNomina_triggered()
{
    NominaWidget* nominaModel = new NominaWidget(this);
    nominaModel->setWindowFlags(Qt::Window);
    nominaModel->show();
    updateTables();
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
    updateTables();
}

void MainWindow::updateTables()
{
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
    updateAnticipoTableView();
    loadDatosEmpleados();
}

void MainWindow::on_EliminarNomProcPushButton_clicked()
{
    eliminarNominaProcesada();

}

void MainWindow::on_actionConfiguracion_triggered()
{
    empresaDialog* empresaD = new empresaDialog(this);
    empresaD->setWindowFlags(Qt::Window);
    empresaD->show();
    updateNominaCargadaTableView();
    updateNominaProcesadaTableView();
}

void MainWindow::on_generarAnticipoPushButton_clicked()
{
    AnticipoWidget* anticipoW = new AnticipoWidget(this);
    anticipoW->setWindowFlags(Qt::Window);
    anticipoW->show();
     QObject::connect(anticipoW,SIGNAL(destroyed(QObject*)),this,SLOT(updateTables()));
}

void MainWindow::on_verAnticipoPushButton_clicked()
{
    ReportModel report;
    int index = ui->anticipoTableView->currentIndex().row();
    int anticipoId = anticipoModel->record(index).value("id").toInt();
    report.anticipo(anticipoId);
}

void MainWindow::on_anticipoTableView_doubleClicked(const QModelIndex &index)
{
    (void) index;
    on_verAnticipoPushButton_clicked();
}

void MainWindow::on_CargarNomPushButton_4_clicked()
{

}

void MainWindow::on_eliminarAnticipoPushButton_clicked()
{
    AnticipoModel anticipo("anticipoMainWindow","127.0.0.1","nomina","root","19017070",3306);
    int index = ui->anticipoTableView->currentIndex().row();
    int anticipoId = anticipoModel->record(index).value("id").toInt();

    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    if (msg.question(this,"Advertencia","¿Desea Eliminar Anticipo seleccionado? ") == QMessageBox::Yes){

        if (anticipo.deleteAnticipo(anticipoId))
            QMessageBox::information(this,"Información",anticipo.getStatusMessage(),QMessageBox::Ok);
        else
            QMessageBox::critical(this,"Error",anticipo.getStatusMessage(),QMessageBox::Ok);
    }
    updateTables();

}

void MainWindow::on_eliminarNomCargadaPushButton_clicked()
{
    eliminarNominaCargada();
}
