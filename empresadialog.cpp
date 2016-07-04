#include "empresadialog.h"
#include "ui_empresadialog.h"

empresaDialog::empresaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::empresaDialog)
{
    ui->setupUi(this);
}

empresaDialog::~empresaDialog()
{
    delete ui;
}
