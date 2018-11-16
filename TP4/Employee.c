#include "Employee.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validator.h"
#include "array.h"
#include "utn.h"
#define BUFFER 1024

/**
*\brief Funcion que valida campo
*\param char* name campo a validar
*\return [1] si se valido el campo correctamente - [0] ERROR
*/
static int isValidName(char* name)
{
    int retorno = 0;
    int charIngresados = strlen(name);

    if(name != NULL && array_StringCharEsValido(name,charIngresados))
    {
        name[0]=toupper(name[0]);
        retorno = 1;
    }
    return retorno;
}
/**
*\brief Funcion que valida campo
*\param char* horas campo a validar
*\return [1] si se valido el campo correctamente - [0] ERROR
*/
static int isValidHoras(char* horas)
{
    int retorno = 0;
    int charIngresados = strlen(horas);

    if(horas != NULL && array_StringIntEsValido(horas, charIngresados))
    {
        retorno = 1;
    }
    return retorno;
}
/**
*\brief Funcion que valida campo
*\param char* sueldo campo a validar
*\return [1] si se valido el campo correctamente - [0] ERROR
*/
static int isValidSueldo(char* sueldo)
{
    int retorno = 0;
    int charIngresados = strlen(sueldo);

    if(sueldo != NULL && isValidEntero(sueldo,charIngresados))
    {
        retorno = 1;
    }
    return retorno;
}
/**
*\brief Funcion que valida campo
*\param char* id campo a validar
*\return [1] si se valido el campo correctamente - [0] ERROR
*/
static int isValidId(char* id)
{
    int retorno = 0;
    int charIngresados = strlen(id);

    if(id != NULL && isValidEntero(id,charIngresados))
    {
        retorno = 1;
    }
    else
    {
        printf("\nID NO VALIDO");
    }
    return retorno;
}
int employee_filtrarEmpleadosHoras(void* pElemento)
{
    int retorno = -1;
    int auxHoras = 0;
    int filtro = -1;
    //utn_getEntero(&filtro,2,"\nIngrese el numero de horas para hacer el filtro ","ERROR!",0,1000);

    if(pElemento != NULL)
    {
        Employee_getHorasTrabajadas(pElemento,&auxHoras);
        if(auxHoras >= 50)
        {
            retorno = 0;
        }

    }
    return retorno;
}
///--------------------------------------------------------------ORDENAR-----------------------------------------------------------------------------
/**
*\brief Funcion maestra de ordenamiento, ejecuta switch que permite al usuario seleccionar criterio[NOMBRE - SUELDO - ID] y orden [ASCENDENTE - DESCENDENTE]
*\param void* pArrayListEmployee lista de elementos que se va a ordenar
*\return void
*/
void seleccionarCriterioOrdenamiento(void* pArrayListEmployee)
{
    int opcion = 0;
    int orden = -1;
    limpiarPantalla();
    printf("\n******************************\nEL ORDENAMIENTO PUEDE DEMORAR!\n******************************\n");
    utn_getEntero(&opcion,2,"\nSELECCIONE EL CRITERIO DE ORDENAMIENTO\n1. NOMBRE\n2. SUELDO\n3. ID\n4. Volver\n", "\nOPCION INVALIDA\n",1,4);
    if(opcion >= 1 || opcion < 4)
    {
        utn_getEntero(&orden,2,"\nSELECCIONE EL ORDEN \n[1] ASCENDENTE - [0] DESCENDENTE\n", "\nOPCION INVALIDA\n",0,1);

        switch(opcion)
        {
        case 1:
            ll_sort(pArrayListEmployee,Employee_criterioNombre,orden);
            break;
        case 2:
            ll_sort(pArrayListEmployee,Employee_criterioSueldo,orden);
            break;
        case 3:
            ll_sort(pArrayListEmployee,Employee_criterioID,orden);
            break;
        }
    printf("\nORDENAMIENTO FINALIZADO");

    }
}
/**
*\brief Funcion esclava de ordenamiento, compara el campo sueldo
*\param void* thisA elemento A de la estructura que contiene el campo a comparar
*\param void* thisB elemento B de la estructura que contiene el campo a comparar
*\return [1] si thisA->sueldo es mayor a thisB->sueldo
*        [-1] si thisA->sueldo es menor a thisB->sueldo
*        [0] si thisA->sueldo es igual a thisB->sueldo
*/
int Employee_criterioSueldo(void* thisA, void* thisB)
{
    int retorno = 0;
    if(((Employee*)thisA)->sueldo > ((Employee*)thisB)->sueldo)
    {
        retorno = 1;
    }
    if(((Employee*)thisA)->sueldo < ((Employee*)thisB)->sueldo)
    {
        retorno = -1;
    }

    return retorno;
}
/**
*\brief Funcion esclava de ordenamiento, compara el campo sueldo
*\param void* thisA elemento A de la estructura que contiene el campo a comparar
*\param void* thisB elemento B de la estructura que contiene el campo a comparar
*\return [1] si thisA->ID es mayor a thisB->ID
*        [-1] si thisA->ID es menor a thisB->ID
*        [0] si thisA->ID es igual a thisB->ID
*/
int Employee_criterioID(void* thisA, void* thisB)
{
    int retorno = 0;
    if(((Employee*)thisA)->id > ((Employee*)thisB)->id)
    {
        retorno = 1;
    }
    if(((Employee*)thisA)->id < ((Employee*)thisB)->id)
    {
        retorno = -1;
    }

    return retorno;
}
/**
*\brief Funcion esclava de ordenamiento, compara el campo nombre
*\param void* thisA elemento A de la estructura que contiene el campo a comparar
*\param void* thisB elemento B de la estructura que contiene el campo a comparar
*\return [1] si bufferNombreUno es mayor a bufferNombreDos
*        [-1] si bufferNombreUno es menor a bufferNombreDos
*        [0] si bufferNombreUno es igual a bufferNombreDos
*/
int Employee_criterioNombre(void* thisA,void* thisB)
{
    int retorno = 0;
    char bufferNombreUno[BUFFER];
    char bufferNombreDos[BUFFER];

    Employee_getNombre(((Employee*)thisA),bufferNombreUno);
    Employee_getNombre(((Employee*)thisB),bufferNombreDos);

    if(strcmp(bufferNombreUno,bufferNombreDos) < 0)
    {
        retorno = -1;
    }
    else if(strcmp(bufferNombreUno,bufferNombreDos) > 0)
    {

        retorno = 1;
    }
    return retorno;
}

///----------------------------------------------------------------------------------------------------------------------------
/**
*\brief Funcion que muestra todos los campos de una estructura
*\param this es el elemento seleccionado para mostrar
*\return [0]= Mostro el elemento - [-1] ERROR
*/
int employee_mostrar(Employee* this)
{
    int retorno = -1;
    int auxiliarId = 0;
    char auxiliarNombre[BUFFER];
    int auxiliaHorasTrabajadas;
    int auxiliarSueldo;

    if(this != NULL)
    {
        Employee_getId(this,&auxiliarId);
        if(auxiliarId != -1)
        {
            Employee_getNombre(this,auxiliarNombre);
            Employee_getId(this,&auxiliarId);
            Employee_getHorasTrabajadas(this,&auxiliaHorasTrabajadas);
            Employee_getSueldo(this,&auxiliarSueldo);

            retorno = 0;
            printf("ID: %d\nNombre: %s\nHoras trabajadas: %dhs\nSueldo: $%d",auxiliarId,auxiliarNombre,auxiliaHorasTrabajadas,auxiliarSueldo);
        }
    }
    return retorno;
}
/**
*\brief Funcion que reserva espacio dinamicamente para el sizeof de Employee
*\return THIS si se pudo reservar memoria para el empleado
*        NULL si no se pudo reservar memoria
*/
Employee* Employee_new()
{
    Employee* this = NULL;
    this=malloc(sizeof(Employee));
    if(this != NULL)
    {
        return this;
    }
    else
    {
        printf("\nNo hay mas espacio");
    }
    return this;
}
/**
*\brief Se recorre array para encontrar elemento por ID
*\param LinkedList* pArrayListEmployee es la lista que se reccore
*\param int idIngresado es el ID a encontrar
*\return auxiliarEmpleado si encontre el empleado - NULL si no lo encontre
*/
Employee* Employee_getById(LinkedList* pArrayListEmployee,int idIngresado)
{
    Employee* retorno = NULL;
    Employee* auxiliarEmpleado;
    int indice = 0;
    int auxiliarID = 0;

    if(pArrayListEmployee != NULL)
    {
        for(indice=0; indice<ll_len(pArrayListEmployee); indice++)
        {
            auxiliarEmpleado = ll_get(pArrayListEmployee,indice);///En cada iteracion me guardo el empleado completo
            Employee_getId(auxiliarEmpleado,&auxiliarID);///Saco el ID del empleado
            if(auxiliarID == idIngresado) /// Comparo ID's
            {
                retorno = auxiliarEmpleado;
                break;
            }
        }
    }
    return retorno;
}
/**
*\brief Funcion que modifica todos los campos de la estructura, ejecuta switch para que el usuario que campo seleccionar
*       se mantiene en funcionamiento hasta que el usuario agote intentos o seleccione 4 = Regresa al menu principal
*\param LinkedList* pArrayListEmployee es la lista donde se almacenan los empleados
*\return [0]= Exito y [-1]= ERROR
*/
int Employee_editarEmpleado(void* pArrayListEmployee)
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferID[BUFFER];
    int opcion;
    int idIngresado=0;

    if(pArrayListEmployee != NULL )
    {
        ingresoTeclado("\nIngrese el ID a buscar ","ERROR!",bufferID,BUFFER,isValidId,2); ///Pido el ID y valido que sea un ID valido mediante puntero a la funcion Is ValidId
        idIngresado = atoi(bufferID); ///Casteo el ID a int para usar la funcion getById
        limpiarPantalla();
        this = Employee_getById(pArrayListEmployee,idIngresado); ///GGuardo en this el empleado encontrado para editar
        if(this != NULL && ll_contains(pArrayListEmployee, this))
        {
            printf("\nID ENCONTRADO\n");
            do
            {
                limpiarPantalla();
                employee_mostrar(this); ///Muestro el empleado para verificar que sea el hay que modificar
                printf("\n\nSeleccione el campo que desea modificar\n1) Nombre\n2) Horas trabajadas\n3) Sueldo\n4) Volver");
                utn_getEntero(&opcion,3,"\nOpcion: ","\nERROR! Ingrese un numero",1,4);
                retorno = 0;
                switch(opcion)
                {
                case 1 :
                    Employee_modificarEmpleado(this,"\nNOMBRE\n",isValidName,Employee_setNombre);///Pido nombre, valido y seteo en el campo
                    break;
                case 2 :
                    Employee_modificarEmpleado(this,"\nHORAS TRABAJADAS\n",isValidHoras,Employee_setHorasTrabajadas);///Pido horas trabajadas, valido y seteo en el campo
                    break;
                case 3 :
                    Employee_modificarEmpleado(this,"\nSUELDO\n",isValidSueldo,Employee_setSueldo);///Pido sueldo, valido y seteo en el campo
                    break;
                case 4 :
                    break;
                }
            }
            while(opcion != 4);
        }
        else
        {
            printf("\nID NO ENCONTRADO");
        }
    }
    return retorno;
}
/**
*\brief Funcion que modifica los campos de la estructura
*\param Employee* this Es el elemento a modificar
*\param char* mensaje a mostrar al usuario
*\param int (*validacion)(char*) puntero a la funcion que validara el campo
*\param int (*set)(Employee*,char*) puntero a la funcion que setea el campo
*\return [0] = Exito y [-1] ERROR
*/
int Employee_modificarEmpleado(Employee* this, char* mensaje, int (*validacion)(char*),int (*set)(Employee*,char*))
{
    int retorno = -1;
    char opcion[2];
    char buffer[BUFFER];

    if(this != NULL && mensaje != NULL && validacion != NULL && set != NULL)
    {
        ingresoTeclado(mensaje,"\nERROR en ingreso desde teclado",buffer,BUFFER,(*validacion),2);
        array_getLetras(opcion,2,"\nMODIFICAR DATO? S/N\n","\nERROR!",2);
        if(buffer != NULL && !strcasecmp(opcion,"s"))
        {
            (*set)(this,buffer);
            retorno = 0;
        }
        else
        {
            printf("\nNO SE GUARDO LA MODIFICACION");
        }
    }
    return retorno;
}
/**
*\brief Funcion que genera un empleado nuevo dinamicamente y guarda todos sus campos mediante la funcion set_campo
*\param char* idStr ID
*\param char* nombreStr Nombre
*\param char* horasTrabajadasStr Horas Trabajadas
*\param char* sueldoStr Sueldo
*\return THIS para realizar el ll_add y NULL si hubo algun error en las validaciones
*/
Employee* Employee_newConParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* this;
    this=Employee_new();
    if(isValidName(nombreStr) && isValidHoras(horasTrabajadasStr) && isValidSueldo(sueldoStr) && isValidId(idStr))
    {
        Employee_setNombre(this,nombreStr);
        Employee_setId(this,idStr);
        Employee_setHorasTrabajadas(this,horasTrabajadasStr);
        Employee_setSueldo(this,sueldoStr);
        return this;
    }
    else
    {
        printf("\nHubo un error en la carga\n");
        Employee_delete(this);
    }

    return NULL;
}
/**
*\brief Libera espacio en memoria ocupado por elemento
*\param tihs Es el elemento a eliminar
*\return Retorna 0 si logra liberar sino retorna -1
*/
int Employee_delete(Employee* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}
/**
*\brief Funcion que elimina un empleado pero mantiene su puntero a la estructura en un array statico de "arrayElementosBaja"
*\param void* pArrayListEmployee es la lista de elementos de la cual hay que eliminar el elemento indicado
*\return Employee* arrayEmpleadosBaja es el array del tipo elemento donde se van a guardar los punteros eliminados
*/
int employee_eliminarEmpleado(void* pArrayListEmployee,void* listaEmpleadosBaja)
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferId[BUFFER];
    int idIngresado;
    char opcion[2];
    int indice;

    if(!ingresoTeclado("\nINGRESE EL ID DEL EMPLEADO A BORRAR ","\nERROR!",bufferId,BUFFER,isValidId,2))
    {
        idIngresado = atoi(bufferId); ///Casteo el ID a int para usar la funcion getById
        this = Employee_getById(pArrayListEmployee,idIngresado); ///Guardo el empleado completo
        if(this != NULL)///Valido que se haya encontrado un elemento
        {
            employee_mostrar(this); ///Ultima verificacion antes de borrar
            array_getLetras(opcion,2,"\nDesea dar de baja? S/N ","\nError",2);
            if(!strcasecmp("s",opcion))
            {
                indice = ll_indexOf(pArrayListEmployee,this);
                ll_pop(pArrayListEmployee,indice);
                ll_add(listaEmpleadosBaja,this);
                retorno = 0;
            }
        }
        else
        {
            printf("\nEl ID ingresado no existe");
        }
    }
    return retorno;
}
/**
 * \brief Funcion que carga un empleado desde el teclado
 * \param void* pArrayListEmployee es la lista del array donde se va a cargar
 * \param input Array donde se cargará el texto ingresado
 * \return void
 */
int Employee_nuevoEmpleado(void* pArrayListEmployee)
{
    int retorno = -1;
    Employee* this = NULL;
    char bufferNombre[BUFFER];
    char bufferHoras[BUFFER];
    char bufferSueldo[BUFFER];
    char bufferID[BUFFER];
    int auxiliarHoras, auxiliarSueldo = 0;
    int auxiliarID = Employee_getNextID(pArrayListEmployee);
    sprintf(bufferID,"%d",auxiliarID);///Funcion para pasar el ID de int a buffer para el newConParamentros
    printf("ID: %s",bufferID);
    if(
        !array_getNombre(bufferNombre,1024,"\nINGRESE EL NOMBRE DEL EMPLEADO: \n","ERROR! NOMBRE INVALIDO!",2)&&
        !utn_getEntero(&auxiliarHoras,2,"\nINGRESE LAS HORAS TRABAJADAS DEL EMPLEADO: \n","ERROR! NUMERO INVALIDO",1,10000000)&&
        !utn_getEntero(&auxiliarSueldo,2,"\nINGRESE EL SUELDO DEL EMPLEADO: \n","ERROR! NUMERO INVALIDO\n",1,10000000)
    )
    {
        sprintf(bufferHoras,"%d",auxiliarHoras);///Funcion para pasar las horas de int a buffer para el newConParamentros
        sprintf(bufferSueldo,"%d",auxiliarSueldo);///Funcion para pasar el sueldo de int a buffer para el newConParamentros
        this = Employee_newConParametros(bufferID,bufferNombre,bufferHoras,bufferSueldo);
        if(this != NULL)
        {
            retorno = 0;
            ll_add(pArrayListEmployee,this);
        }
        else
        {
            Employee_delete(this);
        }
    }
    return retorno;
}
/**
 * \brief Funcion hecha en clase para encontrar automaticamente el proximo ID, se recorre todo el Linked List
 *        guardando en cada iteracion el ID del empleado, al final del FOR devuelvo ultimo ID + 1
 * \param void* pArrayListEmployee lista a reccorer
 * \return int auxiliarID para asignar - [-1] ERROR
 */
int Employee_getNextID(void* pArrayListEmployee)
{
    Employee* auxiliarEmpleado = NULL;
    int retorno = -1;
    int indice = 0;
    int auxiliarID = 0;

    if(pArrayListEmployee != NULL)
    {
        for(indice=0; indice<ll_len(pArrayListEmployee); indice++) ///Recorro todo el LinkedList
        {
            auxiliarEmpleado = ll_get(pArrayListEmployee,indice);///Obtengo cada empleado
            Employee_getId(auxiliarEmpleado,&auxiliarID);///Obtengo el ID del empleado
        }
        retorno = auxiliarID+1;///Devuelvo el ultimo ID encontrado + 1 para asignarlo al proximo
    }
    return retorno;
}
///--------------------------------------------SETTERS----------------------------------------------------------------------------
/**
 * \brief Funcion que setea el campo ID
 * \param Employee* this Empleado al que se le va a setear el ID
 * \param char* id string del ID a setear, se realiza un atoi antes del seteo
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_setId(Employee* this,char* id)
{
    int retorno = -1;
    static int proximoId= -1;
    int idToInt = 0;
    idToInt=atoi(id); ///Casteo para cumplir con el campo int de la estructura Employee

    if(this!=NULL && idToInt==-1)
    {
        proximoId++;
        this->id=proximoId;
        retorno=0;
    }
    else if(idToInt>proximoId)
    {
        proximoId=idToInt;
        this->id=proximoId;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Funcion que setea el campo nombre
 * \param Employee* this Empleado al que se le va a setear el nombre
 * \param char* nombre string del nombre a setear
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_setNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Funcion que setea el campo horasTrabajadas
 * \param Employee* this Empleado al que se le va a setear el horasTrabajadas
 * \param char* horasTrabajadas string de horasTrabajadas a setear, se realiza un atoi antes del seteo
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_setHorasTrabajadas(Employee* this,char* horasTrabajadas)
{
    int retorno=-1;
    int horasTrabajadasToInt;
    horasTrabajadasToInt = atoi(horasTrabajadas);///Casteo para cumplir con el campo int de la estructura Employee

    if(this!=NULL)
    {
        this->horasTrabajadas=horasTrabajadasToInt;
        retorno=0;
    }
    return retorno;
}

/**
 * \brief Funcion que setea el campo sueldo
 * \param Employee* this Empleado al que se le va a setear el sueldo
 * \param char* sueldo string de sueldo a setear, se realiza un atoi antes del seteo
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_setSueldo(Employee* this,char* sueldo)
{
    int retorno=-1;
    int sueldoToInt=0;
    sueldoToInt=atoi(sueldo);///Casteo para cumplir con el campo int de la estructura Employee

    if(this!=NULL)
    {
        this->sueldo=sueldoToInt;
        retorno=0;
    }
    return retorno;
}
///--------------------------------------------GETTERS----------------------------------------------------------------------------
/**
 * \brief Funcion que lee el campo sueldo
 * \param Employee* this Empleado al que se le va a leer el sueldo
 * \param int* sueldo Puntero auxiliar a int donde se va a almacenar la direccion de memoria del campo sueldo del usuario
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *sueldo=this->sueldo;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Funcion que lee el campo nombre
 * \param Employee* this Empleado al que se le va a leer el nombre
 * \param char* nombre string donde se va a almacenar el campo sueldo del nombre
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_getNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Funcion que lee el campo id
 * \param Employee* this Empleado al que se le va a leer el id
 * \param int* id Puntero auxiliar a int donde se va a almacenar la direccion de memoria del campo id del usuario
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_getId(Employee* this,int* id)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *id=this->id;
        retorno=0;
    }
    return retorno;
}
/**
 * \brief Funcion que lee el campo horasTrabajadas
 * \param Employee* this Empleado al que se le va a leer el horasTrabajadas
 * \param int* horasTrabajadas Puntero auxiliar a int donde se va a almacenar la direccion de memoria del campo horasTrabajadas del usuario
 * \return [0] EXITO - [-1] ERROR
 */
int Employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *horasTrabajadas=this->horasTrabajadas;
        retorno=0;
    }
    return retorno;
}
