#include "aportefaovinsertdialog.h"
#include "ui_aportefaovinsertdialog.h"

aporteFaovInsertDialog::aporteFaovInsertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aporteFaovInsertDialog)
{
    ui->setupUi(this);
}

aporteFaovInsertDialog::~aporteFaovInsertDialog()
{
    delete ui;
}
