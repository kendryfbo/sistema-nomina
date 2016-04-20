#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    model = new LoginModel("login","127.0.0.1","nomina","root","19017070",3306);

    if (!model->isConected())
    {
        QMessageBox::critical(this,"ERROR CRITICO",model->getStatusMessage(),QMessageBox::Ok);
        this->close();
    } else ui->statusLabel->setText(model->getStatusMessage());

    prepareWidget();
}

LoginDialog::~LoginDialog()
{
    delete model;
    delete ui;
}

void LoginDialog::prepareWidget()
{
      ui->userLineEdit->setFocus();
      this->setWindowTitle("Login");
}

bool LoginDialog::checkUserExist(){

    QString user = ui->userLineEdit->text();
    if (!model->existUsuario(user))
    {
       ui->userLineEdit->setFocus();
       ui->statusLabel->setText(model->getStatusMessage());
       return false;
    }
    ui->statusLabel->setText(model->getStatusMessage());
    return true;
}

bool LoginDialog::passwordMatch(){

    QString user = ui->userLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (!model->matchUserPassword(user,password))
    {
        ui->passwordLineEdit->clear();
        ui->userLineEdit->setFocus();
        ui->userLineEdit->selectAll();
        ui->statusLabel->setText(model->getStatusMessage());
        return false;
    }
    ui->statusLabel->setText(model->getStatusMessage());
    return true;
}

void LoginDialog::on_userLineEdit_editingFinished()
{
    checkUserExist();
}


void LoginDialog::on_pushButton_clicked()
{
    passwordMatch();
}

void LoginDialog::on_pushButton_2_clicked()
{
    this->reject();
}


