#ifndef EMPRESADIALOG_H
#define EMPRESADIALOG_H

#include <QDialog>

namespace Ui {
class empresaDialog;
}

class empresaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit empresaDialog(QWidget *parent = 0);
    ~empresaDialog();

private:
    Ui::empresaDialog *ui;
};

#endif // EMPRESADIALOG_H
