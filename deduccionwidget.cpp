#include "deduccionwidget.h"
#include "ui_deduccionwidget.h"

#include <QListWidget>

DeduccionWidget::DeduccionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeduccionWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    model = new DeduccionModel("deduccion","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

DeduccionWidget::~DeduccionWidget()
{
    delete model;
    delete ui;
}

void DeduccionWidget::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    formaModel = new QSqlQueryModel(this);
    setState(State::inicial);
    setValidadores();
    updateTableView();
    updateFormaComboBox();
    updateFormulaCombobox();
    ui->deduccionTableView->selectRow(0);

}

void DeduccionWidget::setState(DeduccionWidget::State xstate)
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

void DeduccionWidget::stateAgregar()
{
    ui->DeduccionTabWidget->setCurrentIndex(0);

    ui->codigoLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setEnabled(true);
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->codigoLineEdit->setEnabled(true);
    ui->formulaComboBox->setEnabled(true);
    ui->formulaLabel->setEnabled(true);
    ui->activoCheckBox->setEnabled(true);
    ui->activoCheckBox->setChecked(true);
    ui->codigoLineEdit->clear();
    ui->descripcionLineEdit->clear();
    ui->FormaComboBox->setCurrentIndex(0);
    ui->valorDoubleSpinBox->setValue(100);
    ui->codigoLineEdit->setFocus();

    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Agregar");

    ui->busquedaComboBox->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->deduccionTableView->setEnabled(false);
    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);

}

void DeduccionWidget::stateModificar()
{
    ui->DeduccionTabWidget->setCurrentIndex(0);

    ui->descripcionLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setFocus();
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->formulaComboBox->setEnabled(true);
    ui->formulaLabel->setEnabled(true);
    ui->activoCheckBox->setEnabled(true);
    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Modificar");

    ui->codigoLineEdit->setEnabled(false);
    ui->busquedaComboBox->setEnabled(false);
    ui->deduccionTableView->setEnabled(false);
    ui->busquedaLineEdit->setEnabled(false);
    ui->agregarPushButton->setEnabled(false);
    ui->modificarPushButton->setEnabled(false);
    ui->eliminarPushButton->setEnabled(false);

}

void DeduccionWidget::stateInicial()
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

    ui->busquedaComboBox->setEnabled(true);
    ui->busquedaLineEdit->setEnabled(true);
    ui->deduccionTableView->setEnabled(true);
    ui->agregarPushButton->setEnabled(true);
    ui->modificarPushButton->setEnabled(true);
    ui->eliminarPushButton->setEnabled(true);

    ui->accionPushButton->setText("Aceptar");

    ui->busquedaLineEdit->setFocus();
}

void DeduccionWidget::cancelar() {

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

void DeduccionWidget::status()
{
    ui->statusLabel->setText("Status: "+model->getStatusMessage());
}

void DeduccionWidget::agregarDeduccion()
{
    model->insertDeduccion(descargarDeduccion());
    status();
    updateTableView();
    setState(State::inicial);
}

void DeduccionWidget::modificarDeduccion()
{
    model->updateDeduccion(descargarDeduccion());
    status();
    updateTableView();
    setState(State::inicial);
}

void DeduccionWidget::eliminarDeduccion()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    deduccion = descargarDeduccion();

    if (msg.question(this,"¿Pregunta?","¿Desea Eliminar Deducción? \nCodigo: " + deduccion.getCodigo() +"\n"
                         + "Descripcion: " +deduccion.getDescripcion()) == QMessageBox::Yes){

        model->DeleteDeduccion(deduccion.getCodigo());
        status();
        updateTableView();
        setState(State::inicial);
        }
}

void DeduccionWidget::updateTableView(QString str){

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

void DeduccionWidget::updateFormaComboBox(QString str)
{
    formaModel->setQuery(model->findForma(str));
    ui->FormaComboBox->setModel(formaModel);
    ui->FormaComboBox->setModelColumn(1);
}

void DeduccionWidget::updateFormulaCombobox(QString str)
{
    ui->formulaComboBox->addItems(model->findFormulas(str));
}

void DeduccionWidget::cargarDeduccion(Deduccion deduccion)
{
    ui->codigoLineEdit->setText(deduccion.getCodigo());
    ui->descripcionLineEdit->setText(deduccion.getDescripcion());
    ui->activoCheckBox->setChecked(deduccion.isActivo());
    ui->fechaLineEdit->setText(deduccion.getFecha());

    for (int i=0; i < ui->FormaComboBox->count() ;i++) {
        ui->FormaComboBox->setCurrentIndex(i);
           if (ui->FormaComboBox->currentText() == deduccion.getForma()) {
               updateFormaParameters();
               break;
           }   
    }
    for (int i=0; i < ui->formulaComboBox->count() ;i++)
    {
        ui->formulaComboBox->setCurrentIndex(i);
           if (ui->formulaComboBox->currentText() == deduccion.getFormula()) {
               updateFormaParameters();
               break;
           }
    }

    ui->valorDoubleSpinBox->setValue(deduccion.getValor());
}

Deduccion DeduccionWidget::descargarDeduccion()
{
    deduccion = Deduccion(
                ui->codigoLineEdit->text(),
                ui->descripcionLineEdit->text(),
                ui->FormaComboBox->currentText(),
                ui->valorDoubleSpinBox->value(),
                ui->formulaComboBox->currentText(),
                ui->activoCheckBox->isChecked());
    return deduccion;
}

void DeduccionWidget::deduccionTableViewSelectionChange(){

    QModelIndex myIndex= ui->deduccionTableView->model()->index(ui->deduccionTableView->currentIndex().row(),0);
    QString codigo = ui->deduccionTableView->model()->data(myIndex).toString();
    deduccion = Deduccion(model->findDeduccion(codigo));
    status();
    if (!(deduccion.getCodigo() == "DEFAULT")) {
        cargarDeduccion(deduccion);
    }
}

void DeduccionWidget::on_cancelarPushButton_clicked()
{
    cancelar();
}

void DeduccionWidget::on_agregarPushButton_clicked()
{
    setState(State::agregar);
}
void DeduccionWidget::on_modificarPushButton_clicked()
{
    setState(State::modificar);
}
void DeduccionWidget::on_eliminarPushButton_clicked()
{
    eliminarDeduccion();
}

void DeduccionWidget::on_accionPushButton_clicked()
{
    if (validarDatos())
    {
        if (state == State::agregar)
            agregarDeduccion();
        else if (state == State::modificar)
            modificarDeduccion();
    }
}

void DeduccionWidget::updateFormaParameters (){

    if (ui->FormaComboBox->currentText() == "FORMULA")
    {
        ui->formulaComboBox->setVisible(true);
        ui->formulaLabel->setVisible(true);
        updateFormulaCombobox();
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

void DeduccionWidget::setValidadores()
{
    ui->codigoLineEdit->setValidator(&codigoValidador);
    ui->descripcionLineEdit->setValidator(&upperCaseValidador);
}

bool DeduccionWidget::validarDatos()
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

void DeduccionWidget::on_FormaComboBox_currentIndexChanged(int index)
{
    (void) index;
    updateFormaParameters();
}

void DeduccionWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableView(arg1);
}

void DeduccionWidget::on_codigoLineEdit_editingFinished()
{
    QString codigo = ui->codigoLineEdit->text();
    if (model->deduccionExist(codigo)){
        ui->codigoLineEdit->blockSignals(true);
        QMessageBox::warning(this,"ALERTA","Codigo ya se encuentra Registrado");
        ui->codigoLineEdit->blockSignals(false);
        ui->codigoLineEdit->setFocus();
        ui->codigoLineEdit->clear();
    }
}
