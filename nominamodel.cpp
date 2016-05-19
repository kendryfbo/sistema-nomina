#include "nominamodel.h"

const QString TABLE_NOMINAMODEL = "nominamodel";

const QString TABLE_NOMINACARGADA = "nominacargada";
const QString TABLE_NOMINACARGADADETALLE = "nominacargadadetalle";
const QString TABLE_NOMINACARGADADETALLERESUMVIEW = "nominacargadadetalleresumview";
const QString TABLE_NOMINACARGADARESUMVIEW = "nominacargadaresumview";


const QString TABLE_NOMINAPROCESADA = "nominaprocesada";
const QString TABLE_NOMINAPROCESADAEMP = "nominaprocesadaemp";
const QString TABLE_NOMINAPROCESADADETALLERESUMVIEW = "nominaprocesadadetalleresumview";
const QString TABLE_NOMINAPROCESADARESUMVIEW = "nominaprocesadaresumview";

const QString TABLE_DEDUCCIONCARGADA = "deduccioncargada";
const QString TABLE_DEDUCCARGADARESUMVIEW = "deduccargadaresumview";
const QString TABLE_DEDUCCIONEMP = "deduccionemp";
const QString TABLE_DEDUCCIONPROCESADA = "deduccionprocesada";
const QString TABLE_DEDUCPROCESADARESUMVIEW = "deduccionprocesadaresumview";

const QString TABLE_ASIGNACIONCARGADA = "asignacioncargada";
const QString TABLE_ASIGNCARGADARESUMVIEW = "asigncargadaresumview";
const QString TABLE_ASIGNACIONEMP = "asignacionemp";
const QString TABLE_ASIGNACIONPROCESADA = "asignacionprocesada";
const QString TABLE_ASIGNPROCESADARESUMVIEW = "asignacionprocesadaresumview";

NominaModel::NominaModel()
{
    AreaModel areaModel(conexion);
}
NominaModel::NominaModel(QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
    empModel = new EmpleadoModel(conexion);
    deduccModel = new DeduccionModel(conexion);
    asignacModel = new AsignacionModel(conexion);

}
NominaModel::NominaModel(QString connName, QString hostName, QString dbName, QString dbUserName, QString dbUserPassword, int dbPort)
{
    conexion = connDB( connName,hostName, dbName, dbUserName, dbUserPassword, dbPort);
    connect();
    query = new QSqlQuery(conexion.db);
    empModel = new EmpleadoModel(conexion);
    deduccModel = new DeduccionModel(conexion);
    asignacModel = new AsignacionModel(conexion);
}

NominaModel::~NominaModel()
{
    delete empModel;
    delete deduccModel;
    delete asignacModel;
    delete query;
}

bool NominaModel::insertModeloNomina(QString codigo, QString descripcion, int dias, double porcSueldo, double porcDeduccion, double porcAsignacion)
{
    query->prepare("INSERT INTO "+TABLE_NOMINAMODEL+" ("
                                                    "codigo,descripcion,dias,sueldo_porc,deducc_porc,asignac_porc) VALUES ("
                                                    ":codigo,:descripcion,:dias,:sueldo_porc,:deducc_porc,:asignac_porc)");

    query->bindValue(":codigo",codigo);
    query->bindValue(":descripcion",descripcion);
    query->bindValue(":dias",dias);
    query->bindValue(":sueldo_porc",porcSueldo);
    query->bindValue(":deducc_porc",porcDeduccion);
    query->bindValue(":asignac_porc",porcAsignacion);

    if (!query->exec())
    {
        status = "ERROR al Insertar Modelo de Nomina: " + query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        status = "Modelo de Nomina Insertado Exitosamente...";
        debugMessage(status);
        return true;
    }
}
bool NominaModel::updateModeloNomina(QString codigo, QString descripcion, int dias, double porcSueldo, double porcDeduccion, double porcAsignacion)
{
    query->prepare("UPDATE "+TABLE_NOMINAMODEL+" SET "
                                               "descripcion=:descripcion,dias=:dias,sueldo_porc=:sueldo_porc,"
                                               "deducc_porc=:deducc_porc,asignac_porc=:asignac_porc "
                                               "WHERE codigo=:codigo");

    query->bindValue(":codigo",codigo);
    query->bindValue(":descripcion",descripcion);
    query->bindValue(":dias",dias);
    query->bindValue(":sueldo_porc",porcSueldo);
    query->bindValue(":deducc_porc",porcDeduccion);
    query->bindValue(":asignac_porc",porcAsignacion);

    if (!query->exec())
    {
        status = "ERROR al Actualizar Modelo de Nomina: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->lastError().text());
        debugMessage(query->lastQuery());
        return false;
    } else {
        status = "Modelo de Nomina Actualizado Exitosamente...";
        debugMessage(status);
        return true;
    }
}
bool NominaModel::deleteModeloNomina(QString codigo)
{
    query->prepare("DELETE FROM "+TABLE_NOMINAMODEL+" WHERE codigo='"+codigo+"'");

    if (!query->exec())
    {
        status = "ERROR al Eliminar Modelo de Nomina: " + query->lastError().text();
        debugMessage(status);
        return false;
    } else {
        status = "Modelo de Nomina Eliminado Exitosamente...";
        debugMessage(status);

        return true;
    }
}

bool NominaModel::nominaModelExist(QString codigo)
{
    query->prepare("SELECT * FROM nominamodel where codigo=:codigo");
    query->bindValue(":codigo",codigo);
    if (!query->exec())
    {
        status = "ERROR al Buscar Si existe Modelo de Nomina: " + query->lastError().text();
        debugMessage(status);
        return false;
    } else if (!query->next())
    {
        status = "Modelo de Nomina No encontrado.";
        debugMessage(status);
        return false;
    }else
    {
        status = "Modelo de Nomina Encontrado...";
        debugMessage(status);
        return true;
    }
}

QSqlQuery NominaModel::findNominaModel(QString codigo)
{
    query->prepare("SELECT * FROM nominamodel where codigo=:codigo");
    query->bindValue(":codigo",codigo);
    if (!query->exec())
    {
        status = "ERROR al Buscar Modelo de Nomina: " + query->lastError().text();
        debugMessage(status);
    } else if (!query->next())
    {
        status = "Modelo de Nomina No encontrado.";
        debugMessage(status);
    }else
    {
        status = "Modelo de Nomina Encontrado...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery NominaModel::findNominasModel(QString descripcion)
{
    descripcion = "%"+descripcion+"%";
    query->prepare("SELECT codigo,descripcion FROM nominamodel where descripcion LIKE(:descripcion)");
    query->bindValue(":descripcion",descripcion);

    if (!query->exec())
    {
        status = "ERROR al Buscar Modelos de Nomina: " + query->lastError().text();
        debugMessage(status);
    } else {
        status = "Modelos de Nomina Encontrados.";
        debugMessage(status);
    }
    query->executedQuery();
    return *query;
}

Nomina NominaModel::findNominaCargada(int numero)
{
    Nomina nomina;

    query->prepare("SELECT * FROM "+TABLE_NOMINACARGADA+" WHERE numero=:numero");
    query->bindValue(":numero",numero);

    if (!query->exec())
    {
        status = "ERROR Buscar Nomina Cargada: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->lastQuery());
    } else if (!query->next())
    {
        status = "Nomina Cargada no Existe.";
        debugMessage(status);
    } else
    {
        nomina = Nomina(
                    query->value("numero").toInt(),
                    query->value("descripcion").toString(),
                    query->value("dias").toInt(),
                    query->value("porc_salario").toDouble(),
                    query->value("porc_deduccion").toDouble(),
                    query->value("porc_asignacion").toDouble(),
                    query->value("fecha_pago").toString(),
                    query->value("fecha_desde").toString(),
                    query->value("fecha_hasta").toString(),
                    query->value("cod_usuario").toString(),
                    query->value("fecha_creac").toString()
                    );
        status = "Nomina Cargada Encontrada....";
        debugMessage(status);
    }

    return nomina;
}

QSqlQuery NominaModel::findNominasCargadas()
{
    query->prepare("SELECT * FROM "+TABLE_NOMINACARGADARESUMVIEW);

    if (!query->exec())
    {
        status = "ERROR al buscar Nominas Cargadas: " + query->lastError().text();
        debugMessage(status);
    }else
    {
        status = "Nominas Cargadas Buscadas Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

bool NominaModel::nominaExiste(int numero)
{
    Nomina nomina;

    nomina = findNominaCargada(numero);

    if (nomina.getNumero() == numero)
    {
        status = "Nomina Encontrada...";
        debugMessage(status);
        return true;
    }else{
        status = "Nomina no Encontrada.";
        debugMessage(status);
        return false;
    }

}

QSqlQuery NominaModel::findEmpleadosFromNominaCargada(int numero, QString str, CampoEmp campo)
{
    QString sql = "";

    sql = "SELECT * FROM "+TABLE_NOMINACARGADADETALLERESUMVIEW+" WHERE numero=:numero ";

    if (campo == CampoEmp::cedula)
        sql = sql + "AND cedula LIKE('%"+str+"%')";
    else if (campo == CampoEmp::nombres)
        sql = sql + "AND nombres LIKE('%"+str+"%')";
    else if (campo == CampoEmp::apellidos)
        sql = sql + "AND apellidos LIKE('%"+str+"%')";

    query->prepare(sql);
    query->bindValue(":numero",numero);

    if (!query->exec())
    {
        status = "ERROR al buscar Empleados en Nomina Numero: "+QString::number(numero)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Empleados en Nomina Numero: "+QString::number(numero)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery NominaModel::findAsignNomCargadaFromEmp(int nominaNum, QString cedula)
{
    QString sql = "";

    sql = "SELECT codigo,descripcion,cantidad,valor,total FROM "+TABLE_ASIGNCARGADARESUMVIEW+" WHERE numero=:numero AND cedula=:cedula ";

    query->prepare(sql);
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cedula",cedula);

    if (!query->exec())
    {
        status = "ERROR al buscar Asignaciónes de Empleado cedula: "+cedula+" en Nomina Numero: "+QString::number(nominaNum)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Asignaciónes de Empleado cedula: "+cedula+" en Nomina Numero: "+QString::number(nominaNum)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery NominaModel::findDeduccNomCargadasFromEmp(int nominaNum, QString cedula)
{
    QString sql = "";

    sql = "SELECT codigo,descripcion,cantidad,valor,total FROM "+TABLE_DEDUCCARGADARESUMVIEW+" WHERE numero=:numero AND cedula=:cedula ";

    query->prepare(sql);
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cedula",cedula);

    if (!query->exec())
    {
        status = "ERROR al buscar Deducciónes de Empleado cedula: "+cedula+" en Nomina Numero: "+QString::number(nominaNum)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Deducciónes de Empleado cedula: "+cedula+" en Nomina Numero: "+QString::number(nominaNum)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

bool NominaModel::procesarNomina(int nominaNum)
{
    startTransaction();

    if (!insertNominaProcesada(nominaNum))
    {
        status = "ERROR al Procesar Nomina: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }
    else if (!insertDeduccionesProcesadas(nominaNum))
    {
        status = "ERROR al Procesar Nomina: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }
    else if (!insertAsignacionesProcesadas(nominaNum))
    {
        status = "ERROR al Procesar Nomina: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }
    else if (!insertNominaProcesadaEmp(nominaNum))
    {
        status = "ERROR al Procesar Nomina: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }
    else if (!deleteNominaCargada(nominaNum))
    {
            status = "ERROR al Procesar Nomina: " + status;
            debugMessage(status);
            rollBack();
            return false;
    } else {
        status = "Nomina Procesada Exitosamente....";
        debugMessage(status);
        Commit();
        return true;
    }
}

QSqlQuery NominaModel::findNominasProcesadas()
{
    query->prepare("SELECT * FROM "+TABLE_NOMINAPROCESADARESUMVIEW);

    if (!query->exec())
    {
        status = "ERROR al buscar Nominas Procesadas: " + query->lastError().text();
        debugMessage(status);
    }else
    {
        status = "Nominas Procesadas Buscadas Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

Nomina NominaModel::findNominaProcesada(int numero)
{
    Nomina nomina;

    query->prepare("SELECT * FROM "+TABLE_NOMINAPROCESADA+" WHERE numero=:numero");
    query->bindValue(":numero",numero);

    if (!query->exec())
    {
        status = "ERROR Buscar Nomina Procesada: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->lastQuery());
    } else if (!query->next())
    {
        status = "Nomina Procesada no Existe.";
        debugMessage(status);
    } else
    {
        nomina = Nomina(
                    query->value("numero").toInt(),
                    query->value("descripcion").toString(),
                    query->value("dias").toInt(),
                    query->value("porc_salario").toDouble(),
                    query->value("porc_deduccion").toDouble(),
                    query->value("porc_asignacion").toDouble(),
                    query->value("fecha_pago").toString(),
                    query->value("fecha_desde").toString(),
                    query->value("fecha_hasta").toString(),
                    query->value("cod_usuario").toString(),
                    query->value("fecha_creac").toString()
                    );
        status = "Nomina Procesada Encontrada....";
        debugMessage(status);
    }

    return nomina;
}

bool NominaModel::nominaProcesadaExiste(int numero)
{
    Nomina nomina;

    nomina = findNominaProcesada(numero);

    if (nomina.getNumero() == numero)
    {
        status = "Nomina Encontrada...";
        debugMessage(status);
        return true;
    }else{
        status = "Nomina no Encontrada.";
        debugMessage(status);
        return false;
    }
}

QSqlQuery NominaModel::findEmpleadosFromNominaProcesada(int numero, QString str, NominaModel::CampoEmp campo)
{
    QString sql = "";

    sql = "SELECT * FROM "+TABLE_NOMINAPROCESADADETALLERESUMVIEW+" WHERE numero=:numero ";

    if (campo == CampoEmp::cedula)
        sql = sql + "AND cedula LIKE('%"+str+"%')";
    else if (campo == CampoEmp::nombres)
        sql = sql + "AND nombres LIKE('%"+str+"%')";
    else if (campo == CampoEmp::apellidos)
        sql = sql + "AND apellidos LIKE('%"+str+"%')";

    query->prepare(sql);
    query->bindValue(":numero",numero);

    if (!query->exec())
    {
        status = "ERROR al buscar Empleados en Nomina Procesada Numero: "+QString::number(numero)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Empleados en Nomina Procesada Numero: "+QString::number(numero)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery NominaModel::findAsignNomProcesadaFromEmp(int nominaNum, QString cedula)
{
    QString sql = "";

    sql = "SELECT codigo,descripcion,cantidad,valor,total FROM "+TABLE_ASIGNPROCESADARESUMVIEW+" WHERE numero=:numero AND cedula=:cedula ";

    query->prepare(sql);
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cedula",cedula);

    if (!query->exec())
    {
        status = "ERROR al buscar Asignaciónes de Empleado cedula: "+cedula+" en Nomina Procesada Numero: "+QString::number(nominaNum)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Asignaciónes de Empleado cedula: "+cedula+" en Nomina Procesada Numero: "+QString::number(nominaNum)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

QSqlQuery NominaModel::findDeduccNomProcesadaCargadasFromEmp(int nominaNum, QString cedula)
{
    QString sql = "";

    sql = "SELECT codigo,descripcion,cantidad,valor,total FROM "+TABLE_DEDUCPROCESADARESUMVIEW+" WHERE numero=:numero AND cedula=:cedula ";

    query->prepare(sql);
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cedula",cedula);

    if (!query->exec())
    {
        status = "ERROR al buscar Deducciónes de Empleado cedula: "+cedula+" en Nomina Procesada Numero: "+QString::number(nominaNum)+",  Error:"+ query->lastError().text();
        debugMessage(status);
    } else {
        status = "Busqueda de Deducciónes de Empleado cedula: "+cedula+" en Nomina Procesada Numero: "+QString::number(nominaNum)+" realizada Exitosamente...";
        debugMessage(status);
    }
    return *query;
}

bool NominaModel::cargarNominaEmpleado(Empleado empleado, Nomina nomina)
{
    startTransaction();

    query->exec("SELECT MAX(numero) FROM "+TABLE_NOMINACARGADA+" FOR UPDATE");
    query->next();
    int nominaNum = query->value(0).toInt() + 1;

    if (!insertNominaCargada(nomina,nominaNum))
    {
        status = "ERROR al cargar nomina Empleado: \n" + status;
        debugMessage(status);
        rollBack();
        return false;
    }

    nomina = findNominaCargada(nominaNum);

    if (!insertDeduccionesCargadas(nomina,empleado))
    {
        status = "ERROR al cargar nomina Empleado: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }

    if (!insertNominaCargadaDetalle(nomina,empleado))
    {
        status = "ERROR al cargar nomina Empleado: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }

    status = "Nomina Empleado Cargada Exitosamente...";
    debugMessage(status);
    Commit();
    return true;
}

bool NominaModel::cargarNominaArea(QString area, Nomina nomina)
{

    QList<QString> cedulasEmpelados;

    startTransaction();

    query->exec("SELECT MAX(numero) FROM "+TABLE_NOMINACARGADA+" FOR UPDATE");
    query->next();
    int nominaNum = query->value(0).toInt() + 1;

    if (!insertNominaCargada(nomina,nominaNum))
    {
        status = "ERROR al cargar nomina Area: " + status;
        debugMessage(status);
        rollBack();
        return false;
    }

    nomina = findNominaCargada(nominaNum);


    query->prepare("SELECT * FROM empleado WHERE cod_area=:area");
    query->bindValue(":area",area);

    if (!query->exec())
    {
        status = "ERROR al Buscar empleados por Area: " + query->lastError().text();
        debugMessage(status);
        return false;
    } else if (query->size()>0){
        while (query->next())
        {
            cedulasEmpelados << query->value("cedula").toString();
        }

        for (int i=0; i < cedulasEmpelados.size(); i++)
        {
            Empleado empleado = empModel->findEmpleado(cedulasEmpelados.at(i));

            if (!insertDeduccionesCargadas(nomina,empleado))
            {
                status = "ERROR al cargar nomina Empleado: " + status;
                debugMessage(status);
                rollBack();
                return false;
            }

            if (!insertAsignacionesCargadas(nomina,empleado))
            {
                status = "ERROR al cargar nomina Empleado: " + status;
                debugMessage(status);
                rollBack();
                return false;
            }

            if (!insertNominaCargadaDetalle(nomina,empleado))
            {
                status = "ERROR al cargar nomina Empleado: " + status;
                debugMessage(status);
                rollBack();
                return false;
            }
        }
    } else {
        status = "NOMINA NO CARGADA: Área Seleccionada No posee Empleados Asignados.";
        debugMessage(status);
        rollBack();
        return false;
    }

    status = "Nomina por Área Cargada Exitosamente...";
    debugMessage(status);
    Commit();
    return true;


}

bool NominaModel::deleteNominaCargada(int numero)
{
    query->prepare("DELETE FROM nominacargada WHERE numero=:numero");
    query->bindValue(":numero",numero);

    if (!query->exec())
    {
        status = "ERROR al eliminar Nomina Cargada numero "+QString::number(numero)+" Error: "+query->lastError().text();
        debugMessage(status);
        return false;
    }
    status = "Nomina Cargada Numero: "+QString::number(numero)+" Eliminada Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertNominaCargada(Nomina &nomina, int numero)
{
    query->prepare("INSERT INTO "+TABLE_NOMINACARGADA+" ("
                                                      "numero,descripcion,dias,porc_salario,porc_deduccion,porc_asignacion,fecha_pago,fecha_desde,fecha_hasta,cod_usuario,fecha_creac)"
                                                      " VALUES ("
                                                      ":numero,:descripcion,:dias,:porc_salario,:porc_deduccion,:porc_asignacion,:fecha_pago,:fecha_desde,:fecha_hasta,:cod_usuario,CURDATE())");

    query->bindValue(":numero",numero);
    query->bindValue(":descripcion",nomina.getDescripcion());
    query->bindValue(":dias",nomina.getDias());
    query->bindValue(":porc_salario",nomina.getSalario());
    query->bindValue(":porc_deduccion",nomina.getDeduccion());
    query->bindValue(":porc_asignacion",nomina.getAsignacion());
    query->bindValue(":fecha_pago",nomina.getFechaPago());
    query->bindValue(":fecha_desde",nomina.getFechaDesde());
    query->bindValue(":fecha_hasta",nomina.getFechaHasta());
    query->bindValue(":cod_usuario","TESTC");

    if (!query->exec())
    {
        status = "ERROR al Insertar Nomina Cargada: " + query->lastError().text();
        debugMessage(status);
        return false;
    }
    status = "Nomina Cargada Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertNominaCargadaDetalle(Nomina &nomina, Empleado &empleado)
{
    query->prepare("INSERT INTO "+TABLE_NOMINACARGADADETALLE+" ("
                                                             "numero,ced_emp,salario) VALUES ("
                                                             ":numero,:ced_emp,:salario)");

    int salario = empleado.getSalarioDia() * nomina.getDias();

    query->bindValue(":numero",nomina.getNumero());
    query->bindValue(":ced_emp",empleado.getCedula());
    query->bindValue(":salario",salario);

    if (!query->exec())
    {
        status = "ERROR al Insertar Nomina Cargada Detalle: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->lastQuery());
        return false;
    }
    status = "Nomina Cargada Detalle Insertada Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertDeduccionesCargadas(Nomina &nomina, Empleado &empleado)
{
   QSqlQuery queryTemp = empModel->findDeducciones(empleado.getCedula());

   while (queryTemp.next())
   {
       QString codigoDeduccion = queryTemp.value("cod_deduccion").toString();
       int cantidad = queryTemp.value("cantidad").toInt();

       Deduccion deduccion(deduccModel->findDeduccion(codigoDeduccion));
       if (!insertDeduccionCargada(deduccion,empleado,nomina.getNumero(),nomina.getDeduccion(),cantidad))
       {
           status = "ERROR al Insertar Deducciónes Cargadas: " + status;
           debugMessage(status);
           return false;
           break;
       }
   }
   return true;
}

bool NominaModel::insertDeduccionCargada(Deduccion &deduccion,Empleado &empleado, int nominaNum, double porcentaje, int cantidad)
{
    QString forma = deduccion.getForma();
    double valor = 0;

    if (forma == "VALOR")
    {
         valor = deduccion.getValor();
    }
    else  if (forma == "HORA")
    {
        if (empleado.getClasificacion().getFormaPago() == "HORA")
        {
            valor = empleado.getSalarioHora();
        }
    }
    else  if (forma == "DIA")
    {
        valor = empleado.getSalarioDia();
    }
    else  if (forma == "SEMANA")
    {
        valor = empleado.getSalarioSemana();
    }
    else  if (forma == "MES")
    {
        valor = empleado.getSalarioMes();
    }
    else  if (forma == "FORMULA")
    {
        // UBICAR LISTA DE FORMULAS Y DEVOLVER VALOR
        if ("S.S.O"){

        }
    }

    valor = valor * (porcentaje/100);

    query->prepare("INSERT INTO "+TABLE_DEDUCCIONCARGADA+" ("
                                   "numero,cod_deduc,ced_emp,descripcion,cantidad,valor) VALUES ("
                                                         ":numero,:cod_deduc,:ced_emp,:descripcion,:cantidad,:valor)");
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cod_deduc",deduccion.getCodigo());
    query->bindValue(":ced_emp",empleado.getCedula());
    query->bindValue(":descripcion",deduccion.getDescripcion());
    query->bindValue(":cantidad",cantidad);
    query->bindValue(":valor",valor);

    if (!query->exec())
    {
        debugMessage(query->lastQuery());
        status = "ERROR al insertar Deducción Cargada: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else
    {
        status = "Deducción Cargada insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool NominaModel::insertAsignacionesCargadas(Nomina &nomina, Empleado &empleado)
{
    QSqlQuery queryTemp = empModel->findAsignaciones(empleado.getCedula());

    while (queryTemp.next())
    {
        QString codigoAsignacion = queryTemp.value("cod_asignacion").toString();
        int cantidad = queryTemp.value("cantidad").toInt();

        Asignacion asignacion(asignacModel->findAsignacion(codigoAsignacion));
        if (!insertAsignacionCargada(asignacion,empleado,nomina.getNumero(),nomina.getAsignacion(),cantidad))
        {
            status = "ERROR al Insertar Asignaciónes Cargadas: " + status;
            debugMessage(status);
            return false;
            break;
        }
    }
    return true;
}

bool NominaModel::insertAsignacionCargada(Asignacion &asignacion, Empleado &empleado, int nominaNum, double porcentaje, int cantidad)
{
    QString forma = asignacion.getForma();
    double valor = 0;

    if (forma == "VALOR")
    {
         valor = asignacion.getValor();
    }
    else  if (forma == "HORA")
    {
        if (empleado.getClasificacion().getFormaPago() == "HORA")
        {
            valor = empleado.getSalarioHora();
        }
    }
    else  if (forma == "DIA")
    {
        valor = empleado.getSalarioDia();
    }
    else  if (forma == "SEMANA")
    {
        valor = empleado.getSalarioSemana();
    }
    else  if (forma == "MES")
    {
        valor = empleado.getSalarioMes();
    }
    else  if (forma == "FORMULA")
    {
        // UBICAR LISTA DE FORMULAS Y DEVOLVER VALOR
    }

    valor = valor * (porcentaje/100);

    query->prepare("INSERT INTO "+TABLE_ASIGNACIONCARGADA+" ("
                                   "numero,cod_asign,ced_emp,descripcion,cantidad,valor) VALUES ("
                                                         ":numero,:cod_asign,:ced_emp,:descripcion,:cantidad,:valor)");
    query->bindValue(":numero",nominaNum);
    query->bindValue(":cod_asign",asignacion.getCodigo());
    query->bindValue(":ced_emp",empleado.getCedula());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":cantidad",cantidad);
    query->bindValue(":valor",valor);

    if (!query->exec())
    {
        debugMessage(query->lastQuery());
        status = "ERROR al insertar Asignación Cargada: " + query->lastError().text();
        debugMessage(status);
        return false;
    }else
    {
        status = "Asignación Cargada insertada Exitosamente...";
        debugMessage(status);
        return true;
    }
}

bool NominaModel::insertNominaProcesada(int numero)
{
    Nomina nomina = findNominaCargada(numero);

    query->prepare("INSERT INTO "+TABLE_NOMINAPROCESADA+" ("
                                                      "numero,descripcion,dias,porc_salario,porc_deduccion,porc_asignacion,fecha_pago,fecha_desde,fecha_hasta,cod_usuario,fecha_creac)"
                                                      " VALUES ("
                                                      ":numero,:descripcion,:dias,:porc_salario,:porc_deduccion,:porc_asignacion,:fecha_pago,:fecha_desde,:fecha_hasta,:cod_usuario,CURDATE())");

    query->bindValue(":numero",numero);
    query->bindValue(":descripcion",nomina.getDescripcion());
    query->bindValue(":dias",nomina.getDias());
    query->bindValue(":porc_salario",nomina.getSalario());
    query->bindValue(":porc_deduccion",nomina.getDeduccion());
    query->bindValue(":porc_asignacion",nomina.getAsignacion());
    query->bindValue(":fecha_pago",nomina.getFechaPago());
    query->bindValue(":fecha_desde",nomina.getFechaDesde());
    query->bindValue(":fecha_hasta",nomina.getFechaHasta());
    query->bindValue(":cod_usuario","TESTP");

    if (!query->exec())
    {
        status = "ERROR al Insertar Nomina Procesada: " + query->lastError().text();
        debugMessage(status);
        return false;
    }
    status = "Nomina Procesada Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertNominaProcesadaEmp(int numero)
{
    QSqlQuery thisQuery =  findEmpleadosFromNominaCargada(numero);

    while (thisQuery.next())
    {
        query->prepare("INSERT INTO "+TABLE_NOMINAPROCESADAEMP+" ("
                                                                 "numero,ced_emp,salario) VALUES ("
                                                                 ":numero,:ced_emp,:salario)");

        query->bindValue(":numero",numero);
        query->bindValue(":ced_emp",thisQuery.value("cedula").toString());
        query->bindValue(":salario",thisQuery.value("salario").toString());

        if (!query->exec())
        {
            status = "ERROR al Insertar Datos Empleado en Nomina Procesada: " + query->lastError().text();
            debugMessage(status);
            return false;
        }

    }
    status = "Empleados en Nomina Procesada insertados Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertDeduccionesProcesadas(int numero)
{
    QSqlQuery thisQuery =  *query;

    thisQuery.prepare("SELECT * FROM "+TABLE_DEDUCCIONCARGADA+" WHERE numero=:numero");
    thisQuery.bindValue(":numero",numero);

    if (!thisQuery.exec())
    {
        status = "ERROR al Buscar Deducciones Cargadas en Nomina Procesada: " + thisQuery.lastError().text();
        debugMessage(status);
        return false;
    }
    while (thisQuery.next())
    {   
        query->prepare("INSERT INTO "+TABLE_DEDUCCIONPROCESADA+" ("
                                           "numero,cod_deduc,ced_emp,descripcion,cantidad,valor) VALUES ("
                                                                 ":numero,:cod_deduc,:ced_emp,:descripcion,:cantidad,:valor)");

        query->bindValue(":numero",thisQuery.value("numero").toString());
        query->bindValue(":cod_deduc",thisQuery.value("cod_deduc").toString());
        query->bindValue(":ced_emp",thisQuery.value("ced_emp").toString());
        query->bindValue(":descripcion",thisQuery.value("descripcion").toString());
        query->bindValue(":cantidad",thisQuery.value("cantidad").toString());
        query->bindValue(":valor",thisQuery.value("valor").toString());


        if (!query->exec())
        {
            status = "ERROR al insertar Deducción Procesada: " + query->lastError().text();
            debugMessage(status);
            return false;
            }
    }

    status = "Deducciónes en Nomina Procesada insertados Exitosamente...";
    debugMessage(status);
    return true;
}

bool NominaModel::insertAsignacionesProcesadas(int numero)
{
    QSqlQuery thisQuery =  *query;

    thisQuery.prepare("SELECT * FROM "+TABLE_ASIGNACIONCARGADA+" WHERE numero=:numero");
    thisQuery.bindValue(":numero",numero);

    if (!thisQuery.exec())
    {
        status = "ERROR al Buscar Asignaciónes Cargadas en Nomina Procesada: " + thisQuery.lastError().text();
        debugMessage(status);
        return false;
    }
    while (thisQuery.next())
    {
        query->prepare("INSERT INTO "+TABLE_ASIGNACIONPROCESADA+" ("
                                           "numero,cod_asign,ced_emp,descripcion,cantidad,valor) VALUES ("
                                                                 ":numero,:cod_asign,:ced_emp,:descripcion,:cantidad,:valor)");

        query->bindValue(":numero",thisQuery.value("numero").toString());
        query->bindValue(":cod_asign",thisQuery.value("cod_asign").toString());
        query->bindValue(":ced_emp",thisQuery.value("ced_emp").toString());
        query->bindValue(":descripcion",thisQuery.value("descripcion").toString());
        query->bindValue(":cantidad",thisQuery.value("cantidad").toString());
        query->bindValue(":valor",thisQuery.value("valor").toString());


        if (!query->exec())
        {
            status = "ERROR al insertar Asignación Procesada: " + query->lastError().text();
            debugMessage(status);
            return false;
            }
    }

    status = "Asignaciónes en Nomina Procesada insertadas Exitosamente...";
    debugMessage(status);
    return true;
}

