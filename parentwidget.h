#ifndef PARENTWIDGET_H
#define PARENTWIDGET_H

#include <QObject>
#include <QWidget>

class ParentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParentWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // PARENTWIDGET_H