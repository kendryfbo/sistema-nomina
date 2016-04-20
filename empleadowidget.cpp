#include "empleadowidget.h"
#include "ui_empleadowidget.h"

EmpleadoWidget::EmpleadoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmpleadoWidget)
{
    ui->setupUi(this);
}

EmpleadoWidget::~EmpleadoWidget()
{
    delete ui;
}
