#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 * \param FILE* pFile Puntero del tipo file al archivo que hay que parsear
 * \param pArrayListEmployee LinkedList* lista donde se van a a guardar los empleados
 * \return Exito=1 y Error=-0
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
/** \brief Parsea los datos los datos de los empleados desde el archivo data.dat (modo texto).
 * \param FILE* pFile Puntero del tipo file al archivo que hay que parsear
 * \param pArrayListEmployee LinkedList* lista donde se van a a guardar los empleados
 * \return Exito=1 y Error=-0
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int cantidadLeida;
    Employee* pEmployee;
    Employee* aux = Employee_new();

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            pEmployee = Employee_new();
            cantidadLeida = fread(pEmployee,sizeof(Employee),1,pFile);
            if(pEmployee != NULL && cantidadLeida == 1)
            {
                Employee_setId(aux,"0");
                ll_add(pArrayListEmployee,pEmployee);
                retorno = 0;
            }
        }
    }
    return retorno;
}
/** \brief Parsea los datos los datos de los empleados al archivo data.csv (modo texto).
 * \param FILE* pFile Puntero del tipo file al archivo que hay que parsear
 * \param pArrayListEmployee LinkedList* lista desde donde se van a a guardar los empleados
 * \return Exito=1 y Error=-0
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
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            if(i==0)
            {
                fprintf(pFile,"id,nombre,horas,sueldo\n");///Agrega la cabecera al archivo de texto
            }
            this = ll_get(pArrayListEmployee,i);
            Employee_getNombre(this,bufferNombre);
            Employee_getHorasTrabajadas(this,&bufferHorasTrabajadas);
            Employee_getSueldo(this,&bufferSueldo);
            Employee_getId(this,&bufferId);
            fprintf(pFile,"%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    return retorno;
}
/** \brief Parsea los datos los datos de los empleados al archivo data.dat (modo texto).
 * \param FILE* pFile Puntero del tipo file al archivo que hay que parsear
 * \param pArrayListEmployee LinkedList* lista desde donde se van a a guardar los empleados
 * \return Exito=1 y Error=-0
 */
int parser_SaveToBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    Employee* auxiliarEmpleado = NULL;
    int retorno = -1;
    int i = 0;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        while(i != ll_len(pArrayListEmployee))
        {
            auxiliarEmpleado = ll_get(pArrayListEmployee,i);
            if(auxiliarEmpleado != NULL)
            {
                fwrite(auxiliarEmpleado,sizeof(Employee),1,pFile);
            }
            retorno = 0;
            i++;
        }
    }
    return retorno;
}
