#ifndef APORTEFAOVINSERTDIALOG_H
#define APORTEFAOVINSERTDIALOG_H

#include <QDialog>

namespace Ui {
class aporteFaovInsertDialog;
}

class aporteFaovInsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aporteFaovInsertDialog(QWidget *parent = 0);
    ~aporteFaovInsertDialog();

private:
    Ui::aporteFaovInsertDialog *ui;
};

#endif // APORTEFAOVINSERTDIALOG_H
