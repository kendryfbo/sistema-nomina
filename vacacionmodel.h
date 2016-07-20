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
    generateVacacion(Vacacion vacacion,int diasBono,int diasAjuste,QStringList codDeducciones);

    // Process of all employees vacations from the corresponding vacacion cargada num
    processVacacion(int vacacionNum);


private:

    // Insert, Update and Delete from table 'vacacioncargada'
    insertVacacionCargada(Vacacion vacacion);
    updateVacacionCargada(Vacacion vacacion);
    deleteVacacionCargada(int vacacionNum);

    // Insert, Update and Delete from table 'vacaciondetalle'
    insertVacacionDetalleCargada(int vacacionNum,QString empleadoCed,int diasBono,int diasAjuste);
    updateVacacionDetalleCargada(int vacacionNum,QString empleadoCed,int diasBono,int diasAjuste);
    /* Para futuras mejoras en donde se puedan eliminar empleados de las vacaciones cargadas
    * deleteVacacionDetalleCargada();
    */

    // Insert, Update and Delete from table 'vacaciondetallededuccion'
    insertdetalleDeduccionCargada(Vacacion vacacion);
    updatedetalleDeduccionCargada(Vacacion vacacion);
    deletedetalleDeduccionCargada(int vacacionNum);

};

#endif // VACACIONMODEL_H
