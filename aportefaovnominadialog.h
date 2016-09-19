#ifndef APORTEFAOVNOMINADIALOG_H
#define APORTEFAOVNOMINADIALOG_H

#include <QDialog>

namespace Ui {
class aporteFaovNominaDialog;
}

class aporteFaovNominaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aporteFaovNominaDialog(QWidget *parent = 0);
    ~aporteFaovNominaDialog();

private:
    Ui::aporteFaovNominaDialog *ui;
};

#endif // APORTEFAOVNOMINADIALOG_H
