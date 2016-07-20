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
    generateVacacion(Vacacion vacacion,int diasBono,int diasAjuste,QStringList codDeducciones); // falta por implementar

    // Process of all employees vacations from the corresponding vacacion cargada num
    processVacacion(int vacacionNum); // falta por implementar


private:

    // Insert, Update and Delete from table 'vacacioncargada'
    insertVacacionCargada(Vacacion vacacion); // falta por implementar
    updateVacacionCargada(Vacacion vacacion); // falta por implementar
    deleteVacacionCargada(int vacacionNum); // falta por implementar

    // Insert, Update and Delete from table 'vacaciondetalle'
    insertVacacionDetalleCargada(int vacacionNum,QString empleadoCed,int diasBono,int diasAjuste); // falta por implementar
    updateVacacionDetalleCargada(int vacacionNum,QString empleadoCed,int diasBono,int diasAjuste); // falta por implementar
    /* Para futuras mejoras en donde se puedan eliminar empleados de las vacaciones cargadas
    * deleteVacacionDetalleCargada();
    */

    // Insert, Update and Delete from table 'vacaciondetallededuccion'
    insertdetalleDeduccionCargada(); // falta por implementar
    updatedetalleDeduccionCargada(); // falta por implementar
    deletedetalleDeduccionCargada();  // falta por implementar

    // Obtener Montos de bono Vacacional y Ajuste Salarial
    double getBonoVacacional(int vacacionNum,QString empleadoCed); // falta por implementar
    double getajusteSalario(int vacacionNum,QString empleadoCed); // falta por implementar

    double getBonoIntegral(int vacacionNum,QString empleadoCed);
};

#endif // VACACIONMODEL_H
