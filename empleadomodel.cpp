#include "empleadomodel.h"

const QString TABLE_EMPLEADO = "empleado";
const QString TABLE_DEDUCCION = "deduccionemp";
const QString TABLE_ASIGNACION = "asignacionemp";
const QString TABLE_NOMINAPROCESADA = "nominaprocesada";
const QString TABLE_AREA= "area";
const QString TABLE_CLASIFIC = "clasificacion";
const QString TABLE_NOMINAPROCESADADETALLERESUMVIEW = "nominaprocesadadetalleresumview";

EmpleadoModel::EmpleadoModel(connDB conn)
{
    query = new QSqlQuery(conn.db);
}
EmpleadoModel::EmpleadoModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);

}

EmpleadoModel::EmpleadoModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
}

EmpleadoModel::~EmpleadoModel()
{
    delete query;
}

bool EmpleadoModel::insertEmpleado(Empleado empleado)
{
    query->prepare("INSERT INTO "+TABLE_EMPLEADO+" ("
                   "cedula,nombres,apellidos,rif,fechanac,lugarnac,email,edocivil,numhijos,"
                   "direccion,tlf1,tlf2,nivelacad,espec,nivelsup,titulo,cod_area,cod_clasif,nivel"
                   ",horas,contrato,fecha_ingeduc,fecha_ingeducpriv,fecha_ing,status)"
                   "Values ("
                   ":cedula,:nombres,:apellidos,:rif,:fechanac,:lugarnac,:email,:edocivil,:numhijos,:"
                   "direccion,:tlf1,:tlf2,:nivelacad,:espec,:nivelsup,:titulo,:cod_area,:cod_clasif,:nivel"
                   ",:horas,:contrato,:fecha_ingeduc,:fecha_ingeducpriv,:fecha_ing,:status)");

    query->bindValue(":cedula",empleado.getCedula());
    query->bindValue(":nombres",empleado.getNombres());
    query->bindValue(":apellidos",empleado.getApellidos());
    query->bindValue(":rif",empleado.getRif());
    query->bindValue(":fechanac",empleado.getFechaNac());
    query->bindValue(":lugarnac",empleado.getLugarNac());
    query->bindValue(":email",empleado.getEmail());
    query->bindValue(":edocivil",empleado.getEdoCivil());
    query->bindValue(":numhijos",empleado.getNumHijos());
    query->bindValue(":direccion",empleado.getDireccion());
    query->bindValue(":tlf1",empleado.getTlf1());
    query->bindValue(":tlf2",empleado.getTlf2());
    query->bindValue(":nivelacad",empleado.getNivelAcad());
    query->bindValue(":espec",empleado.getEspec());
    query->bindValue(":nivelsup",empleado.getNivelAcadSup());
    query->bindValue(":titulo",empleado.getTitulo());
    query->bindValue(":cod_area",empleado.getArea());
    query->bindValue(":cod_clasif",empleado.getClasificacion().getCodigo());
    query->bindValue(":nivel",empleado.getNivel());
    query->bindValue(":horas",empleado.getHoras());
    query->bindValue(":contrato",empleado.getContrato());
    query->bindValue(":fecha_ingeduc",empleado.getFechaIngrEduc());
    query->bindValue(":fecha_ingeducpriv",empleado.getFechaIngrEducPriv());
    query->bindValue(":fecha_ing",empleado.getFechaIng());
    query->bindValue(":status",empleado.getStatus());

    if (!query->exec()){
        status = "Error al Insertar Empleado: " + query->lastError().text();
        debugMessage(status);
        //debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Empleado Insertado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool EmpleadoModel::updateEmpleado(Empleado empleado)
{
    query->prepare("UPDATE  "+TABLE_EMPLEADO+" SET "
                                            "nombres=:nombres,apellidos=:apellidos,rif=:rif,fechanac=:fechanac,lugarnac=:lugarnac,email=:email,edocivil=:edocivil,"
                                              "numhijos=:numhijos,direccion=:direccion,tlf1=:tlf1,tlf2=:tlf2,nivelacad=:nivelacad,espec=:espec,nivelsup=:nivelsup,"
                                              "titulo=:titulo,cod_area=:cod_area,cod_clasif=:cod_clasif,nivel=:nivel,horas=:horas,contrato=:contrato,"
                                              "fecha_ingeduc=:fecha_ingeduc,fecha_ingeducpriv=:fecha_ingeducpriv,fecha_ing=:fecha_ing,"
                                              "status=:status WHERE cedula=:cedula");

    query->bindValue(":cedula",empleado.getCedula());
    query->bindValue(":nombres",empleado.getNombres());
    query->bindValue(":apellidos",empleado.getApellidos());
    query->bindValue(":rif",empleado.getRif());
    query->bindValue(":fechanac",empleado.getFechaNac());
    query->bindValue(":lugarnac",empleado.getLugarNac());
    query->bindValue(":email",empleado.getEmail());
    query->bindValue(":edocivil",empleado.getEdoCivil());
    query->bindValue(":numhijos",empleado.getNumHijos());
    query->bindValue(":direccion",empleado.getDireccion());
    query->bindValue(":tlf1",empleado.getTlf1());
    query->bindValue(":tlf2",empleado.getTlf2());
    query->bindValue(":nivelacad",empleado.getNivelAcad());
    query->bindValue(":espec",empleado.getEspec());
    query->bindValue(":nivelsup",empleado.getNivelAcadSup());
    query->bindValue(":titulo",empleado.getTitulo());
    query->bindValue(":cod_area",empleado.getArea());
    query->bindValue(":cod_clasif",empleado.getClasificacion().getCodigo());
    query->bindValue(":nivel",empleado.getNivel());
    query->bindValue(":horas",empleado.getHoras());
    query->bindValue(":contrato",empleado.getContrato());
    query->bindValue(":fecha_ingeduc",empleado.getFechaIngrEduc());
    query->bindValue(":fecha_ingeducpriv",empleado.getFechaIngrEducPriv());
    query->bindValue(":fecha_ing",empleado.getFechaIng());
    query->bindValue(":status",empleado.getStatus());

    if (!query->exec()){
        status = "Error al Actualizar Empleado: " + query->lastError().text();
        debugMessage(status);
        //debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Empleado Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool EmpleadoModel::deleteEmpleado(QString cedula)
{

    query->prepare("DELETE FROM "+TABLE_EMPLEADO+" WHERE cedula=:cedula");
    query->bindValue(":cedula",cedula);

    if (!query->exec()){
        status = "Error al Eliminar Empleado: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else {
        status = "Empleado Eliminado Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool EmpleadoModel::empleadoExist(QString cedula)
{
    Empleado empleado = findEmpleado(cedula);
    if (empleado.getCedula() == "DEFAULT")
        return false;
    else
        return true;
}

Empleado EmpleadoModel::findEmpleado(QString cedula)
{

    Empleado empleado;
    query->prepare("SELECT * FROM "+TABLE_EMPLEADO+" where cedula=:cedula");
    query->bindValue(":cedula",cedula);

    if (!query->exec())
    {
        status = "ERROR al buscar Empleado: " + query->lastError().text();
        debugMessage(status);

    } else if (!query->next())
    {
        status = "Empleado numero de cedula: " +cedula+" No existe.";
        debugMessage(status);
    } else
    {
        Clasificacion clasificacion(findClasificacion(query->value("cod_clasif").toString()));
        empleado = Empleado(
                    query->value("cedula").toString(),
                    query->value("nombres").toString(),
                    query->value("apellidos").toString(),
                    query->value("rif").toString(),
                    query->value("fechanac").toString(),
                    query->value("lugarnac").toString(),
                    query->value("email").toString(),
                    query->value("edocivil").toString(),
                    query->value("numhijos").toInt(),
                    query->value("direccion").toString(),
                    query->value("tlf1").toString(),
                    query->value("tlf2").toString(),
                    query->value("nivelacad").toString(),
                    query->value("espec").toString(),
                    query->value("nivelsup").toBool(),
                    query->value("titulo").toString(),
                    query->value("fecha_ingeduc").toString(),
                    query->value("fecha_ingeducpriv").toString(),
                    query->value("fecha_ing").toString(),
                    query->value("status").toString(),
                    query->value("cod_area").toString(),
                    clasificacion,
                    query->value("nivel").toString(),
                    query->value("horas").toInt(),
                    query->value("salariohora").toDouble(),
                    query->value("salariodia").toDouble(),
                    query->value("salariasem").toDouble(),
                    query->value("salariomes").toDouble(),
                    query->value("contrato").toString(),
                    query->value("antiguedad").toInt()
                    );
       status = "Empleado Encontrado...";
       debugMessage(status);
    }

    return empleado;
}

QSqlQuery EmpleadoModel::findEmpleados(QString str, Campo campo, Status empStatus, bool ini, bool fin)
{
    QString sql;

    if (ini)
        str = "%"+str;
    if (fin)
        str = str+"%";

    if (campo == Campo::cedula)
        sql = "SELECT cedula,nombres,apellidos FROM "+TABLE_EMPLEADO+" WHERE cedula LIKE ('"+str+"')";
    else if (campo == Campo::nombre)
        sql = "SELECT cedula,nombres,apellidos FROM "+TABLE_EMPLEADO+" WHERE nombres LIKE ('"+str+"')";
    else if (campo == Campo::apellido)
        sql = "SELECT cedula,nombres,apellidos FROM "+TABLE_EMPLEADO+" WHERE apellidos LIKE ('"+str+"')";

    if (empStatus == Status::activo)
        sql = sql + " AND status='ACTIVO'";
    else  if (empStatus == Status::inactivo)
        sql = sql + " AND status='INACTIVO'";
    else  if (empStatus == Status::vacacion)
        sql = sql + " AND status='VACACION'";
    else  if (empStatus == Status::reposo)
        sql = sql + " AND status='REPOSO'";

     query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Empleados: " + query->lastError().text();
         debugMessage(status);
         //debugMessage(query->executedQuery());
     }else {
         status = "Busqueda de Empleados Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

bool EmpleadoModel::insertDeduccion(QString codigo, QString cedulaEmp, QString tipo, int cantidad)
{
    query->prepare("INSERT INTO "+TABLE_DEDUCCION+" ("
                                                  "ced_emp,cod_deduccion,tipo,cantidad) VALUES ("
                                                  ":ced_emp,:cod_deduccion,:tipo,:cantidad)");

    query->bindValue(":ced_emp",cedulaEmp);
    query->bindValue(":cod_deduccion",codigo);
    query->bindValue(":tipo",tipo);
    query->bindValue(":cantidad",cantidad);

    if(query->exec())
    {
        status = "ERROR al Insertar Deducción a Empleado: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        status = "Deducción Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool EmpleadoModel::eliminarDeduccion(QString codigo, QString cedulaEmp)
{
    query->prepare("DELETE FROM "+TABLE_DEDUCCION+" WHERE cod_deduccion=:codigo AND ced_emp=:cedula");
    query->bindValue(":codigo",codigo);
    query->bindValue(":cedula",cedulaEmp);

    if (!query->exec())
    {
        status = "ERROR al Eliminar Deducción a Empleado: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        status = "Deducción Eliminada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

QSqlQuery EmpleadoModel::findDeduccion(QString codigo, QString cedulaEmp)
{
    query->prepare("SELECT * FROM "+TABLE_DEDUCCION+" WHERE cod_deduccion=:cod_deduccion AND ced_emp=:ced_emp");

    query->bindValue(":cod_deduccion",codigo);
    query->bindValue(":ced_emp",cedulaEmp);

    if (!query->exec())
    {
        status = "ERROR al Buscar Deducción de Empleado: " + query->lastError().text();
        debugMessage(status);

    } else if (!query->next())
    {
        status = "Deducción de Empleado numero de codigo: " +codigo+" No existe.";
        debugMessage(status);
    } else
    {    
        status = "Deducción de Empleado Encontrada...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery EmpleadoModel::findDeducciones(QString cedulaEmp, QString deduccion, Tipo tipo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        deduccion = "%"+deduccion;
    if (fin)
        deduccion = deduccion+"%";

    if (tipo == Tipo::fija)
        sql = "SELECT cod_deduccion, (SELECT descripcion FROM deduccionconcepto WHERE deduccionconcepto.codigo=deduccionemp.cod_deduccion) AS Deducción, cantidad AS Cantidad FROM "+TABLE_DEDUCCION+" WHERE cod_deduccion LIKE('"+deduccion+"') AND ced_emp="+cedulaEmp+" AND tipo LIKE('FIJA')";
    if (tipo == Tipo::eventual)
        sql = "SELECT cod_deduccion, (SELECT descripcion FROM deduccionconcepto WHERE deduccionconcepto.codigo=deduccionemp.cod_deduccion) AS Deducción, cantidad AS Cantidad FROM "+TABLE_DEDUCCION+" WHERE cod_deduccion LIKE('"+deduccion+"') AND ced_emp="+cedulaEmp+" AND tipo LIKE('EVENTUAL')";

        query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Deducción de Empleado: " + query->lastError().text();
         debugMessage(status);
         debugMessage(query->executedQuery());
     }else {
         status = "Busqueda de Deducción de Empleado Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

bool EmpleadoModel::insertAsignacion(QString codigo, QString cedulaEmp, QString tipo, int cantidad)
{
    query->prepare("INSERT INTO "+TABLE_ASIGNACION+" ("
                                                  "ced_emp,cod_asignacion,tipo,cantidad) VALUES ("
                                                  ":ced_emp,:cod_asignacion,:tipo,:cantidad)");

    query->bindValue(":ced_emp",cedulaEmp);
    query->bindValue(":cod_asignacion",codigo);
    query->bindValue(":tipo",tipo);
    query->bindValue(":cantidad",cantidad);

    if(query->exec())
    {
        status = "ERROR al Insertar Asignación a Empleado: " +query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        status = "Asignación Insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool EmpleadoModel::eliminarAsignacion(QString codigo, QString cedulaEmp)
{
    query->prepare("DELETE FROM "+TABLE_ASIGNACION+" WHERE cod_asignacion='"+codigo+"' AND ced_emp='"+cedulaEmp+"'");

    if (!query->exec())
    {
        status = "ERROR al Eliminar Asignación a Empleado: " +query->lastError().text();
        debugMessage(status);
        debugMessage(query->lastQuery());
        return false;
    } else {
        status = "Asignación Eliminada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

QSqlQuery EmpleadoModel::findAsignacion(QString codigo, QString cedulaEmp)
{
    query->prepare("SELECT * FROM "+TABLE_ASIGNACION+" WHERE cod_asignacion=:cod_asignacion AND ced_emp=:ced_emp");

    query->bindValue(":cod_asignacion",codigo);
    query->bindValue(":ced_emp",cedulaEmp);

    if (!query->exec())
    {
        status = "ERROR al Buscar Asignación de Empleado: " + query->lastError().text();
        debugMessage(status);

    } else if (!query->next())
    {
        status = "Asignación de Empleado numero de codigo: " +codigo+" No existe.";
        debugMessage(status);
    } else
    {
        status = "Asignación de Empleado Encontrada...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery EmpleadoModel::findAsignaciones(QString cedulaEmp,QString asignacion,EmpleadoModel::Tipo tipo, bool ini, bool fin)
{
    QString sql;

    if (ini)
        asignacion = "%"+asignacion;
    if (fin)
        asignacion = asignacion+"%";

    if (tipo == Tipo::fija)
        sql = "SELECT cod_asignacion, (SELECT descripcion FROM asignacionconcepto WHERE asignacionconcepto.codigo=asignacionemp.cod_asignacion) AS Asignación, cantidad AS Cantidad FROM "+TABLE_ASIGNACION+" WHERE cod_asignacion LIKE('"+asignacion+"') AND ced_emp="+cedulaEmp+" AND tipo='FIJA'";
    if (tipo == Tipo::eventual)
        sql = "SELECT cod_asignacion, (SELECT descripcion FROM asignacionconcepto WHERE asignacionconcepto.codigo=asignacionemp.cod_asignacion) AS Asignación, cantidad AS Cantidad FROM "+TABLE_ASIGNACION+" WHERE cod_asignacion LIKE('"+asignacion+"') AND ced_emp="+cedulaEmp+" AND tipo='EVENTUAL'";

        query->prepare(sql);

     if (!query->exec())
     {
         status = "Error al Realizar Busqueda de Asignación de Empleado: " + query->lastError().text();
         debugMessage(status);
         //debugMessage(query->executedQuery());
     }else {
         status = "Busqueda de Asignación de Empleado Realizada Exitosamente...";
         debugMessage(status);
     }
     return *query;
}

QSqlQuery EmpleadoModel::findNominaProcesada(QString cedulaEmp, QString str, bool ini, bool fin)
{
    (void) str;
    (void) ini;
    (void) fin;

    query->prepare("SELECT numero,(SELECT descripcion FROM "+TABLE_NOMINAPROCESADA+" WHERE "+TABLE_NOMINAPROCESADA+".numero="+TABLE_NOMINAPROCESADADETALLERESUMVIEW+".numero) as Descripción, "
                                "(SELECT fecha_pago FROM "+TABLE_NOMINAPROCESADA+" WHERE "+TABLE_NOMINAPROCESADA+".numero="+TABLE_NOMINAPROCESADADETALLERESUMVIEW+".numero) as FechaPago,"
                                "FORMAT(salario,2) as Salario,FORMAT(asignacion,2) as Asignacion,FORMAT(deduccion,2) as Deduccion,FORMAT(pago,2) as Pago "
                                "FROM "+TABLE_NOMINAPROCESADADETALLERESUMVIEW+" WHERE cedula=:cedula");

    query->bindValue(":cedula",cedulaEmp);

    if (!query->exec())
    {
        status = "ERROR al buscar Nominas Procesadas de Empleado Cedula:"+cedulaEmp+" error:"+query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
    }else
    {
        status = "Busqueda de Nominas Procesadas de Empleado Cedula:"+cedulaEmp+" Realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery EmpleadoModel::findAreas()
{
    query->prepare("SELECT * FROM "+TABLE_AREA+" WHERE activo=true ");

    if (!query->exec())
    {
        status = "Error al Realizar de Área en Empleado: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
    }else {
        status = "Busqueda de Área en Empleado Realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;


}

Clasificacion EmpleadoModel::findClasificacion(QString codigo)
{
    QSqlQuery clasificQuery = *query;

    clasificQuery.prepare("SELECT * FROM "+TABLE_CLASIFIC+" WHERE codigo=:codigo");
    clasificQuery.bindValue(":codigo",codigo);

    if (!clasificQuery.exec())
    {
        status = "Error al Buscar Clasificación: " + clasificQuery.lastError().text();
        debugMessage(status);
    }else if (!clasificQuery.next())
    {
        status = "Clasificación Codigo: "+codigo+" No existe.";
        debugMessage(status);
    }else
    {
        Clasificacion clasificacion(
                    clasificQuery.value("codigo").toString(),
                    clasificQuery.value("descripcion").toString(),
                    clasificQuery.value("cod_area").toString(),
                    clasificQuery.value("formapago").toString(),
                    clasificQuery.value("valor").toDouble(),
                    clasificQuery.value("activo").toBool(),
                    clasificQuery.value("fechacreac").toString()
                    );

        status = "Clasificación código:"+codigo+" Encontrada...";
        debugMessage(status);
        return clasificacion;
    }
    return Clasificacion();
}

QSqlQuery EmpleadoModel::findClasificaciones(QString area)
{
    query->prepare("SELECT * FROM "+TABLE_CLASIFIC+" WHERE cod_area=:area AND activo=true");
    query->bindValue(":area",area);

    if (!query->exec())
    {
        status = "Error al Realizar Busqueda de Clasificación en Empleado: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
    }else {
        status = "Busqueda de Clasificación en Empleado Realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}
