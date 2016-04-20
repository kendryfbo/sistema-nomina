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
    model->setDebug(false);
    prepareWidget();
}

DeduccionWidget::~DeduccionWidget()
{
    delete tableModel;
    delete model;
    delete ui;
}

void DeduccionWidget::prepareWidget()
{
    tableModel = new QSqlQueryModel(this);
    setState(State::inicial);
    updateTableView();
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
    ui->codigoLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setEnabled(true);
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);
    ui->codigoLineEdit->setEnabled(true);

    ui->codigoLineEdit->clear();
    ui->descripcionLineEdit->clear();
    ui->FormaComboBox->setCurrentIndex(0);
    ui->valorDoubleSpinBox->setValue(1);
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
    ui->descripcionLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setFocus();
    ui->FormaComboBox->setEnabled(true);
    ui->valorDoubleSpinBox->setEnabled(true);


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

    ui->codigoLineEdit->setEnabled(false);
    ui->descripcionLineEdit->setEnabled(false);
    ui->FormaComboBox->setEnabled(false);
    ui->valorDoubleSpinBox->setEnabled(false);
    ui->codigoLineEdit->setEnabled(false);

    ui->accionPushButton->setEnabled(false);

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
    ui->statusLabel->setText(model->getStatusMessage());
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
        tableModel->setQuery(model->findDeducciones(str,DeduccionModel::Campo::descripcion));
    else if (ui->busquedaComboBox->currentIndex() == 1)
        tableModel->setQuery(model->findDeducciones(str,DeduccionModel::Campo::codigo));
    else
        tableModel->setQuery(model->findDeducciones(str,DeduccionModel::Campo::descripcion));

    ui->deduccionTableView->setModel(tableModel);
    QObject::connect(ui->deduccionTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(deduccionTableViewSelectionChange()));
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
               updateValorDoubleSpinBoxParameters(i);
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
    if (state == State::agregar)
        agregarDeduccion();
    else if (state == State::modificar)
        modificarDeduccion();
}

void DeduccionWidget::updateValorDoubleSpinBoxParameters (int index){
    if (index == 0)
    {
        ui->valorDoubleSpinBox->setMaximum(100);
        ui->valorDoubleSpinBox->setSuffix(" %  ");
    }else if (index == 1)
    {
        ui->valorDoubleSpinBox->setMaximum(999999999.99);
        ui->valorDoubleSpinBox->setSuffix(" Bs.");
    }
}

void DeduccionWidget::on_FormaComboBox_currentIndexChanged(int index)
{
    updateValorDoubleSpinBoxParameters(index);
}
