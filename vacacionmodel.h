#ifndef VACACIONMODEL_H
#define VACACIONMODEL_H


#include "model.h"
#include "vacacion.h"
#include "nominamodel.h"
class VacacionModel : public Model
{
public:

    // CONSTRUCTORS
    VacacionModel(connDB conn);
    VacacionModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort);
    VacacionModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort);

    // DESTRUCTOR
    ~VacacionModel();

    // Generation of all employees vacations in selected area from vacation
    bool generateVacacion(Vacacion vacacion,int diasBono,int diasAjuste); // falta por implementar

    // Insert deducciones a procesar en vacacion Generada
    bool insertDeduccionEnVacacion(QString deduccionCod,int cantidad);


    // Process of all employees vacations from the corresponding vacacion cargada num
    processVacacion(int vacacionNum); // falta por implementar


private:

    QStringList findEmpeladosFromArea(QString areaCod);

    // Insert and Delete from table 'vacacioncargada'
    bool insertVacacionCargada(Vacacion vacacion);
    bool deleteVacacionCargada(int vacacionNum);
    Vacacion findVacacionCargada(int VacacionNum);


    // Cargar todos los empleados que pertenecen al area de las vacaciones
    bool insertVacacionCargadaDetalles(Vacacion vacacion,int diasBono,int diasAjuste);
    // Insert, Update and Delete from table 'vacaciondetalle'
    bool insertVacacionCargadaDetalleEmp(int vacacionNum,QString empleadoCed,int diasBono,int diasAjuste);

    /* Para futuras mejoras en donde se puedan eliminar empleados de las vacaciones cargadas
     * deleteVacacionDetalleCargada();
     */

    // Insert, Update and Delete from table 'vacaciondetallededuccion'
    insertVacacionCargadaDeducciones(); // falta por implementar
    // Insert, Update and Delete from table 'vacaciondetallededuccion'
    insertVacacionCargadaDeduccion(); // falta por implementar
    updateVacacionCargadaDeduccion(); // falta por implementar
    deleteVacacionCargadaDeduccion(); // falta por implementar

    // Obtener Montos de bono Vacacional y Ajuste Salarial
    double getBonoVacacional(int vacacionNum,QString empleadoCed); // falta por implementar
    double getajusteSalario(int vacacionNum,QString empleadoCed); // falta por implementar
    double getBonoIntegral(int vacacionNum,QString empleadoCed);
};

#endif // VACACIONMODEL_H
