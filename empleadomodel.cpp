#include "empleadomodel.h"

const QString TABLE_EMPLEADOS = "empleado";
const QString TABLE_DEDUCCION = "deduccionemp";

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
    query->prepare("INSERT INTO "+TABLE_EMPLEADOS+" ("
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
    query->bindValue(":cod_area",empleado.getArea().codigo);
    query->bindValue(":cod_clasif",empleado.getClasificacion().codigo);
    query->bindValue(":nivel",empleado.getNivel());
    query->bindValue(":horas",empleado.getHoras());
    query->bindValue(":contrato",empleado.getContrato());
    query->bindValue(":fecha_ingeduc",empleado.getFechaIngrEduc());
    query->bindValue(":fecha_ingeducpriv",empleado.getFechaIngrEducPriv());
    query->bindValue(":fecha_ing",empleado.getFechaIng());
    query->bindValue(":status",empleado.getStatus().codigo);

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
    query->prepare("UPDATE  "+TABLE_EMPLEADOS+" SET "
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
    query->bindValue(":cod_area",empleado.getArea().codigo);
    query->bindValue(":cod_clasif",empleado.getClasificacion().codigo);
    query->bindValue(":nivel",empleado.getNivel());
    query->bindValue(":horas",empleado.getHoras());
    query->bindValue(":contrato",empleado.getContrato());
    query->bindValue(":fecha_ingeduc",empleado.getFechaIngrEduc());
    query->bindValue(":fecha_ingeducpriv",empleado.getFechaIngrEducPriv());
    query->bindValue(":fecha_ing",empleado.getFechaIng());
    query->bindValue(":status",empleado.getStatus().codigo);

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

bool EmpleadoModel::InsertDeducible(QString codDeducible, QString cedulaEmp)
{

}

