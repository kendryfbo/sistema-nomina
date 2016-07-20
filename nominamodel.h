#ifndef NOMINAMODEL_H
#define NOMINAMODEL_H

#include <QtCore>

#include "model.h"
#include "nomina.h"
#include "empleadomodel.h"
#include "areamodel.h"
#include "anticipomodel.h"

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



     bool cargarNominaArea(QString area,Nomina nomina);

     // ACTUALIZAR
      bool cargarNominaEmpleado(Empleado empleado, Nomina nomina);
     // ACTUALIZAR
     bool cargarNominaArea(QString area, int Numero);
     // ACTUALIZAR
     bool CargarNomina(QList<QString> area,Nomina nomina);


     bool deleteNominaCargada(int numero);
     bool nominaExiste(int numero);
     Nomina findNominaCargada(int numero);

     QSqlQuery findNominasCargadas();
     QSqlQuery findEmpleadosFromNominaCargadaDetalle(int numero,QString str = "",CampoEmp campo = CampoEmp::cedula);
     QSqlQuery findEmpleadosFromNominaCargada(int numero,QString str = "",CampoEmp campo = CampoEmp::cedula);
     QSqlQuery findAsignNomCargadaFromEmp(int nominaNum,QString cedula);
     QSqlQuery findDeduccNomCargadasFromEmp(int nominaNum,QString cedula);
     
     bool agregarDeduccionEmpleado(QString deduccionCod,QString empCedula,int nominaNum,int Cantidad);
     bool agregarASignacionEmpleado(QString asignacionCod,QString empCedula,int nominaNum,int Cantidad);
     bool eliminarDeduccionEmpleado(QString deduccionCod,QString empCedula,int nominaNum);
     bool eliminarASignacionEmpleado(QString asignacionCod,QString empCedula,int nominaNum);


     bool procesarNomina(int nominaNum);
     bool deleteNominaProcesada(int nominaNum);

     QSqlQuery findNominasProcesadas();
     Nomina findNominaProcesada(int numero);
      bool nominaProcesadaExiste(int numero);

      QSqlQuery findEmpleadosFromNominaProcesada(int numero,QString str = "",CampoEmp campo = CampoEmp::cedula);
      QSqlQuery findAsignNomProcesadaFromEmp(int nominaNum,QString cedula);
      QSqlQuery findDeduccNomProcesadaCargadasFromEmp(int nominaNum,QString cedula);


      QSqlQuery findAnticiposView();
      bool cargarAnticipos(int anticipoId,int nominaNum);

private:
     EmpleadoModel* empModel;
     DeduccionModel* deduccModel;
     AsignacionModel* asignacModel;


     // NOMINA CARGADA
     bool  insertNominaCargada(Nomina &nomina);
     bool insertNominaCargadaDetalle(Nomina &nomina,Empleado &empleado);

     bool insertDeduccionesCargadas(Nomina &nomina,Empleado &empleado);
     bool insertDeduccionCargada(Deduccion &deduccion,Empleado &empleado,int nominaNum, double porcentaje,int cantidad);
     bool deleteDeduccionCargada(QString deduccionCod,QString empCedula,int nominaNum);

     bool insertAsignacionesCargadas(Nomina &nomina,Empleado &empleado);
     bool insertAsignacionCargada(Asignacion &asignacion,Empleado &empleado,int nominaNum, double porcentaje,int cantidad);
     bool deleteAsignacionCargada(QString asignacionCod,QString empCedula,int nominaNum);

     /* ANTICIPOS */

     // CARGAR ANTICIPOS PENDIENTES POR PROCESAR
     bool insertDeduccionDeAnticipoNomCargada(QString cedulaEmp,QString descripcion,double monto,int anticipoID, int nominaNum);

      // NOMINA PROCESADA
     bool  insertNominaProcesada(int numero);
     bool insertNominaProcesadaEmp(int numero);
     bool insertDeduccionesProcesadas(int numero);
     bool insertAsignacionesProcesadas(int numero);

    // FORMULAS
     double formulaSSO();

     // SALARIO INTEGRAL Y SALARIO BASE
     double getSalarioIntegralFromEmpleado(QString cedulaEmp, int nominaNum);
     double getSalarioBaseFromEmpleado(QString cedulaEmp,int nominaNum);

};

#endif // NOMINAMODEL_H
