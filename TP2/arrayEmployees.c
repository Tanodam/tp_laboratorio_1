#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "arrayEmployees.h"
#include "array.h"
#include "validator.h"


int empleado_inicializarArray(Empleado* pBuffer,int limite){
    int i;
    for(i=0;i<limite;i++){
        pBuffer[i].isEmpty=1;
    }
    return 0;
}
int empleado_buscarIndiceVacio(Empleado* pBuffer,int limite,int*indice){
    int i;
    int retorno=-1;
    for(i=0;i<limite;i++){
        if(pBuffer[i].isEmpty==1){
            *indice=i;
            retorno=0;
            break;
        }
    }
    return retorno;
}

int empleado_obtenerID(){
    static int ID=-1;
    ID++;
    return ID;
}
int empleado_altaEmpleado(Empleado* pBuffer,int indice, int limite)
{
    array_getNombre(pBuffer[indice].nombre,51, "\nIngrese su nombre: ", "\nERROR!", 3);
    array_getNombre(pBuffer[indice].apellido, 51, "\nIngrese su apellido: ", "\nERROR!", 3);
    utn_getEntero(&pBuffer[indice].edad,3,"\nIngrese su edad: ", "\nError!", 18, 70);
    utn_getFloat(&pBuffer[indice].salario, 3, "\nIngrese el salario: ", "\nError!",0.0, 99999.0);
    utn_getEntero(&pBuffer[indice].sector,3,"\nIngrese el sector: ", "\nError!", 1, 38);
    pBuffer[indice].isEmpty=0;
    pBuffer[indice].id=empleado_obtenerID();

    return 0;
}

int empleado_modificarEmpleadoPorId(Empleado* pBuffer,int indice){
    array_getNombre(pBuffer[indice].nombre,51,"\nIngrese su nombre: ","\nERROR!", 3);
    array_getNombre(pBuffer[indice].apellido, 51,"\nIngrese su apellido: ","\nERROR!", 3);
    utn_getEntero(&pBuffer[indice].edad,3,"\nIngrese su edad: ","\nError!", 18, 70);
    utn_getFloat(&pBuffer[indice].salario, 3, "\nIngrese el salario: ","\nERROR!",0.0, 99999.0);
    utn_getEntero(&pBuffer[indice].sector,3,"\nIngrese el sector: ","\nERROR!", 1, 38);
    return 0;
}

Empleado* empleado_busquedaPorID(Empleado* pBuffer, int limite, int ID){
    int i;
    Empleado* retorno=NULL;
    for (i=0;i<limite;i++){
        if(pBuffer[i].isEmpty==0 && pBuffer[i].id==ID){

            retorno= &pBuffer[i];
            break;
        }
    }
    return retorno;
}
int empleado_existeID(Empleado* pBuffer,int limite, int ID){
    int i;
    int retorno=-1;
    for(i=0;i<limite;i++){
        if(pBuffer[i].id==ID && pBuffer[i].isEmpty==0){
            retorno=0;
        }
    }
    return retorno;
}
void empleado_borrarPorID(Empleado* pBuffer,int limite, int indice)
{
    if(pBuffer != NULL && limite>0)
    {
        pBuffer[indice].isEmpty=1;
    }
}

int empleado_imprimirListaEmpleados(Empleado* pBuffer,int limite)
{
    int i;
    limpiarPantalla();
    myFlush();

    for(i=0;i<limite;i++){
        if(pBuffer[i].isEmpty==0){
            printf("\nID: %d",pBuffer[i].id);
            printf("\nNombre: %s",pBuffer[i].nombre);
            printf("\nApellido: %s",pBuffer[i].apellido);
            printf("\nSalario: %.2f",pBuffer[i].salario);
            printf("\nEdad: %d",pBuffer[i].edad);
            printf("\nSector: %d\n\n",pBuffer[i].sector);

        }
    }
        pausarPantalla();
        limpiarPantalla();
    return 0;
}

/**
*\brief Construye el menu principal de la Calculadora y valida la opcion seleccionada
*\param Valor de la variable asignada a numeroA para mostrarla en pantalla.
*\param Valor de la variable asignada a numeroB para mostrarla en pantalla.
*\return Exito=0 Devuelve la opcion ingresada y validada Error=5 Devuelve 5 porque es el case de Salida del programa.
*
*/
int empleado_construirMenu()
{
        int respuesta;
        printf("1. Alta Empleado\n");
        printf("2. Modificar Empleado\n");
        printf("3. Baja Empleado\n");
        printf("4. Informar \n");
        printf("5. Salir\n");
        myFlush();
        if(utn_getEntero(&respuesta,3,"Ingrese la opcion deseada\n","Opcion invalida\n", 1,5))
        {
            return 5;
        }

        return respuesta;
}

int empleado_ingresoForzado(Empleado* pBuffer,int limite,char* nombre,char* apellido,int edad,float salario,int sector){
    int aux;

    empleado_buscarIndiceVacio(pBuffer,limite,&aux);
    pBuffer[aux].id=empleado_obtenerID();
    strncpy(pBuffer[aux].nombre,nombre,50);
    strncpy(pBuffer[aux].apellido,apellido,50);
    pBuffer[aux].edad=edad;
    pBuffer[aux].salario=salario;
    pBuffer[aux].sector=sector;
    pBuffer[aux].isEmpty=0;
    return 0;
}

int empleado_sort(Empleado* pBuffer,int limite)
{
    int retorno=-1;
    int i;
    int j;
    Empleado auxiliar;

    if(pBuffer != NULL && limite >0)
    {
        retorno = 0;

        for(i=0;i<limite-1;j++)
        {
            if(strcmp(pBuffer[i].apellido,pBuffer[j].apellido)>0)
               {
                   printf("\nAPELLIDO %d %s", i,pBuffer[i].apellido);
                   printf("\nAPELLIDO %d %s", j,pBuffer[j].apellido);
                   auxiliar=pBuffer[i];
                   pBuffer[i]=pBuffer[j];
                   pBuffer[j]=auxiliar;
               }
//            else if((strcmp(pBuffer[i].apellido, pBuffer[j].apellido)) && (pBuffer[i].sector == pBuffer[j].sector))
//            {
////                printf("\nAPELLIDO %d %s", i,pBuffer[i].apellido);
////                printf("\nAPELLIDO %d %s", j,pBuffer[j].apellido);
//                   auxiliar=pBuffer[i];
//                   pBuffer[i]=pBuffer[j];
//                   pBuffer[j]=auxiliar;
//            }
        }
    }
    return retorno;
}
