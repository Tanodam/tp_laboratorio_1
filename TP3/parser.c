#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int flagPrimeraVuelta=1;
    char bufferID[1024];
    char bufferNombre[1024];
    char bufferHorasTrabajadas[1024];
    char bufferSueldo[1024];

    Employee* pEmpleado = NULL;

    if(pFile!=NULL)
    {
        while(!feof(pFile))
        {
            if(flagPrimeraVuelta)
            {
                flagPrimeraVuelta = 0;
                fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",
                       bufferID,
                       bufferNombre,
                       bufferHorasTrabajadas,
                       bufferSueldo);
            }
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",
                   bufferID,
                   bufferNombre,
                   bufferHorasTrabajadas,
                   bufferSueldo);

            pEmpleado = Employee_newConParametros(bufferID,
                                                  bufferNombre,
                                                  bufferHorasTrabajadas,
                                                  bufferSueldo);

            if(pEmpleado != NULL)
            {
                retorno = 0;
                ll_add(pArrayListEmployee,pEmpleado);
            }
        }
    }

    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int cantidadLeida;
    Employee* pEmployee;
    Employee* aux = Employee_new();

    if(pFile != NULL && pArrayListEmployee != NULL && ll_len(pArrayListEmployee))
    {
        while(!feof(pFile))
        {
            pEmployee = Employee_new();
            cantidadLeida = fread(pEmployee,sizeof(Employee),1,pFile);
            if(pEmployee != NULL && cantidadLeida == 1)
            {
                ll_add(pArrayListEmployee,pEmployee);//Se agrega ELEMENTO a LINKED LIST
                retorno = 0;
            }
        }
        Employee_delete(aux);
    }
    return retorno;
}
/** \brief Parsea los datos del linked list al archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_SaveToText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    Employee* this = NULL;
    int retorno = -1;
    int i = 0;
    char bufferNombre[1024];
    int bufferId = 0;
    int bufferHorasTrabajadas = 0;
    int bufferSueldo = 0;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        for(i=0; i<ll_len(pArrayListEmployee); i++) //Recorro todo el array hasta el LEN
        {
            if(i==0)
            {
                fprintf(pFile,"id,nombre,horas,sueldo\n");///Agrega la cabecera al archivo de texto
            }
            this = ll_get(pArrayListEmployee,i);//Obtengo el elemento del array en posicion index
            Employee_getNombre(this,bufferNombre);
            Employee_getHorasTrabajadas(this,&bufferHorasTrabajadas);
            Employee_getSueldo(this,&bufferSueldo);
            Employee_getId(this,&bufferId);
            //printf("%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            fprintf(pFile,"%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Parsea los datos del linked list al archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_SaveToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i = 0;
    int len;
    Employee* auxEmployee;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);
        while(i != len)
        {
            auxEmployee = ll_get(pArrayListEmployee,i);
            if(auxEmployee != NULL)
            {
                fwrite(auxEmployee,sizeof(Employee),1,pFile);
            }
            retorno = 0;
            i++;
        }
    }
    return retorno;
}

