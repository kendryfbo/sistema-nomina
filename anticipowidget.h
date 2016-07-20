#ifndef ANTICIPOWIDGET_H
#define ANTICIPOWIDGET_H

#include <QWidget>
#include <QtSql>
#include "anticipodialog.h"
#include "anticipomodel.h"

namespace Ui {
class AnticipoWidget;
}

class AnticipoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnticipoWidget(QWidget *parent = 0);
    ~AnticipoWidget();

private slots:
    void anticipoTableViewSelectionChange();

    void on_generarAnticipoPushButton_clicked();

    void on_actualizarPushButton_clicked();

    void on_procesarPushButton_clicked();

    void on_cancelarPushButton_clicked();

private:
    Ui::AnticipoWidget *ui;

    AnticipoModel* model;

   QSqlQueryModel* anticipoModel;

   void prepareWidget();

   void updateTableAnticipo();
   void updateAnticipoEmpleado();
   bool InsertAnticipo();

   bool validarDatos();

   QString area; // CODIGO DE AREA
   QString descArea; // DESCRIPCION DE AREA
   int dias;
   double porcentaje;

};

#endif // ANTICIPOWIDGET_H
