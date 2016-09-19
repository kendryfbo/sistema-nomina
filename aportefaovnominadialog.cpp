#include "aportefaovnominadialog.h"
#include "ui_aportefaovnominadialog.h"

aporteFaovNominaDialog::aporteFaovNominaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aporteFaovNominaDialog)
{
    ui->setupUi(this);
}

aporteFaovNominaDialog::~aporteFaovNominaDialog()
{
    delete ui;
}
