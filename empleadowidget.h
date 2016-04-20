#ifndef EMPLEADOWIDGET_H
#define EMPLEADOWIDGET_H

#include <QWidget>

namespace Ui {
class EmpleadoWidget;
}

class EmpleadoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmpleadoWidget(QWidget *parent = 0);
    ~EmpleadoWidget();

private:
    Ui::EmpleadoWidget *ui;
};

#endif // EMPLEADOWIDGET_H
