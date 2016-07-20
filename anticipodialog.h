#ifndef ANTICIPODIALOG_H
#define ANTICIPODIALOG_H

#include <QDialog>
#include <QMessageBox>


#include "areamodel.h"

namespace Ui {
class AnticipoDialog;
}

class AnticipoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnticipoDialog(QWidget *parent = 0);
    ~AnticipoDialog();


    QString getArea() const;
    int getDias() const;
    double getPorcentaje() const;
    QString getDescArea() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AnticipoDialog *ui;
    AreaModel* model;
    QSqlQueryModel *areaModel;

    void prepareWidget();

    QString area;
    QString descArea;
    int dias;
    double porcentaje;


};

#endif // ANTICIPODIALOG_H
