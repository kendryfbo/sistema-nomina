#ifndef APORTEFAOVINSERTDIALOG_H
#define APORTEFAOVINSERTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class aporteFaovInsertDialog;
}

class aporteFaovInsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aporteFaovInsertDialog(QWidget *parent = 0);
    ~aporteFaovInsertDialog();

    QString getDescripcion() const;
    double getAportePatron() const;
    double getAporteEmpleado() const;

private slots:


    void on_aceptarPushButton_clicked();

    void on_cancelarPushButton_clicked();

private:
    Ui::aporteFaovInsertDialog *ui;

    void prepareWidget();

    bool validarDatos();

    QString descripcion;
    double aportePatron;
    double aporteEmpleado;
};

#endif // APORTEFAOVINSERTDIALOG_H
