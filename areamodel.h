#ifndef AREAMODEL_H
#define AREAMODEL_H

#include <QtCore>
#include "model.h"
#include "area.h"
#include "clasificacion.h"

class AreaModel : public Model
{
public:

    enum class Campo{codigo,descripcion};

    AreaModel(connDB conn);
    AreaModel(QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);
    AreaModel(QString connName,QString hostName,QString dbName,QString dbUserName,QString dbUserPassword,int dbPort);

    ~AreaModel();

    bool insertArea(Area area);
    bool updateArea(Area area);
    bool deleteArea(QString codigo);

    Area FindArea(QString codigo);
    QSqlQuery findAreas(QString str = "", bool activo=true, Campo campo = Campo::descripcion,bool ini = true ,bool fin = true);

    bool insertClasificacion(Clasificacion clasificacion);
    bool updateClasificacione(Clasificacion clasificacion);
    bool deleteClasificacion(QString codigo);

    bool clasificacionExiste(QString codigo);
    Clasificacion findClasificacion(QString codigo);
    QSqlQuery findClasificaciones(QString str = "", QString area=" ", Campo campo = Campo::descripcion, bool activo=true, bool ini = true , bool fin = true);
};

#endif // AREAMODEL_H
