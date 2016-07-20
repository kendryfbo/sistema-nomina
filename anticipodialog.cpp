#include "anticipodialog.h"
#include "ui_anticipodialog.h"

AnticipoDialog::AnticipoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnticipoDialog)
{
    ui->setupUi(this);

    model = new AreaModel("AnticipoDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->reject();
    }
    model->setDebug(true);
    prepareWidget();
}

AnticipoDialog::~AnticipoDialog()
{
    delete model;
    delete ui;
}

void AnticipoDialog::on_buttonBox_accepted()
{

    area = areaModel->record(ui->AreaComboBox->currentIndex()).value("codigo").toString();
    descArea = areaModel->record(ui->AreaComboBox->currentIndex()).value("descripcion").toString();
    dias = ui->diasSpinBox->value();
    porcentaje = ui->porcentajeDoubleSpinBox->value();
accept();
}

void AnticipoDialog::prepareWidget()
{
    areaModel = new QSqlQueryModel(this);
    areaModel->setQuery(model->findAreas());
    ui->AreaComboBox->setModel(areaModel);
    ui->AreaComboBox->setModelColumn(1);
    ui->AreaComboBox->setFocus();
}

QString AnticipoDialog::getDescArea() const
{
    return descArea;
}

double AnticipoDialog::getPorcentaje() const
{
    return porcentaje;
}

int AnticipoDialog::getDias() const
{
    return dias;
}

QString AnticipoDialog::getArea() const
{
    return area;
}

void AnticipoDialog::on_buttonBox_rejected()
{
    reject();
}
