#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QApplication>
#include "LimeReport"

class ReportModel
{
public:
    ReportModel();

    ~ReportModel();
    void reciboEmpleado(int nominaNum,QString empCedula);
    void recibosEmpleados(int nominaNum);
    void nomina(int nominaNum);
    void anticipo(int anticipoId);

private:

    LimeReport::ReportEngine *report;

    QString rootPath;




};

#endif // REPORTMODEL_H
