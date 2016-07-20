#include "reportmodel.h"
#include "LimeReport"

const QString reporteReciboDepagoPath="/reportes/ReciboDePago.lrxml";
const QString reporteRecibosDepagoPath="/reportes/RecibosDePago.lrxml";
const QString reporteAnticipoPath="/reportes/ReporteAnticipo.lrxml";
const QString reporteNominaPath="/reportes/ReporteNomina.lrxml";

ReportModel::ReportModel()
{
    report = new LimeReport::ReportEngine();
    rootPath = QApplication::applicationDirPath();
}

ReportModel::~ReportModel()
{
    delete report;
}

void ReportModel::reciboEmpleado(int nominaNum, QString empCedula)
{
    QString path = rootPath + reporteReciboDepagoPath;
    report->loadFromFile(path);
    report->dataManager()->setReportVariable("nominaNum",nominaNum);
    report->dataManager()->setReportVariable("cedulaEmp",empCedula);
    report->setShowProgressDialog(true);
    report->previewReport();
}

void ReportModel::recibosEmpleados(int nominaNum)
{
    QString path = rootPath + reporteRecibosDepagoPath;
    report->loadFromFile(path);
    report->dataManager()->setReportVariable("nominaNum",nominaNum);
    report->setShowProgressDialog(true);
    report->previewReport();



}

void ReportModel::nomina(int nominaNum)
{
    QString path = rootPath + reporteNominaPath;
    report->loadFromFile(path);
    report->dataManager()->setReportVariable("nominaNum",nominaNum);
    report->setShowProgressDialog(true);
    report->previewReport();
}

void ReportModel::anticipo(int anticipoId)
{
    QString path = rootPath + reporteAnticipoPath;
    report->loadFromFile(path);
    report->dataManager()->setReportVariable("anticipoId",anticipoId);
    report->setShowProgressDialog(true);
    report->previewReport();
}
