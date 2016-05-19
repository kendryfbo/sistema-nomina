#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include "LimeReport"

class ReportModel
{
public:
    ReportModel();

    ~ReportModel();
    void reciboEmpleado(int nominaNum,QString empCedula);
    void recibosEmpleados(int nominaNum);
    void nomina(int nominaNum);

private:

    LimeReport::ReportEngine *report;




};

#endif // REPORTMODEL_H
