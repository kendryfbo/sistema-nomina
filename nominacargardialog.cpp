#include "nominacargardialog.h"
#include "ui_nominacargardialog.h"

NominaCargarDialog::NominaCargarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NominaCargarDialog)
{
    ui->setupUi(this);
    NominaModeloIsCargada = false;
    prepareDialog();


}
NominaCargarDialog::~NominaCargarDialog()
{
    delete area;
    delete ui;
}

void NominaCargarDialog::prepareDialog()
{
    area = new AreaModel("nominaCargarArea","127.0.0.1","nomina","root","19017070",3306);
    nominaModelDialog = new NominaModelDialog(this);
    areaModel = new QSqlQueryModel(this);
    setState(State::inactive);
    buscarNominaModel();
    updateAreaComboBox();
}

void NominaCargarDialog::updateAreaComboBox()
{
    areaModel->setQuery(area->findAreas());
    ui->areaComboBox->setModel(areaModel);
    ui->areaComboBox->setModelColumn(1);
}

void NominaCargarDialog::buscarNominaModel()
{
    if (nominaModelDialog->exec() == QDialog::Accepted)
    {
       cargarDatosNominaModel();
    } else
        setState(State::inactive);
}

void NominaCargarDialog::cargarDatosNominaModel()
{
    ui->codigoNominaModeloLineEdit->setText(nominaModelDialog->getCodigo());
    ui->descripcionNominaModeloLineEdit->setText(nominaModelDialog->getDescripcion());
    ui->diasNominaModeloSpinBox->setValue(nominaModelDialog->getDias());
    ui->salarioNominaModeloDoubleSpinBox->setValue(nominaModelDialog->getSalario());
    ui->deduccionNominaModeloDoubleSpinBox->setValue(nominaModelDialog->getDeduccion());
    ui->asignacionNominaModeloDoubleSpinBox->setValue(nominaModelDialog->getAsignacion());
    setState(State::active);
}

void NominaCargarDialog::cargarNomina()
{
    if (validarDatos())
    {
            Nomina nomina(
                ui->descripcionNominaCargadaLineEdit->text(),
                ui->diasNominaModeloSpinBox->value(),
                ui->salarioNominaModeloDoubleSpinBox->value(),
                ui->deduccionNominaModeloDoubleSpinBox->value(),
                ui->asignacionNominaModeloDoubleSpinBox->value(),
                ui->fechaPagoDateEdit->date().toString("yyyy-MM-dd"),
                ui->fechaPagoDateEdit->date().toString("yyyy-MM-dd"),
                ui->fechaPagoDateEdit->date().toString("yyyy-MM-dd"),
                "root");

            NominaModel nominaModel("nominaCargar","127.0.0.1","nomina","root","19017070",3306);
            QString codigoArea = areaModel->record(ui->areaComboBox->currentIndex()).value("codigo").toString();

            if (!nominaModel.cargarNominaArea(codigoArea,nomina)){
                QMessageBox::warning(NULL,"Alerta",nominaModel.getStatusMessage());
            }else {
                QMessageBox::information(this,"Información","Nomina numero Cargada Exitosamente...");
                accept();
            }
    }
}

bool NominaCargarDialog::validarDatos()
{
    QString advertencias = "";

     if (ui->codigoNominaModeloLineEdit->text().isEmpty())
     {
         advertencias = "- <b>Campo Código Modelo de Nomina no Puede estar en Blanco<b> \n"+ advertencias;
         ui->codigoNominaModeloLineEdit->setFocus();
     }
    if (ui->descripcionNominaCargadaLineEdit->text().isEmpty())
    {
        advertencias = "- <b>Campo Descripción no Puede estar en Blanco<b> \n"+ advertencias;
        ui->descripcionNominaCargadaLineEdit->setFocus();
    }

    if (advertencias == "")
        return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void NominaCargarDialog::setValidadores()
{
    ui->descripcionNominaCargadaLineEdit->setValidator(&upperCaseValidador);
}

void NominaCargarDialog::setState(NominaCargarDialog::State xstate)
{
    state = xstate;
    if (state == State::active){
        stateActive();
    }else if (state == State::inactive){
        stateInactive();
    }
}

void NominaCargarDialog::stateInactive()
{
    ui->datosNominaGroupBox->setEnabled(false);
    ui->cargarNominaPushButton->setEnabled(false);
    ui->codigoNominaModeloLineEdit->setEnabled(true);
    ui->codigoNominaModeloLineEdit->setFocus();
}

void NominaCargarDialog::stateActive()
{
    QDate date = QDate::currentDate();

    ui->datosNominaGroupBox->setEnabled(true);
    ui->cargarNominaPushButton->setEnabled(true);

    ui->codigoNominaModeloLineEdit->setEnabled(false);

    ui->fechaPagoDateEdit->setDate(date);
    ui->fechaDesdeDateEdit->setDate(date);
    ui->fechaHastaDateEdit->setDate(date.addDays(ui->diasNominaModeloSpinBox->value()));
    ui->descripcionNominaCargadaLineEdit->setFocus();
}

void NominaCargarDialog::on_pushButton_clicked()
{
    buscarNominaModel();
}

void NominaCargarDialog::on_cancelarPushButton_clicked()
{
    reject();
}

void NominaCargarDialog::on_cargarNominaPushButton_clicked()
{
    cargarNomina();
}

void NominaCargarDialog::on_prestacionGroupBox_toggled(bool arg1)
{
    if (arg1)
        ui->prestacionGroupBox->setEnabled(true);
    else
        ui->prestacionGroupBox->setEnabled(false);
}
