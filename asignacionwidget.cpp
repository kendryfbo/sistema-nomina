#include "asignacionwidget.h"
#include "ui_asignacionwidget.h"

AsignacionWidget::AsignacionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AsignacionWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    model = new AsignacionModel("deduccion","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

AsignacionWidget::~AsignacionWidget()
{
    delete model;
    delete ui;
}

void AsignacionWidget::asignacionTableViewSelectionChange()
{
    QModelIndex myIndex= ui->asignacionTableView->model()->index(ui->asignacionTableView->currentIndex().row(),0);
    QString codigo = ui->asignacionTableView->model()->data(myIndex).toString();
    asignacion = Asignacion(model->findAsignacion(codigo));
    status();
    if (!(asignacion.getCodigo() == "")) {
        cargarAsignacion(asignacion);
    }
}

void AsignacionWidget::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    formaModel = new QSqlQueryModel(this);
    setState(State::inicial);
    setValidadores();
    updateTableView();
    updateFormaComboBox();
    updateFormulaCombobox();
    ui->asignacionTableView->selectRow(0);
}

void AsignacionWidget::setState(AsignacionWidget::State xstate)
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

void AsignacionWidget::stateAgregar()
{
    ui->asignacionTabWidget->setCurrentIndex(0);

    ui->codigoLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setEnabled(true);
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->codigoLineEdit->setEnabled(true);
    ui->formulaComboBox->setEnabled(true);
    ui->formulaLabel->setEnabled(true);
    ui->activoCheckBox->setEnabled(true);
    ui->primaCheckBox->setEnabled(true);
    ui->activoCheckBox->setChecked(true);
    ui->primaCheckBox->setChecked(false);
    ui->codigoLineEdit->clear();
    ui->descripcionLineEdit->clear();
    ui->FormaComboBox->setCurrentIndex(0);
    ui->valorDoubleSpinBox->setValue(100);
    ui->codigoLineEdit->setFocus();

    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Agregar");

    ui->busquedaComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->asignacionTableView->setEnabled(false);
    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);
}

void AsignacionWidget::stateModificar()
{
    ui->asignacionTabWidget->setCurrentIndex(0);

    ui->descripcionLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setFocus();
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->formulaComboBox->setEnabled(true);
    ui->formulaLabel->setEnabled(true);
    ui->activoCheckBox->setEnabled(true);
    ui->primaCheckBox->setEnabled(true);
    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Modificar");

    ui->codigoLineEdit->setEnabled(false);
    ui->busquedaComboBox->setEnabled(false);
    ui->asignacionTableView->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);
}

void AsignacionWidget::stateInicial()
{
    ui->codigoLineEdit->clear();
    ui->descripcionLineEdit->clear();
    ui->FormaComboBox->setCurrentIndex(0);
    ui->valorDoubleSpinBox->setValue(1);
    ui->formulaComboBox->setCurrentIndex(0);
    ui->codigoLineEdit->setEnabled(false);
    ui->descripcionLineEdit->setEnabled(false);
    ui->FormaComboBox->setEnabled(false);
    ui->valorDoubleSpinBox->setEnabled(false);
    ui->codigoLineEdit->setEnabled(false);
    ui->formulaComboBox->setEnabled(false);
    ui->formulaLabel->setEnabled(false);
    ui->accionPushButton->setEnabled(false);
    ui->activoCheckBox->setEnabled(false);
    ui->primaCheckBox->setEnabled(false);
    ui->busquedaComboBox->setEnabled(true);
    ui->busquedaLineEdit->setEnabled(true);
    ui->asignacionTableView->setEnabled(true);
    ui->agregarPushButton->setEnabled(true);
    ui->modificarPushButton->setEnabled(true);
    ui->eliminarPushButton->setEnabled(true);

    ui->accionPushButton->setText("Aceptar");

    ui->busquedaLineEdit->setFocus();
}

void AsignacionWidget::cancelar()
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

void AsignacionWidget::status()
{
    ui->statusLabel->setText("Status: "+model->getStatusMessage());
}

void AsignacionWidget::agregarAsignacion()
{
    model->insertAsignacion(descargarAsignacion());
    status();
    updateTableView();
    setState(State::inicial);
}

void AsignacionWidget::modificarAsignacion()
{
    model->updateAsignacion(descargarAsignacion());
    status();
    updateTableView();
    setState(State::inicial);
}

void AsignacionWidget::eliminarAsignacion()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    asignacion = descargarAsignacion();

    if (msg.question(this,"¿Pregunta?","¿Desea Eliminar Asignación? \nCodigo: " + asignacion.getCodigo() +"\n"
                         + "Descripcion: " +asignacion.getDescripcion()) == QMessageBox::Yes){

        model->DeleteAsignacion(asignacion.getCodigo());
        status();
        updateTableView();
        setState(State::inicial);
    }
}

void AsignacionWidget::updateTableView(QString str)
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

void AsignacionWidget::updateFormaComboBox(QString str)
{
    formaModel->setQuery(model->findForma(str));
    ui->FormaComboBox->setModel(formaModel);
    ui->FormaComboBox->setModelColumn(1);
}

void AsignacionWidget::updateFormulaCombobox(QString str)
{
    ui->formulaComboBox->addItems(model->findFormulas(str));
}

void AsignacionWidget::cargarAsignacion(Asignacion asignacion)
{
    ui->codigoLineEdit->setText(asignacion.getCodigo());
    ui->descripcionLineEdit->setText(asignacion.getDescripcion());
    ui->primaCheckBox->setChecked(asignacion.hasPrima());
    ui->activoCheckBox->setChecked(asignacion.isActivo());
    ui->fechaLineEdit->setText(asignacion.getFecha());

    for (int i=0; i < ui->FormaComboBox->count() ;i++) {
        ui->FormaComboBox->setCurrentIndex(i);
           if (ui->FormaComboBox->currentText() == asignacion.getForma()) {
               updateFormaParameters();
               break;
           }
    }
    for (int i=0; i < ui->formulaComboBox->count() ;i++)
    {
        ui->formulaComboBox->setCurrentIndex(i);
           if (ui->formulaComboBox->currentText() == asignacion.getFormula()) {
               updateFormaParameters();
               break;
           }
    }

    ui->valorDoubleSpinBox->setValue(asignacion.getValor());
}

Asignacion AsignacionWidget::descargarAsignacion()
{
    asignacion = Asignacion(
                ui->codigoLineEdit->text(),
                ui->descripcionLineEdit->text(),
                ui->FormaComboBox->currentText(),
                ui->valorDoubleSpinBox->value(),
                ui->formulaComboBox->currentText(),
                ui->primaCheckBox->isChecked(),
                ui->activoCheckBox->isChecked());

    return asignacion;
}

void AsignacionWidget::updateFormaParameters()
{
    if (ui->FormaComboBox->currentText() == "FORMULA")
    {
        ui->formulaComboBox->setVisible(true);
        ui->formulaLabel->setVisible(true);
    } else
    {
        ui->formulaComboBox->setVisible(false);
        ui->formulaLabel->setVisible(false);
        ui->formulaComboBox->setCurrentIndex(0);

        if (ui->FormaComboBox->currentText() == "VALOR")
        {
            ui->valorDoubleSpinBox->setMaximum(999999999.99);
            ui->valorDoubleSpinBox->setSuffix(" Bs.");
        } else
        {
            ui->valorDoubleSpinBox->setMaximum(100);
            ui->valorDoubleSpinBox->setSuffix(" %  ");
        }
    }
}

void AsignacionWidget::setValidadores()
{
    ui->codigoLineEdit->setValidator(&codigoValidador);
    ui->descripcionLineEdit->setValidator(&upperCaseValidador);
}

bool AsignacionWidget::validarDatos()
{
    QString advertencias = "";

    if (ui->formulaComboBox->isVisible() && ui->formulaComboBox->currentText().isEmpty())
    {
        advertencias = "- <b>Campo Formula no Puede estar en Blanco<b> \n"+ advertencias;
        ui->formulaComboBox->setFocus();
    }

     if (ui->descripcionLineEdit->text().isEmpty())
     {
         advertencias = "- <b>Campo Descripción no Puede estar en Blanco<b> \n"+ advertencias;
         ui->descripcionLineEdit->setFocus();
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

void AsignacionWidget::on_agregarPushButton_clicked()
{
    setState(State::agregar);
}

void AsignacionWidget::on_modificarPushButton_clicked()
{
    setState(State::modificar);
}

void AsignacionWidget::on_eliminarPushButton_clicked()
{
    eliminarAsignacion();
}

void AsignacionWidget::on_accionPushButton_clicked()
{
    if (validarDatos())
    {
        if (state == State::agregar)
            agregarAsignacion();
        else if (state == State::modificar)
            modificarAsignacion();
    }
}

void AsignacionWidget::on_FormaComboBox_currentIndexChanged(int index)
{
    (void) index;
    updateFormaParameters();
}

void AsignacionWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableView(arg1);
}

void AsignacionWidget::on_codigoLineEdit_editingFinished()
{
    QString codigo = ui->codigoLineEdit->text();
    if (model->asignacionExist(codigo)){
        ui->codigoLineEdit->blockSignals(true);
        QMessageBox::warning(this,"ALERTA","Codigo ya se encuentra Registrado");
        ui->codigoLineEdit->blockSignals(false);
        ui->codigoLineEdit->setFocus();
        ui->codigoLineEdit->clear();
    }
}

void AsignacionWidget::on_cancelarPushButton_clicked()
{
    cancelar();
}
