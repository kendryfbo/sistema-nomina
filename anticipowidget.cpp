#include "anticipowidget.h"
#include "ui_anticipowidget.h"

AnticipoWidget::AnticipoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnticipoWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    model = new AnticipoModel("anticipo","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    }
    model->setDebug(true);
    prepareWidget();
}

AnticipoWidget::~AnticipoWidget()
{
    delete model;
    delete ui;
}

void AnticipoWidget::anticipoTableViewSelectionChange()
{
    QString cedula = anticipoModel->record(ui->anticipoTableView->currentIndex().row()).value("cedula").toString();
    QString datos = anticipoModel->record(ui->anticipoTableView->currentIndex().row()).value("datos").toString();
    QString anticipoStr = anticipoModel->record(ui->anticipoTableView->currentIndex().row()).value("monto").toString();
    QLocale c(QLocale::C);
    ui->cedulaLineEdit->setText(cedula);
    ui->datosLineEdit->setText(datos);
    ui->anticipoDoubleSpinBox->setValue(c.toDouble(anticipoStr));
}

void AnticipoWidget::on_generarAnticipoPushButton_clicked()
{
    model->clearAnticipoTemp();
    AnticipoDialog* anticipo = new AnticipoDialog(this);
    if (anticipo->exec() == QDialog::Accepted)
    {
        area = anticipo->getArea();
        descArea = anticipo->getDescArea();
        dias = anticipo->getDias();
        porcentaje = anticipo->getPorcentaje();
       model->generarAnticiposTemp(area,dias,porcentaje);
       updateTableAnticipo();
    }
}

void AnticipoWidget::prepareWidget()
{
    anticipoModel = new QSqlQueryModel(this);
    model->clearAnticipoTemp();
}

void AnticipoWidget::updateTableAnticipo()
{
    anticipoModel->setQuery(model->findAnticipoTempView());
    ui->anticipoTableView->setModel(anticipoModel);
    ui->anticipoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QObject::connect(ui->anticipoTableView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,SLOT(anticipoTableViewSelectionChange()));

}

void AnticipoWidget::updateAnticipoEmpleado()
{
    model->updateAnticipoTemp(ui->cedulaLineEdit->text(),ui->anticipoDoubleSpinBox->value());
}

bool AnticipoWidget::InsertAnticipo()
{
    QString descripcion = ui->descripcionLineEdit->text();
    if (!model->insertAnticipo(descripcion,descArea,dias,porcentaje))
    {
         QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
         return false;
    }
    return true;
}

bool AnticipoWidget::validarDatos()
{
    QString advertencias = "";

    if (anticipoModel->rowCount() <=0)
    {
        advertencias = "- <b>Debe Generar como minimo un Anticipo<b> \n"+ advertencias;
    }

     if (ui->descripcionLineEdit->text().isEmpty())
     {
         advertencias = "- <b>Campo Descripción no Puede estar en Blanco<b> \n"+ advertencias;
         ui->descripcionLineEdit->setFocus();
     }
    if (advertencias == "") return true;
    else {
        QMessageBox::warning(this,"Alerta",advertencias);
        return false;
    }
}

void AnticipoWidget::on_actualizarPushButton_clicked()
{
    updateAnticipoEmpleado();
    updateTableAnticipo();
}

void AnticipoWidget::on_procesarPushButton_clicked()
{
    if (validarDatos())
    {
        if (InsertAnticipo())
        {
            this->close();
        }
    }

}

void AnticipoWidget::on_cancelarPushButton_clicked()
{
    this->close();
}
