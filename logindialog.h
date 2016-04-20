#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "loginmodel.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:

    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();


private slots:

    void on_userLineEdit_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LoginDialog *ui;

    LoginModel* model;

    void prepareWidget();

    bool checkUserExist();
    bool passwordMatch();
};

#endif // LOGINDIALOG_H
