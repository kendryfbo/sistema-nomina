#include "nominawidget.h"
#include "ui_nominawidget.h"

NominaWidget::NominaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NominaWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    model = new NominaModel("nominaModel","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

NominaWidget::~NominaWidget()
{
    delete model;
    delete ui;
}

void NominaWidget::nominaTableViewSelectionChange()
{
    QModelIndex myIndex= ui->nominaTableView->model()->index(ui->nominaTableView->currentIndex().row(),0);
    QString codigo = ui->nominaTableView->model()->data(myIndex).toString();

    QSqlQuery nominaQuery = model->findNominaModel(codigo);

    codigo = nominaQuery.value("codigo").toString();
    QString descripcion = nominaQuery.value("descripcion").toString();
    int dias = nominaQuery.value("dias").toInt();
    double salario = nominaQuery.value("sueldo_porc").toDouble();
    double deduccion = nominaQuery.value("deducc_porc").toDouble();
    double asignacion = nominaQuery.value("asignac_porc").toDouble();

    ui->codigoLineEdit->setText(codigo);
    ui->descripcionLineEdit->setText(descripcion);
    ui->diasSpinBox->setValue(dias);
    ui->salarioDoubleSpinBox->setValue(salario);
    ui->deduccionDoubleSpinBox->setValue(deduccion);
    ui->asignacionDoubleSpinBox->setValue(asignacion);

}

void NominaWidget::prepareWidget()
{
    tableModel = new QSqlTableModel(this);
     setState(State::inicial);
     updateNominaTableView();
     setValidadores();
}

void NominaWidget::setState(NominaWidget::State xstate)
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

void NominaWidget::stateAgregar()
{
    ui->busquedaLineEdit->setEnabled(false);
    ui->nominaTableView->setEnabled(false);

    ui->codigoLineEdit->setEnabled(true);
    ui->descripcionLineEdit->setEnabled(true);
    ui->diasSpinBox->setEnabled(true);
    ui->salarioDoubleSpinBox->setEnabled(true);
    ui->deduccionDoubleSpinBox->setEnabled(true);
    ui->asignacionDoubleSpinBox->setEnabled(true);

    ui->codigoLineEdit->clear();
    ui->descripcionLineEdit->clear();
    ui->diasSpinBox->setValue(1);
    ui->salarioDoubleSpinBox->setValue(100);
    ui->deduccionDoubleSpinBox->setValue(100);
    ui->asignacionDoubleSpinBox->setValue(100);

    ui->codigoLineEdit->setFocus();

    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Agregar");

}

void NominaWidget::stateModificar()
{
    ui->busquedaLineEdit->setEnabled(false);
    ui->nominaTableView->setEnabled(false);

    ui->descripcionLineEdit->setEnabled(true);
    ui->diasSpinBox->setEnabled(true);
    ui->salarioDoubleSpinBox->setEnabled(true);
    ui->deduccionDoubleSpinBox->setEnabled(true);
    ui->asignacionDoubleSpinBox->setEnabled(true);

    ui->descripcionLineEdit->setFocus();

    ui->accionPushButton->setEnabled(true);
    ui->accionPushButton->setText("Modificar");
}

void NominaWidget::stateInicial()
{
    ui->busquedaLineEdit->setEnabled(true);
    ui->nominaTableView->setEnabled(true);

    ui->codigoLineEdit->setEnabled(false);
    ui->descripcionLineEdit->setEnabled(false);
    ui->diasSpinBox->setEnabled(false);
    ui->salarioDoubleSpinBox->setEnabled(false);
    ui->deduccionDoubleSpinBox->setEnabled(false);
    ui->asignacionDoubleSpinBox->setEnabled(false);

    ui->busquedaLineEdit->setFocus();

    ui->accionPushButton->setEnabled(false);
    ui->accionPushButton->setText("Aceptar");



}

void NominaWidget::cancelar()

{  if (state == State::inicial){
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

void NominaWidget::status()
{
    ui->statusLabel->setText("Status: "+model->getStatusMessage());
}

void NominaWidget::agregarNomina()
{
    model->insertModeloNomina(
                ui->codigoLineEdit->text(),
                ui->descripcionLineEdit->text(),
                ui->diasSpinBox->value(),
                ui->salarioDoubleSpinBox->value(),
                ui->deduccionDoubleSpinBox->value(),
                ui->asignacionDoubleSpinBox->value());
    status();
    updateNominaTableView();
    setState(State::inicial);
}

void NominaWidget::ModificarNomina()
{
    model->updateModeloNomina(
                ui->codigoLineEdit->text(),
                ui->descripcionLineEdit->text(),
                ui->diasSpinBox->value(),
                ui->salarioDoubleSpinBox->value(),
                ui->deduccionDoubleSpinBox->value(),
                ui->asignacionDoubleSpinBox->value());

    status();
    updateNominaTableView();
    setState(State::inicial);
}

void NominaWidget::eliminarNomina()
{
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    QString codigo = ui->codigoLineEdit->text();
    QString descripcion = ui->descripcionLineEdit->text();

    if (msg.question(this,"¿Pregunta?","¿Desea Eliminar Nomina? \nCodigo: " + codigo +"\n"
                         + "Descripcion: " +descripcion) == QMessageBox::Yes){

        model->deleteModeloNomina(codigo);
        status();
        updateNominaTableView();
        setState(State::inicial);
    }

}

void NominaWidget::updateNominaTableView(QString str)
{

    tableModel->setQuery(model->findNominasModel(str));

    ui->nominaTableView->setModel(tableModel);
    QObject::connect(ui->nominaTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(nominaTableViewSelectionChange()));
}

void NominaWidget::setValidadores()
{
    ui->codigoLineEdit->setValidator(&codigoValidador);
    ui->descripcionLineEdit->setValidator(&upperCaseValidador);
}

bool NominaWidget::validarDatos()
{
    QString advertencias = "";

    if (ui->diasSpinBox->value() <= 0)
    {
        advertencias = "- <b>Campo Dias debe ser mayor a 0<b> \n"+ advertencias;
        ui->diasSpinBox->setFocus();
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

void NominaWidget::on_accionPushButton_clicked()
{
    if (validarDatos())
    {
        if (state == State::agregar)
            agregarNomina();
        else if (state == State::modificar)
            ModificarNomina();
    }
}

void NominaWidget::on_agregarPushButton_clicked()
{
    setState(State::agregar);
}

void NominaWidget::on_modificarPushButton_clicked()
{
    setState(State::modificar);
}

void NominaWidget::on_EliminarPushButton_clicked()
{
    eliminarNomina();
}

void NominaWidget::on_cancelarPushButton_clicked()
{
    cancelar();
}

void NominaWidget::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateNominaTableView(arg1);
}
