#include "reportmodel.h"
#include "LimeReport"

const QString reportDir=":/Report";

ReportModel::ReportModel()
{
    report = new LimeReport::ReportEngine();
}

ReportModel::~ReportModel()
{
    delete report;
}

void ReportModel::reciboEmpleado(int nominaNum, QString empCedula)
{
    report->loadFromFile(":/Reportes/Reportes/ReciboDePago.lrxml");
    report->dataManager()->setReportVariable("nominaNum",nominaNum);
    report->dataManager()->setReportVariable("cedulaEmp",empCedula);
    report->setShowProgressDialog(true);
    report->previewReport();
}

void ReportModel::recibosEmpleados(int nominaNum)
{

        report->loadFromFile(":/Reportes/Reportes/RecibosDePago.lrxml");
        report->dataManager()->setReportVariable("nominaNum",nominaNum);
        report->setShowProgressDialog(true);
        report->previewReport();



}

void ReportModel::nomina(int nominaNum)
{
    report->loadFromFile(":/Reportes/Reportes/ReporteNomina.lrxml");
    report->dataManager()->setReportVariable("nominaNum",nominaNum);
    report->setShowProgressDialog(true);
    report->previewReport();
}
