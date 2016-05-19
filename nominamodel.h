#ifndef NOMINAMODEL_H
#define NOMINAMODEL_H

#include <QtCore>

#include "model.h"
#include "nomina.h"
#include "empleadomodel.h"
#include "areamodel.h"

class NominaModel : public Model
{
public:

    enum class CampoEmp{cedula,nombres,apellidos};

    NominaModel();
    NominaModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    NominaModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~NominaModel();


    bool insertModeloNomina(QString codigo,QString descripcion,int dias, double porcSueldo,
                            double porcDeduccion, double porcAsignacion);
    bool updateModeloNomina(QString codigo,QString descripcion,int dias, double porcSueldo,
                            double porcDeduccion, double porcAsignacion);
     bool deleteModeloNomina(QString codigo);

     bool nominaModelExist(QString codigo);
     QSqlQuery findNominaModel(QString codigo);
     QSqlQuery findNominasModel(QString descripcion="");



     bool cargarNominaEmpleado(Empleado empleado, Nomina nomina);
     bool cargarNominaArea(QString area,Nomina nomina);
     bool cargarNominaArea(QString area, int Numero);
     bool CargarNomina(QList<QString> area,Nomina nomina);

     bool deleteNominaCargada(int numero);
     bool nominaExiste(int numero);
     Nomina findNominaCargada(int numero);

     QSqlQuery findNominasCargadas();
     QSqlQuery findEmpleadosFromNominaCargada(int numero,QString str = "",CampoEmp campo = CampoEmp::cedula);
     QSqlQuery findAsignNomCargadaFromEmp(int nominaNum,QString cedula);
     QSqlQuery findDeduccNomCargadasFromEmp(int nominaNum,QString cedula);
     
     bool procesarNomina(int nominaNum);
     QSqlQuery findNominasProcesadas();
     Nomina findNominaProcesada(int numero);
      bool nominaProcesadaExiste(int numero);

      QSqlQuery findEmpleadosFromNominaProcesada(int numero,QString str = "",CampoEmp campo = CampoEmp::cedula);
      QSqlQuery findAsignNomProcesadaFromEmp(int nominaNum,QString cedula);
      QSqlQuery findDeduccNomProcesadaCargadasFromEmp(int nominaNum,QString cedula);

private:
     EmpleadoModel* empModel;
     DeduccionModel* deduccModel;
     AsignacionModel* asignacModel;


     // NOMINA CARGADA
     bool  insertNominaCargada(Nomina &nomina,int numero);
     bool insertNominaCargadaDetalle(Nomina &nomina,Empleado &empleado);

     bool insertDeduccionesCargadas(Nomina &nomina,Empleado &empleado);
     bool insertDeduccionCargada(Deduccion &deduccion,Empleado &empleado,int nominaNum, double porcentaje,int cantidad);

     bool insertAsignacionesCargadas(Nomina &nomina,Empleado &empleado);
     bool insertAsignacionCargada(Asignacion &asignacion,Empleado &empleado,int nominaNum, double porcentaje,int cantidad);

      // NOMINA PROCESADA
     bool  insertNominaProcesada(int numero);
     bool insertNominaProcesadaEmp(int numero);
     bool insertDeduccionesProcesadas(int numero);
     bool insertAsignacionesProcesadas(int numero);

    // FORMULAS

     double formulaSSO();
};

#endif // NOMINAMODEL_H
