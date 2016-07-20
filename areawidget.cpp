#include "areawidget.h"
#include "ui_areawidget.h"

AreaWidget::AreaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AreaWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new AreaModel("asignacion","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

AreaWidget::~AreaWidget()
{
    delete model;
    delete ui;
}

void AreaWidget::clasificacionTableViewSelectionChange()
{
    QModelIndex myIndex= ui->clasificacionTableView->model()->index(ui->clasificacionTableView->currentIndex().row(),0);
    QString codigo = ui->clasificacionTableView->model()->data(myIndex).toString();
    clasificacion = Clasificacion(model->findClasificacion(codigo));
    status();
    if (!(clasificacion.getCodigo() == "")) {
        cargarClasificacion(clasificacion);
    }
}

void AreaWidget::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    areaModel = new QSqlQueryModel(this);
    tipoModel = new QSqlQueryModel(this);
    setState(State::inicial);
    updateTableView();
    updateAreaComboBox();
    UpdateAreaBusqComboBox();
    setValidadores();
}

void AreaWidget::setState(AreaWidget::State xstate)
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

void AreaWidget::stateAgregar()
{
    ui->areaBusqComboBox->setEnabled(false);
    ui->campoBusqComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->clasificacionTableView->setEnabled(false);

    ui->codigoLineEdit->setEnabled(true);
    ui->DescripcionLineEdit->setEnabled(true);
    ui->areaComboBox->setEnabled(true);
    ui->TipoSalarComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->ActivoCheckBox->setEnabled(true);

    ui->accionPushButton->setText("Agregar");
    ui->accionPushButton->setEnabled(true);

    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);

    ui->codigoLineEdit->clear();
    ui->DescripcionLineEdit->clear();
    ui->areaComboBox->setCurrentIndex(0);
    ui->TipoSalarComboBox->setCurrentIndex(0);
    ui->valorDoubleSpinBox->setValue(0);
    ui->ActivoCheckBox->setChecked(true);
}

void AreaWidget::stateModificar()
{

    ui->areaBusqComboBox->setEnabled(false);
    ui->campoBusqComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->clasificacionTableView->setEnabled(false);

    ui->codigoLineEdit->setEnabled(false);
    ui->DescripcionLineEdit->setEnabled(true);
    ui->areaComboBox->setEnabled(false);
    ui->TipoSalarComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->ActivoCheckBox->setEnabled(true);

    ui->accionPushButton->setText("Modificar");
    ui->accionPushButton->setEnabled(true);

    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);
}

void AreaWidget::stateInicial()
{
    ui->areaBusqComboBox->setEnabled(true);
    ui->campoBusqComboBox->setEnabled(true);
    ui->busquedaLineEdit->setEnabled(true);
    ui->clasificacionTableView->setEnabled(true);

    ui->codigoLineEdit->setEnabled(false);
    ui->DescripcionLineEdit->setEnabled(false);
    ui->areaComboBox->setEnabled(false);
    ui->TipoSalarComboBox->setEnabled(false);
    ui->valorDoubleSpinBox->setEnabled(false);
    ui->ActivoCheckBox->setEnabled(false);

    ui->accionPushButton->setText("aceptar");
    ui->accionPushButton->setEnabled(false);

    ui->agregarPushButton->setEnabled(true);
    ui->modificarPushButton->setEnabled(true);
    ui->eliminarPushButton->setEnabled(true);

}

void AreaWidget::cancelar()
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

void AreaWidget::status()
{
    ui->statusLabel->setText("Status: "+model->getStatusMessage());
}

void AreaWidget::agregarClasificacion()
{
    model->insertClasificacion(descargarClasificacion());
    status();
    updateTableView();
    setState(State::inicial);
}

void AreaWidget::modificarClasificacion()
{
    model->updateClasificacione(descargarClasificacion());
    status();
    updateTableView();
    setState(State::inicial);
}

void AreaWidget::eliminarClasificacion()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    clasificacion = descargarClasificacion();

    if (msg.question(this,"¿Pregunta?","¿Desea Eliminar Asignación? \nCodigo: " + clasificacion.getCodigo() +"\n"
                         + "Descripcion: " +clasificacion.getDescripcion()) == QMessageBox::Yes){

        model->deleteClasificacion(clasificacion.getCodigo());
        status();
        updateTableView();
        setState(State::inicial);
    }
}

void AreaWidget::updateTableView(QString str)
{
    QString area = ui->areaBusqComboBox->currentText();
    area = "";
    if (ui->campoBusqComboBox->currentIndex() == 0)
        tableModel->setQuery(model->findClasificaciones(str,area,AreaModel::Campo::descripcion,false));
    else if (ui->campoBusqComboBox->currentIndex() == 1)
        tableModel->setQuery(model->findClasificaciones(str,area,AreaModel::Campo::codigo,false));
    else
        tableModel->setQuery(model->findClasificaciones(str,area,AreaModel::Campo::descripcion,false));

    ui->clasificacionTableView->setModel(tableModel);
    ui->clasificacionTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(ui->clasificacionTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(clasificacionTableViewSelectionChange()));
}

void AreaWidget::UpdateAreaBusqComboBox()
{
    areaModel->setQuery(model->findAreas());
    ui->areaBusqComboBox->setModel(areaModel);
    ui->areaBusqComboBox->setModelColumn(1);
}

void AreaWidget::updateAreaComboBox(QString str)
{
    areaModel->setQuery(model->findAreas(str));
    ui->areaComboBox->setModel(areaModel);
    ui->areaComboBox->setModelColumn(1);
}

void AreaWidget::cargarClasificacion(Clasificacion clasificacion)
{
    ui->codigoLineEdit->setText(clasificacion.getCodigo());
    ui->DescripcionLineEdit->setText(clasificacion.getDescripcion());
    for (int i=0; i < ui->areaComboBox->count() ;i++) {
        QString area = areaModel->record(i).value("codigo").toString();
           if (area == clasificacion.getArea()) {
               ui->areaComboBox->setCurrentIndex(i);
               break;
           }
    }
    for (int i=0; i < ui->TipoSalarComboBox->count() ;i++) {
        ui->TipoSalarComboBox->setCurrentIndex(i);
           if (ui->TipoSalarComboBox->currentText() == clasificacion.getFormaPago()) {
               break;
           }
    }
    ui->valorDoubleSpinBox->setValue(clasificacion.getValor());
    ui->ActivoCheckBox->setChecked(clasificacion.isActivo());
    ui->fechaLineEdit->setText(clasificacion.getFecha());
}

Clasificacion AreaWidget::descargarClasificacion()
{
    QString codigoArea =  areaModel->record(ui->areaComboBox->currentIndex()).value("codigo").toString();
    clasificacion = Clasificacion(
                ui->codigoLineEdit->text(),
                ui->DescripcionLineEdit->text(),
                codigoArea,
                ui->TipoSalarComboBox->currentText(),
                ui->valorDoubleSpinBox->value(),
                ui->ActivoCheckBox->isChecked());

    return clasificacion;
}

void AreaWidget::setValidadores()
{
    ui->codigoLineEdit->setValidator(&codigoValidador);
    ui->DescripcionLineEdit->setValidator(&upperCaseValidador);
}

bool AreaWidget::validarDatos()
{
    QString advertencias = "";

    if (ui->areaComboBox->currentText().isEmpty())
    {
        advertencias = "- <b>Campo Área no puede estar en Blanco<b> \n"+ advertencias;
        ui->areaComboBox->setFocus();
    }
    if (ui->TipoSalarComboBox->currentText().isEmpty())
    {
        advertencias = "- <b>Campo Tipo no puede estar en Blanco<b> \n"+ advertencias;
        ui->TipoSalarComboBox->setFocus();
    }
    if (ui->valorDoubleSpinBox->value() <= 0)
    {
        advertencias = "- <b>Campo Valor debe ser Mayor a 0<b> \n"+ advertencias;
        ui->valorDoubleSpinBox->setFocus();
    }
    if (ui->DescripcionLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Descripción no Puede estar en Blanco<b> \n"+ advertencias;
        ui->DescripcionLineEdit->setFocus();
    }
    if (ui->codigoLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Código no Puede estar en Blanco<b> \n"+ advertencias;
        ui->codigoLineEdit->setFocus();
    }
    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void AreaWidget::on_agregarPushButton_clicked()
{
    setState(State::agregar);
}

void AreaWidget::on_modificarPushButton_clicked()
{
    setState(State::modificar);
}

void AreaWidget::on_cancelarPushButton_clicked()
{
    cancelar();
}

void AreaWidget::on_accionPushButton_clicked()
{
    if (validarDatos())
    {
        if (state == State::agregar)
            agregarClasificacion();
        else if (state == State::modificar)
            modificarClasificacion();
    }
}

void AreaWidget::on_eliminarPushButton_clicked()
{
    eliminarClasificacion();
}

void AreaWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableView(arg1);
}

void AreaWidget::on_codigoLineEdit_editingFinished()
{
    QString codigo = ui->codigoLineEdit->text();
    if (model->clasificacionExiste(codigo)){
        ui->codigoLineEdit->blockSignals(true);
        QMessageBox::warning(this,"ALERTA","Codigo ya se encuentra Registrado");
        ui->codigoLineEdit->blockSignals(false);
        ui->codigoLineEdit->setFocus();
        ui->codigoLineEdit->clear();
    }
}
