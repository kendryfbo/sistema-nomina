#include "empleadowidget.h"
#include "ui_empleadowidget.h"
#include "nominamodel.h"

EmpleadoWidget::EmpleadoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmpleadoWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new EmpleadoModel("empleado","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

EmpleadoWidget::~EmpleadoWidget()
{
    delete model;
    delete ui;
}

void EmpleadoWidget::empleadoTableViewSelectionChange()
{
    QModelIndex myIndex= ui->empleadoTableView->model()->index(ui->empleadoTableView->currentIndex().row(),0);
    QString cedula = ui->empleadoTableView->model()->data(myIndex).toString();
    empleado = Empleado(model->findEmpleado(cedula));
    status();
    if (!(empleado.getCedula() == "DEFAULT")) {
       cargarEmpleado();
    }
}

void EmpleadoWidget::prepareWidget()
{
    empTableModel = new QSqlTableModel(this);
    campoModel = new QSqlQueryModel(this);
    clasificModel = new QSqlQueryModel(this);
    deducFijaModel = new QSqlQueryModel(this);
    deducEventModel = new QSqlQueryModel(this);
    asignFijaModel = new QSqlQueryModel(this);
    asignEventModel = new QSqlQueryModel(this);
    nominaModel = new QSqlQueryModel(this);
    aporteFaovModel = new QSqlQueryModel(this);

    updateCamposComboBox();
    setState(State::inicial);
    updateEmpleadoTableView("");
    ui->empleadoTableView->selectRow(0);

    // INVISIBLES HASTA CORRECTA IMPLEMENTACION
    ui->nominaCargadaGroupBox->setVisible(false);
    ui->asignEventTableView->setVisible(false);
    ui->agrAsignEvenPushButton->setVisible(false);
    ui->EliminarAsignEventPushButton->setVisible(false);
    ui->asignEventLabel->setVisible(false);
    ui->deduccEventTableView->setVisible(false);
    ui->deduccEventLabel->setVisible(false);
    ui->agrDeduccEvenPushButton->setVisible(false);
    ui->eliminarDeduccEventPushButton->setVisible(false);

}

void EmpleadoWidget::setState(EmpleadoWidget::State xstate)
{
    state = xstate;

    if (state == State::agregar){
        stateAgregar();
    }
    if (state == State::modificar) {
        stateModificar();
    }
    if (state == State::inicial){
        stateInicial();
    }
}

void EmpleadoWidget::stateAgregar()
{
    ui->empleadoTableView->setEnabled(false);
    ui->busquedaComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->deduccTab->setEnabled(false);
    ui->asingnTab->setEnabled(false);
    ui->nominaTab->setEnabled(false);
    ui->aporteFaovTab->setEnabled(false);

    botonesDeTabla(false);

    ui->datosPersTab->setEnabled(true);
    ui->infLabTab->setEnabled(true);
    ui->cedulaLineEdit->setEnabled(true);
    ui->fechaIngrDateEdit->setEnabled(true);

    ui->cedulaLineEdit->clear();
    ui->rifLineEdit->clear();
    ui->nombresLineEdit->clear();
    ui->apellidosLineEdit->clear();
    ui->edoCivilComboBox->setCurrentIndex(0);
    ui->numHijosSpinBox->setValue(0);
    ui->fechaNacDateEdit->setDate(QDate::currentDate());
    ui->lugarNacLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->tlf1LineEdit->clear();
    ui->tlf2LineEdit->clear();
    ui->direccionLineEdit->clear();
    ui->nivelAcadLineEdit->clear();
    ui->nivelSupCheckBox->setEnabled(true);
    ui->nivelSupCheckBox->setChecked(false);
    ui->especLineEdit->clear();
    ui->tituloLineEdit->clear();

    ui->nivelLineEdit->clear();
    ui->tipoContratoComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->fechaIngrDateEdit->setDate(QDate::currentDate());
    ui->tipoSalarioLineEdit->clear();
    ui->HorasSpinBox->setValue(0);
    ui->salarioHoraDoubleSpinBox->setValue(0);
    ui->salarioDiaDoubleSpinBox->setValue(0);
    ui->salarioMesDoubleSpinBox->setValue(0);
    ui->clasifcComboBox->setCurrentIndex(-1);

    ui->accionPushButton->setText("Agregar");
    ui->accionPushButton->setVisible(true);
    ui->tabWidget->setCurrentIndex(0);
    ui->cedulaLineEdit->setFocus();

}

void EmpleadoWidget::stateModificar()
{
    ui->empleadoTableView->setEnabled(false);
    ui->busquedaComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);

    ui->deduccTab->setEnabled(false);
    ui->asingnTab->setEnabled(false);
    ui->nominaTab->setEnabled(false);
    ui->aporteFaovTab->setEnabled(false);

    botonesDeTabla(false);

    ui->datosPersTab->setEnabled(true);
    ui->infLabTab->setEnabled(true);
   ui->fechaIngrDateEdit->setEnabled(true);
   ui->cedulaLineEdit->setEnabled(false);
   ui->nivelSupCheckBox->setEnabled(true);
   ui->accionPushButton->setText("Modificar");
   ui->accionPushButton->setVisible(true);
   ui->tabWidget->setCurrentIndex(0);

}

void EmpleadoWidget::stateInicial()
{
    ui->empleadoTableView->setEnabled(true);
    ui->busquedaComboBox->setEnabled(true);
    ui->busquedaLineEdit->setEnabled(true);

    ui->deduccTab->setEnabled(true);
    ui->asingnTab->setEnabled(true);
    ui->nominaTab->setEnabled(true);
    ui->aporteFaovTab->setEnabled(true);

    botonesDeTabla(true);

    ui->datosPersTab->setEnabled(false);
    ui->infLabTab->setEnabled(false);


    ui->cedulaLineEdit->clear();
    ui->rifLineEdit->clear();
    ui->nombresLineEdit->clear();
    ui->apellidosLineEdit->clear();
    ui->edoCivilComboBox->setCurrentIndex(0);
    ui->numHijosSpinBox->setValue(0);
    ui->fechaNacDateEdit->setDate(QDate::currentDate());
    ui->lugarNacLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->tlf1LineEdit->clear();
    ui->tlf2LineEdit->clear();
    ui->direccionLineEdit->clear();
    ui->nivelAcadLineEdit->clear();
    ui->nivelSupCheckBox->setEnabled(false);
    ui->especLineEdit->clear();
    ui->tituloLineEdit->clear();

    //ui->CampoComboBox->setCurrentIndex(0);
    //ui->clasifcComboBox->setCurrentIndex(0);
    ui->nivelLineEdit->clear();
    ui->tipoContratoComboBox->setCurrentIndex(0);
    ui->statusComboBox->setCurrentIndex(0);
    ui->fechaIngrDateEdit->setDate(QDate::currentDate());
    ui->tipoSalarioLineEdit->clear();
    ui->HorasSpinBox->setValue(0);
    ui->salarioHoraDoubleSpinBox->setValue(0);
    ui->salarioDiaDoubleSpinBox->setValue(0);
    ui->salarioMesDoubleSpinBox->setValue(0);

    ui->accionPushButton->setVisible(false);
    ui->busquedaLineEdit->setFocus();
}

void EmpleadoWidget::cancelar()
{
    if (state == State::inicial){
        this->close();
    }else {
        QMessageBox msg;
        msg.setModal(true);
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        if (msg.question(this,"Advertencia","¿Desea cancelar la operacion? ") == QMessageBox::Yes){
           setState(State::inicial);
        }
    }
}

void EmpleadoWidget::status()
{
    ui->statusLabel->setText("Status: " + model->getStatusMessage());
}

void EmpleadoWidget::cargarEmpleado()
{
    cargarDatosEmpleado();
    cargarInfoLaboral();
    cargarDeduccionesEmpelado();
    cargarAsignacionesEmpelado();
    cargarNominasEmpelado();
    cargarAporteFaovEmpleado();


}

void EmpleadoWidget::cargarDatosEmpleado()
{
    ui->cedulaLineEdit->setText(empleado.getCedula());
    ui->nombresLineEdit->setText(empleado.getNombres());
    ui->apellidosLineEdit->setText(empleado.getApellidos());
    ui->edoCivilComboBox->setCurrentText(empleado.getEdoCivil());
    ui->numHijosSpinBox->setValue(empleado.getNumHijos());
    ui->fechaNacDateEdit->setDate(QDate::fromString(empleado.getFechaNac(),"yyyy-MM-dd"));
    ui->lugarNacLineEdit->setText(empleado.getLugarNac());
    ui->emailLineEdit->setText(empleado.getEmail());
    ui->tlf1LineEdit->setText(empleado.getTlf1());
    ui->tlf2LineEdit->setText(empleado.getTlf2());
    ui->direccionLineEdit->setText(empleado.getDireccion());
    ui->nivelAcadLineEdit->setText(empleado.getNivelAcad());
    ui->nivelSupCheckBox->setChecked(empleado.getNivelAcadSup());
    ui->especLineEdit->setText(empleado.getEspec());
    ui->tituloLineEdit->setText(empleado.getTitulo());
}

void EmpleadoWidget::cargarInfoLaboral()
{
    for (int i=0; i < ui->CampoComboBox->count() ;i++) {
        QString area = campoModel->record(i).value("codigo").toString();
           if (area == empleado.getArea()) {
               ui->CampoComboBox->setCurrentIndex(i);
               break;
           }
    }
    if (ui->clasifcComboBox->count()>0)
    {
        for (int i=0; i < ui->clasifcComboBox->count() ;i++) {
            QString clasific = clasificModel->record(i).value("codigo").toString();
            if (clasific == empleado.getClasificacion().getCodigo()) {
                ui->clasifcComboBox->setCurrentIndex(i);
                break;
           }
        }
    }
    ui->tipoSalarioLineEdit->setText(empleado.getClasificacion().getFormaPago());
    ui->nivelLineEdit->setText(empleado.getNivel());

    for (int i=0; i<ui->tipoContratoComboBox->count(); i++)
    {
        ui->tipoContratoComboBox->setCurrentIndex(i);
        if (empleado.getContrato() == ui->tipoContratoComboBox->currentText())
            break;
    }
    for (int i=0; i<ui->statusComboBox->count(); i++)
    {
        ui->statusComboBox->setCurrentIndex(i);
        if (empleado.getStatus() == ui->statusComboBox->currentText())
            break;
    }
    ui->antiguedadLineEdit->setText(QString::number(empleado.getAntiguedad()));
    ui->fechaIngrDateEdit->setDate(QDate::fromString(empleado.getFechaIng(),"yyyy-MM-dd"));
    ui->HorasSpinBox->setValue(empleado.getHoras());
    ui->salarioHoraDoubleSpinBox->setValue(empleado.getSalarioHora());
    ui->salarioDiaDoubleSpinBox->setValue(empleado.getSalarioDia());
    ui->salarioSemDoubleSpinBox->setValue(empleado.getSalarioSemana());
    ui->salarioMesDoubleSpinBox->setValue(empleado.getSalarioMes());
}

void EmpleadoWidget::cargarDeduccionesEmpelado()
{
    updateDeduccFijaTableView();
    updateDeduccEventTableView();
}

void EmpleadoWidget::cargarAsignacionesEmpelado()
{
    updateAsignFijaTableView();
    updateAsignEventTableView();
}

void EmpleadoWidget::cargarNominasEmpelado()
{
    updateNomProcTableView();
}

void EmpleadoWidget::cargarAporteFaovEmpleado()
{
    updateAporteFaovTableView();
}

Empleado EmpleadoWidget::descargarEmpleado()
{
    QString codigoClasif = clasificModel->record(ui->clasifcComboBox->currentIndex()).value("codigo").toString();
    Clasificacion clasificacion(model->findClasificacion(codigoClasif));
    empleado = Empleado(
                ui->cedulaLineEdit->text(),
                ui->nombresLineEdit->text(),
                ui->apellidosLineEdit->text(),
                ui->rifLineEdit->text(),
                ui->fechaNacDateEdit->date().toString("yyyy-MM-dd"),
                ui->lugarNacLineEdit->text(),
                ui->emailLineEdit->text(),
                ui->edoCivilComboBox->currentText(),
                ui->numHijosSpinBox->value(),
                ui->direccionLineEdit->text(),
                ui->tlf1LineEdit->text(),
                ui->tlf2LineEdit->text(),
                ui->nivelAcadLineEdit->text(),
                ui->especLineEdit->text(),
                ui->nivelSupCheckBox->isChecked(),
                ui->tituloLineEdit->text(),
                "2016-10-10",
                "2016-10-10",
                ui->fechaIngrDateEdit->date().toString("yyyy-MM-dd"),
                ui->statusComboBox->currentText(),
                clasificacion.getArea(),
                clasificacion,
                ui->nivelAcadLineEdit->text(),
                ui->HorasSpinBox->value(),
                ui->tipoContratoComboBox->currentText());

    qDebug() << clasificacion.getArea();
    return empleado;
}

void EmpleadoWidget::updateEmpleadoTableView(QString str)
{
    if (ui->busquedaComboBox->currentIndex() == 0)
        empTableModel->setQuery(model->findEmpleados(str,EmpleadoModel::Campo::cedula));
    else if (ui->busquedaComboBox->currentIndex() == 1)
        empTableModel->setQuery(model->findEmpleados(str,EmpleadoModel::Campo::nombre));
    else if (ui->busquedaComboBox->currentIndex() == 2)
        empTableModel->setQuery(model->findEmpleados(str,EmpleadoModel::Campo::apellido));
    else
        empTableModel->setQuery(model->findEmpleados(str,EmpleadoModel::Campo::nombre));

    ui->empleadoTableView->setModel(empTableModel);
    QObject::connect(ui->empleadoTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(empleadoTableViewSelectionChange()));
}

void EmpleadoWidget::updateDeduccFijaTableView()
{
    deducFijaModel->setQuery(model->findDeducciones(empleado.getCedula(),"",model->Tipo::fija));
    deducFijaModel->setHeaderData(0,Qt::Horizontal,"Código");
    ui->deduccFijaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->deduccFijaTableView->setModel(deducFijaModel);
}

void EmpleadoWidget::updateDeduccEventTableView()
{
    deducEventModel->setQuery(model->findDeducciones(empleado.getCedula(),"",model->Tipo::eventual));
    deducEventModel->setHeaderData(0,Qt::Horizontal,"Código");
    ui->deduccEventTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->deduccEventTableView->setModel(deducEventModel);
}

void EmpleadoWidget::updateAsignFijaTableView()
{
    asignFijaModel->setQuery(model->findAsignaciones(empleado.getCedula(),"",model->Tipo::fija));
    asignFijaModel->setHeaderData(0,Qt::Horizontal,"Código");
    ui->asignFijaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->asignFijaTableView->setModel(asignFijaModel);
}

void EmpleadoWidget::updateAsignEventTableView()
{
    asignEventModel->setQuery(model->findAsignaciones(empleado.getCedula(),"",model->Tipo::eventual));
    asignEventModel->setHeaderData(0,Qt::Horizontal,"Código");
    ui->asignEventTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->asignEventTableView->setModel(asignEventModel);
}

void EmpleadoWidget::updateNomProcTableView()
{
    nominaModel->setQuery(model->findNominaProcesada(empleado.getCedula()));
    ui->nominaProcesadaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->nominaProcesadaTableView->setModel(nominaModel);
}

void EmpleadoWidget::updateAporteFaovTableView()
{
    aporteFaovModel->setQuery(model->findAportesEmpleado(empleado.getCedula()));
    ui->aporteFaovTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->aporteFaovTableView->setModel(aporteFaovModel);
}

void EmpleadoWidget::on_agregarPushButton_clicked()
{
    setState(State::agregar);
}

void EmpleadoWidget::on_modificarPushButton_clicked()
{
    setState(State::modificar);
}

void EmpleadoWidget::on_CancelarPushButton_clicked()
{
    cancelar();
}

void EmpleadoWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateEmpleadoTableView(arg1);
}

void EmpleadoWidget::on_busquedaComboBox_currentIndexChanged(int index)
{
    (void) index;
    ui->busquedaLineEdit->setFocus();
}

void EmpleadoWidget::updateCamposComboBox()
{
    campoModel->setQuery(model->findAreas());
    ui->CampoComboBox->setModel(campoModel);
    ui->CampoComboBox->setModelColumn(1);
}

void EmpleadoWidget::updateClasificacionComboBox()
{
    QString area = campoModel->record(ui->CampoComboBox->currentIndex()).value("codigo").toString();
    clasificModel->setQuery(model->findClasificaciones(area));
    ui->clasifcComboBox->setModel(clasificModel);
    ui->clasifcComboBox->setModelColumn(1);
    updateFormaPago();
}

void EmpleadoWidget::updateFormaPago()
{
    QString formaPago = clasificModel->record(ui->clasifcComboBox->currentIndex()).value("formapago").toString();
    ui->tipoSalarioLineEdit->setText(formaPago);

    if (formaPago == "HORA")
    {
        ui->horasLabel->setVisible(true);
        ui->HorasSpinBox->setVisible(true);
    } else
    {
        ui->horasLabel->setVisible(false);
        ui->HorasSpinBox->setVisible(false);
    }
}

void EmpleadoWidget::deleteDeduccion(QString codigo)
{
    model->eliminarDeduccion(codigo,empleado.getCedula());
}

void EmpleadoWidget::deleteAsignacion(QString codigo)
{
    model->eliminarAsignacion(codigo,empleado.getCedula());
}

void EmpleadoWidget::agregarEmpleado()
{
    model->insertEmpleado(descargarEmpleado());
    status();
    updateEmpleadoTableView();
    setState(State::inicial);
}

void EmpleadoWidget::modificarEmpleado()
{
    model->updateEmpleado(descargarEmpleado());
    status();
    updateEmpleadoTableView();
    setState(State::inicial);
}

void EmpleadoWidget::elimianrEmpleado()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    empleado = descargarEmpleado();

    if (msg.question(this,"¿Pregunta?","¿Desea Eliminar Empleado? \nCodigo: " + empleado.getCedula() +"\n"
                         + "Descripcion: " +empleado.getNombres()+" "+empleado.getApellidos()) == QMessageBox::Yes){

        model->deleteEmpleado(empleado.getCedula());
        status();
        updateEmpleadoTableView();
        setState(State::inicial);
    }
}

bool EmpleadoWidget::validarDatos()
{
    QString advertencias = "";

    if (ui->fechaIngrDateEdit->date().toString().isEmpty())
    {
        advertencias = "- <b>Campo Fecha de Ingreso  no Puede estar en Blanco<b> \n "+ advertencias;
        ui->fechaIngrDateEdit->setFocus();
    }
    if (ui->clasifcComboBox->currentText().isEmpty())
    {
        advertencias = "- <b>Campo Clasificación no Puede estar en Blanco<b> \n "+ advertencias;
        ui->clasifcComboBox->setFocus();
    }
    if (ui->CampoComboBox->currentText().isEmpty())
    {
        advertencias = "- <b>Campo Campo no Puede estar en Blanco<b> \n "+ advertencias;
        ui->CampoComboBox->setFocus();
    }
    if (ui->apellidosLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Apellidos no Puede estar en Blanco<b> \n "+ advertencias;
        ui->apellidosLineEdit->setFocus();
    }
    if (ui->apellidosLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Apellidos no Puede estar en Blanco<b> \n "+ advertencias;
        ui->apellidosLineEdit->setFocus();
    }
    if (ui->nombresLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Nombres no Puede estar en Blanco<b> \n "+ advertencias;
        ui->nombresLineEdit->setFocus();
    }
    if (ui->cedulaLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Cedula no Puede estar en Blanco<b> \n "+ advertencias;
        ui->cedulaLineEdit->setFocus();
    }

    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void EmpleadoWidget::botonesDeTabla(bool sentinela)
{
    ui->agregarPushButton->setEnabled(sentinela);
    ui->modificarPushButton->setEnabled(sentinela);
}

void EmpleadoWidget::nominaProcesadaWidget(int nominaNum)
{
    NominaProcesadaWidget* nomProcesadaW = new NominaProcesadaWidget(nominaNum,this);
    nomProcesadaW->setWindowFlags(Qt::Window);
    nomProcesadaW->show();
}

void EmpleadoWidget::on_CampoComboBox_currentIndexChanged(int index)
{
    (void) index;
    updateClasificacionComboBox();
}

void EmpleadoWidget::on_eliminarDeduccFijaPushButton_clicked()
{
    int row = ui->deduccFijaTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = deducFijaModel->record(row).value("cod_deduccion").toString();
        deleteDeduccion(codigo);
        updateDeduccFijaTableView();
    }
}

void EmpleadoWidget::on_clasifcComboBox_currentIndexChanged(int index)
{
    (void) index;
    updateFormaPago();
}

void EmpleadoWidget::on_accionPushButton_clicked()
{
    if (validarDatos())
    {
        if (state == State::agregar)
            agregarEmpleado();
        else if (state == State::modificar)
            modificarEmpleado();
    }
}

void EmpleadoWidget::on_ProcNominaPushButton_clicked()
{
    /*
    Nomina nomina;

    NominaModel nominaModel("empleado","127.0.0.1","nomina","root","19017070",3306);

    nominaModel.cargarNominaEmpleado(empleado,nomina);
*/
}

void EmpleadoWidget::on_agrDeduccFijPushButton_clicked()
{
    DeduccionDialog* deduccD = new DeduccionDialog(this);

    if (deduccD->exec() == QDialog::Accepted)
    {
        model->insertDeduccion(deduccD->getCodigo(),empleado.getCedula(),"FIJA",deduccD->getCantidad());
        cargarDeduccionesEmpelado();
    }
}

void EmpleadoWidget::on_eliminarDeduccEventPushButton_clicked()
{
    int row = ui->deduccFijaTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = deducEventModel->record(row).value("cod_deduccion").toString();
        deleteDeduccion(codigo);
        updateDeduccEventTableView();
    }
}

void EmpleadoWidget::on_agrDeduccEvenPushButton_clicked()
{
    DeduccionDialog* deduccD = new DeduccionDialog(this);

    if (deduccD->exec() == QDialog::Accepted)
    {
        model->insertDeduccion(deduccD->getCodigo(),empleado.getCedula(),"EVENTUAL",deduccD->getCantidad());
        cargarDeduccionesEmpelado();
    }
}

void EmpleadoWidget::on_agrAsignFijPushButton_clicked()
{
    AsignacionDialog* asignD = new AsignacionDialog(this);

    if (asignD->exec() == QDialog::Accepted)
    {
        model->insertAsignacion(asignD->getCodigo(),empleado.getCedula(),"FIJA",asignD->getCantidad());
        cargarAsignacionesEmpelado();
    }
}

void EmpleadoWidget::on_agrAsignEvenPushButton_clicked()
{
    AsignacionDialog* asignD = new AsignacionDialog(this);

    if (asignD->exec() == QDialog::Accepted)
    {
        model->insertAsignacion(asignD->getCodigo(),empleado.getCedula(),"EVENTUAL",asignD->getCantidad());
        cargarAsignacionesEmpelado();
    }
}


void EmpleadoWidget::on_EliminarAsignFijaPushButton_clicked()
{
    int row = ui->asignFijaTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = asignFijaModel->record(row).value("cod_asignacion").toString();
        deleteAsignacion(codigo);
        cargarAsignacionesEmpelado();
    }
}

void EmpleadoWidget::on_EliminarAsignEventPushButton_clicked()
{
    int row = ui->asignEventTableView->currentIndex().row();
    if (!(row < 0))
    {
        QString codigo = asignEventModel->record(row).value("cod_asignacion").toString();
        deleteAsignacion(codigo);
        cargarAsignacionesEmpelado();
    }
}

void EmpleadoWidget::on_nominaProcesadaTableView_doubleClicked(const QModelIndex &index)
{
    int nominaNum = nominaModel->record(index.row()).value("numero").toInt();
    nominaProcesadaWidget(nominaNum);
}

void EmpleadoWidget::on_cedulaLineEdit_editingFinished()
{
    QString cedula = ui->cedulaLineEdit->text();
    if (model->empleadoExist(cedula)){
        ui->cedulaLineEdit->blockSignals(true);
        QMessageBox::warning(this,"ALERTA","Cedula de Empleado ya se encuentra Registrada");
        ui->cedulaLineEdit->blockSignals(false);
        ui->cedulaLineEdit->setFocus();
        ui->cedulaLineEdit->clear();
    }
}

void EmpleadoWidget::on_aporteFaovAgregarPushButton_clicked()
{
    aporteFaovInsertDialog* aporteFaovDialog = new aporteFaovInsertDialog(this);

    if (aporteFaovDialog->exec() == QDialog::Accepted)
    {
        if (!model->insertAporte(empleado.getCedula(),
                            aporteFaovDialog->getDescripcion(),
                            aporteFaovDialog->getAporte()))
        {
            QMessageBox::warning(this,"ERROR",model->getStatusMessage());
        } else
            cargarAporteFaovEmpleado();

    }
}

void EmpleadoWidget::on_aporteFaovEliminarPushButton_clicked()
{
    int row = ui->aporteFaovTableView->currentIndex().row();
    if (!(row < 0))
    {
        int numero = aporteFaovModel->record(row).value("numero").toInt();
        QMessageBox msg;
        msg.setModal(true);
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        if (msg.question(this,"Advertencia","¿Desea Eliminar Aporte de Prestacion? ") == QMessageBox::Yes){
            model->deleteAporte(numero,empleado.getCedula());
            QMessageBox::information(this,"Información",model->getStatusMessage(),QMessageBox::Ok);
            cargarAporteFaovEmpleado();
        }
    }
}
