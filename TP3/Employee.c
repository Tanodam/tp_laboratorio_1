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

///-------------------------------------------------------------------------------------------------------------------------------------------

int Employee_criterio(void* elementoUno, void* elementoDos)
{
    int retorno = 0;
    if(elementoUno != NULL && elementoDos != NULL)
    {
        Employee* empleadoUno=(Employee*)elementoUno;
        Employee* empleadoDos=(Employee*)elementoDos;
        retorno = strcmp(empleadoUno->nombre, empleadoDos->nombre);
    }

    return retorno;
}


/**
*\brief Funcion que muestra todos los campos de una estructura
*\param this es el elemento seleccionado para mostrar
*\param thisB Es el segundo elemento
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
Employee* Employee_new()
{
    Employee* this;
    this=malloc(sizeof(Employee));
    return this;
}
/**
*\brief Se recorre array para encontrar elemento por ID
*\param pArray Es el array para recorrer
*\param idIngresado Es ID para encontrar
*\return Retorna el elemento sino retorna NULL
*/
Employee* Employee_getById(LinkedList* pArrayListEmployee,int idIngresado)
{
    Employee* retorno = NULL;
    int index;
    Employee* auxEmployee;
    int auxID;

    if(pArrayListEmployee != NULL)
    {
        for(index=0; index<ll_len(pArrayListEmployee); index++) //Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            Employee_getId(auxEmployee,&auxID);//Obtengo el ID del elemento
            if(auxID == idIngresado)
            {
                retorno = auxEmployee;
                break;
            }
        }
    }
    return retorno;
}

int Employee_editarEmpleado(void* pArrayListEmployee)
{
    Employee* this = NULL;
    int retorno = -1;
    char bufferID[BUFFER];
    int opcion;
    int idIngresado=0;

    if(pArrayListEmployee != NULL )
    {
        ingresoTeclado("\nIngrese el ID a buscar ","ERROR!",bufferID,BUFFER,isValidId,2);
        idIngresado = atoi(bufferID);
        limpiarPantalla();
        this = Employee_getById(pArrayListEmployee,idIngresado);
        if(this != NULL)
        {
            do
            {
                retorno = 0;
                employee_mostrar(this);
                printf("\nSeleccione el campo que desea modificar\n1) Nombre\n2) Sueldo\n3) Horas trabajadas\n4) Volver");
                utn_getEntero(&opcion,2,"\nOpcion: ","\nERROR! Ingrese un numero",1,4);
                switch(opcion)
                {
                case 1 :
                    Employee_modificarEmpleado(this,"\nNOMBRE\n",isValidName,Employee_setNombre);
                    break;
                case 2 :
                    Employee_modificarEmpleado(this,"\nSUELDO\n",isValidSueldo,Employee_setSueldo);
                    break;
                case 3 :
                    Employee_modificarEmpleado(this,"\nHORAS TRABAJADAS\n",isValidHoras,Employee_setHorasTrabajadas);
                    break;
                case 4 :
                    break;
                }
            }
            while(opcion != 4);
        }
        else
        {
            printf("\nID no encontrado");
        }
    }
    return retorno;
}
Employee* Employee_newConParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* this;
    this=Employee_new();
    if(isValidName(nombreStr) && isValidHoras(horasTrabajadasStr))
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
*\param tihs Es el elemento
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
*\brief Se modifica un campo del elemento
*\param this Es el elemento a modificar
*\param validacion Es el puntero a la funcion de validacion
*\param set Es el puntero a la funcion set del campo
*\return Retorna 0 si logra modificar campo sino retorna -1
*/
int Employee_modificarEmpleado(Employee* this, char* mensaje, int (*validacion)(char*),int (*set)(Employee*,char*))
{
    int retorno = -1;
    char option[2];
    char buffer[BUFFER];

    if(this != NULL && mensaje != NULL && validacion != NULL && set != NULL)
    {
        ingresoTeclado(mensaje,"\nERROR en ingreso desde teclado",buffer,BUFFER,(*validacion),2);
        array_getLetras(option,2,"\nDesea modificar dato? S/N\n","\nERROR!",2);
        if(buffer != NULL && !strcasecmp("s",option))
        {
            (*set)(this,buffer);
            employee_mostrar(this);
            retorno = 0;
        }
    }
    else
    {
        printf("\nError");
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
        idIngresado = atoi(bufferId);
        this = Employee_getById(pArrayListEmployee,idIngresado);
        if(this != NULL)
        {
            employee_mostrar(this);
            array_getLetras(opcion,2,"\nDesea dar de baja? S/N","\nError",2);
            if(!strcasecmp("s",opcion))
            {
                indice = ll_indexOf(pArrayListEmployee,this);
                ll_add(listaEmpleadosBaja,ll_pop(pArrayListEmployee,indice));
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
    int auxiliarID = Employee_getNextID(pArrayListEmployee);
    sprintf(bufferID,"%d",auxiliarID);///Funcion para pasar el ID de int a buffer para el newConParamentros
    printf("ID: %s",bufferID);
    if(
        !array_getNombre(bufferNombre,1024,"\nINGRESE EL NOMBRE DEL EMPLEADO: \n","ERROR! Nombre invalido!",2)&&
        !array_getStringInt(bufferHoras,1024,"\nINGRESE LAS HORAS TRABAJADAS DEL EMPLEADO: \n","ERROR! Numero invalido",2)&&
        !array_getStringInt(bufferSueldo,1024,"\nINGRESE EL SUELDO DEL EMPLEADO: \n","ERROR! Numero invalido\n",2)
    )
    {
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

int Employee_getNextID(void* pArrayListEmployee)
{
    int retorno=-1;
    int index;
    Employee* auxEmployee;
    int auxID;

    if(pArrayListEmployee != NULL)
    {
        for(index=0; index<ll_len(pArrayListEmployee); index++) //Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            Employee_getId(auxEmployee,&auxID);//Obtengo el ID del elemento
        }
        retorno = auxID+1;//Retorno el ID del ultimo elemento más uno
    }
    return retorno;
}

int Employee_setId(Employee* this,char* id)
{
    int retorno=-1;
    static int proximoId=-1;
    int idToInt=0;
    idToInt=atoi(id);

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

int Employee_setHorasTrabajadas(Employee* this,char* horasTrabajadas)
{
    int retorno=-1;
    int horasTrabajadasToInt;
    if(this!=NULL)
    {
        horasTrabajadasToInt = atoi(horasTrabajadas);
        this->horasTrabajadas=horasTrabajadasToInt;
        retorno=0;
    }
    return retorno;
}

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

int Employee_setSueldo(Employee* this,char* sueldo)
{
    int retorno=-1;
    int sueldoToInt=0;
    if(this!=NULL)
    {
        sueldoToInt=atoi(sueldo);
        this->sueldo=sueldoToInt;
        retorno=0;
    }
    return retorno;
}

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

