#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#include "array.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path char* ruta del archivo
 * \param pArrayListEmployee LinkedList* lista donde se va a guardar el archivo
 * \return [0] Exito y [-1] Error
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(!ll_len(pArrayListEmployee))
    {
        FILE* pArchivo = fopen(path,"r");
        retorno = parser_EmployeeFromText(pArchivo,pArrayListEmployee);
        if(retorno!=-1)
        {
            printf("ARCHIVO CARGADO CON EXITO!\nCANTIDAD DE EMPLEADOS: %d\n", ll_len(pArrayListEmployee));
        }
        fclose(pArchivo);
    }
    else
    {
        printf("EL ARCHIVO YA FUE CARGADO\n");
    }
    return retorno;
}
/** \brief Carga los datos de los empleados desde el archivo data.dat (modo binario).
 * \param path char* ruta del archivo
 * \param pArrayListEmployee LinkedList* lista donde se va a guardar el archivo
 * \return [0] Exito y [-1] Error
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pArchivo;
    pArchivo = fopen(path,"rb");
    if(!ll_len(pArrayListEmployee))
    {

        retorno = parser_EmployeeFromBinary(pArchivo,pArrayListEmployee);
        if(retorno != -1)
        {
            printf("ARCHIVO CARGADO CON EXITO!\nCANTIDAD DE EMPLEADOS: %d\n", ll_len(pArrayListEmployee));
            retorno = 0;
        }
        else
        {
            printf("NO HAY NINGUN ARCHIVO BINARIO GENERADO");
        }
    }
    else
    {
        printf("EL ARCHIVO YA FUE CARGADO\n");
    }
    fclose(pArchivo);
    return retorno;
}
/** \brief Alta de empleados
 * \param pArrayListEmployee LinkedList* lista donde se va a cargar el nuevo empleado
 * \return * \return [0] Exito y [-1] Error
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        if(!Employee_nuevoEmpleado(pArrayListEmployee))
        {
            retorno = 0;
            printf("\nSE AGREGO UN NUEVO EMPLEADO");
        }
    }
    else
    {
        printf("NO HAY NINGUNA LISTA CARGADA");
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 * \param pArrayListEmployee LinkedList* lista donde se encuentra el empleado a modificar
 * \return [0] Exito y [-1] Error
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        if(!Employee_editarEmpleado(pArrayListEmployee))
        {
            printf("\nEl empleado fue modificado");
            retorno = 0;
        }
    }
    else
    {
        printf("No hay ninguna lista cargada");
    }
    return retorno;
}

/** \brief Baja de empleado

 * \param LinkedList* pArrayListEmployee lista donde se encuentra el empleado a eliminar
 * \param LinkedList* listaEmpleadosBaja lista destino donde el ll_pop va a dejar el empleado eliminado
 * \return [0] Exito y [-1] Error
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee, LinkedList* listaEmpleadosBaja)
{
    int retorno = -1;

    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        if(!employee_eliminarEmpleado(pArrayListEmployee, listaEmpleadosBaja))
        {
            printf("\nEL EMPLEADO FUE ELIMINADO");
            retorno = 0;
        }
    }
    else
    {
        printf("NO HAY NINGUNA LISTA CARGADA");
    }
    return retorno;
}

/** \brief Listar empleados
 * \param pArrayListEmployee LinkedList* lista que se va a mostrar
 * \return [0] Exito y [-1] Error
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    Employee* auxiliarEmpleado;
    char nombre[128];
    int horasTrabajadas = 0;
    int sueldo = 0;
    int id=0;
    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        retorno = 0;
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            auxiliarEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getNombre(auxiliarEmpleado,nombre);
            Employee_getId(auxiliarEmpleado,&id);
            Employee_getSueldo(auxiliarEmpleado,&sueldo);
            Employee_getHorasTrabajadas(auxiliarEmpleado,&horasTrabajadas);
            printf("\nID: %d \t Nombre: %s \t HorasTrabajadas: %d \t Sueldo: %d",id,nombre,horasTrabajadas,sueldo);
        }
    }
    else
    {
        printf("NO HAY NINGUNA LISTA CARGADA");
    }
    printf("\n\nCANTIDAD DE EMPLEADOS: %d", ll_len(pArrayListEmployee));
    return retorno;
}
/** \brief Listar empleados
 * \param pArrayListEmployee LinkedList* lista que se va a mostrar
 * \return [0] Exito y [-1] Error
 */
int controller_deleteList(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char opcion[2];

    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        array_getLetras(opcion,2,"\n****¿ESTAS SEGURO QUE QUERES BORRAR TODOS LOS EMPLEADOS?**** ELIJA S/N\n","\nERROR!",2);
        if(!strcasecmp(opcion,"s"))
        {
            ll_deleteLinkedList(pArrayListEmployee);
            printf("\nLISTA BORRADA");
            retorno = 0;
        }
    }
    else
    {
        printf("NO HAY NINGUNA LISTA CARGADA");
    }
    return retorno;
}

/** \brief Ordenar empleados
 * \param pArrayListEmployee LinkedList* lista de empleados que se va a ordenar
 * \return [0] Exito y [-1] Error
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        seleccionarCriterioOrdenamiento(pArrayListEmployee);
        retorno = 0;
    }
    else
    {
        printf("NO HAY NINGUNA LISTA CARGADA");
    }
    return retorno;
}

int controller_filter(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    LinkedList* sublist;
    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        sublist = ll_filter(pArrayListEmployee,employee_filtrarEmpleadosHoras);
        ll_map(sublist,employee_mostrar);
        retorno = 0;
    }
    return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* ruta del archivo
 * \param pArrayListEmployee LinkedList* lista que se va a guardar
 * \return [0] Exito y [-1] Error
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo = fopen(path,"w+");
    int retorno = -1;
    if(pArchivo != NULL && !parser_SaveToText(pArchivo,pArrayListEmployee) &&
            pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        retorno = 0;
        printf("\nARCHIVO %s GUARDADO CON EXITO", path);
    }
    else
    {
        printf("No hay ninguna lista cargada\n");
    }
    fclose(pArchivo);
    return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 * \param pArrayListEmployee LinkedList* lista que se va a guardar
 * \return [0] Exito y [-1] Error
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE *pArchivo = fopen(path, "wb");
    Employee* pEmpleado;
    int i;

    if(pArchivo != NULL && pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            pEmpleado = ll_get(pArrayListEmployee,i);
            fwrite(pEmpleado,sizeof(Employee),1,pArchivo);
        }
        printf("\nARCHIVO %s GUARDADO CON EXITO", path);
    }
    else
    {
        printf("\nNO HAY NINGUNA LISTA CARGADA");
    }
    fclose(pArchivo);
    return 1;
}
/** \brief Funcion que ejecuta el menu principal
 * \return void
 */
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Listar empleados de baja
     8. Ordenar empleados
     9. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     10. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    11. Salir
*****************************************************/

void controller_init()
{
    LinkedList* listaEmpleados = ll_newLinkedList(); ///Lista de activos
    LinkedList* listaEmpleadosBaja=ll_newLinkedList();///Lista de inactivos
    int option = 0;
    do
    {
        limpiarPantalla();
        utn_getEntero(&option,2,"1. Carga de empleados (modo texto)\n"
                      "2. Carga de empleados (modo binario)\n"
                      "3. Alta empleado\n"
                      "4. Modificar empleado\n"
                      "5. Baja empleado\n"
                      "6. Borrar toda la lista de empleados\n"
                      "7. Listar empleados\n"
                      "8. Listar empleados de baja\n"
                      "9. Ordenar empleados\n"
                      "10. Filtrar empleados\n"
                      "11. Guardar empleados (modo texto)\n"
                      "12. Guardar empleados (modo binario)\n"
                      "13. Salir\n\nOpcion: ","Opcion invalida\n", 1,15);
        switch(option)
        {
        case 1:
            printf("\nACTIVOS\n");
            controller_loadFromText("data.csv",listaEmpleados);
            printf("\nINACTIVOS\n");
            controller_loadFromText("dataBajas.csv",listaEmpleadosBaja);
            break;
        case 2:
            printf("\nACTIVOS\n");
            controller_loadFromBinary("data.dat",listaEmpleados);
            printf("\nINACTIVOS\n");
            controller_loadFromBinary("dataBajas.dat",listaEmpleadosBaja);
            break;
        case 3:
            controller_addEmployee(listaEmpleados);
            break;
        case 4:
            controller_editEmployee(listaEmpleados);
            break;
        case 5:
            controller_removeEmployee(listaEmpleados, listaEmpleadosBaja);
            break;
        case 6:
            controller_deleteList(listaEmpleados);
            break;
        case 7:
            controller_ListEmployee(listaEmpleados);
            break;
        case 8:
            controller_ListEmployee(listaEmpleadosBaja);
            break;
        case 9:
            controller_sortEmployee(listaEmpleados);
            break;
        case 10:
            controller_filter(listaEmpleados);
            break;
        case 11:
            controller_saveAsText("data.csv",listaEmpleados);
            controller_saveAsText("dataBajas.csv",listaEmpleadosBaja);
            break;
        case 12:
            controller_saveAsBinary("data.dat",listaEmpleados);
            controller_saveAsBinary("dataBajas.dat",listaEmpleadosBaja);
            break;
        case 13:
            break;
        default:
            printf("Opcion Incorrecta\n");
            break;
        }
        printf("\nPulse Enter para continuar");
        myFlush();
        getchar();
    }
    while(option != 13);
}
