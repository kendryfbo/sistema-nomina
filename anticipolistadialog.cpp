#include "anticipolistadialog.h"
#include "ui_anticipolistadialog.h"

AnticipoListaDialog::AnticipoListaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnticipoListaDialog)
{
    ui->setupUi(this);

    model = new AnticipoModel("AnticipoListaDialog","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected()){
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->reject();
    }
    model->setDebug(true);
    prepareWidget();
}

AnticipoListaDialog::~AnticipoListaDialog()
{
    delete model;
    delete ui;
}

void AnticipoListaDialog::prepareWidget()
{
    anticipoModel = new QSqlQueryModel(this);
    updateTableAnticipo();
}

void AnticipoListaDialog::updateTableAnticipo(QString descripcion)
{
    anticipoModel->setQuery(model->findAnticiposView(descripcion));
    ui->anticipoTableView->setModel(anticipoModel);
    ui->anticipoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void AnticipoListaDialog::procesarAnticipo()
{
    anticipoId = anticipoModel->record(ui->anticipoTableView->currentIndex().row()).value("id").toInt();
    QString descripcion = anticipoModel->record(ui->anticipoTableView->currentIndex().row()).value("descripcion").toString();
    qDebug() << anticipoId;
    QString info = "Desea procesar Anticipo:"+descripcion+" Numero:"+QString::number(anticipoId)+"?";
    QMessageBox msg;
    msg.setModal(true);
    msg.addButton(QMessageBox::Yes);
    msg.addButton(QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    if (msg.question(this,"Informacion",info) == QMessageBox::Yes)
    {
        return accept();
    }
}

int AnticipoListaDialog::getAnticipoId() const
{
    return anticipoId;
}



void AnticipoListaDialog::on_busquedaLineEdit_textChanged(const QString &arg1)
{
    updateTableAnticipo(arg1);
}

void AnticipoListaDialog::on_aceptarPushButton_clicked()
{
    procesarAnticipo();
}

void AnticipoListaDialog::on_cancelarPushButton_clicked()
{
    reject();
}
