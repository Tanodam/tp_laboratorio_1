#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "arrayEmployees.h"
#include "array.h"
#include "validator.h"
static void swap(Empleado* valorA,Empleado* valorB);

/**
*\brief Realiza el swap entre dos elementos
*\param valorA es el puntero del primer elemento
*\param valorB es el puntero del segundo elemento
*\return Retorna void
*/
static void swap(Empleado* valorA,Empleado* valorB)
{
    Empleado auxiliar;//TIPO employee
    auxiliar = *valorA;
    *valorA = *valorB;
    *valorB = auxiliar;
}

/**
*\brief Ejecuta el programa
*\param valorA es el puntero del primer elemento
*\param valorB es el puntero del segundo elemento
*\return Retorna void
*/
int arrancaPrograma(Empleado* empleados, int limite)
{
    int opcionMenu = 1;
    int indiceVacio;
    int auxId;
    int contadorEmpleados=0;
    int contadorEmpleadosSueldo=0;
    float sumaSalarios=0;
    float salarioPromedio=0;
    int i;

    empleado_inicializarArray(empleados,limite);

    empleado_ingresoForzado(empleados,limite,"Damian","Gay",22,1850.25,3);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Leandro","Gay",35,1650.25,6);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Lucas","Gay",18,1000.12,8);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Gabriel","Egea",46,2000,4);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Alejandro","Baliba",26,1600,5);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Florencia","Picallo",21,1630.25,1);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Pedro","Andujar",34,1850.25,2);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Yamila","Bofelli",32,1001.12,3);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Emiliano","Gomez",37,2012,4);
    contadorEmpleados++;
    empleado_ingresoForzado(empleados,limite,"Pablo","Coco",26,1600,5);
    contadorEmpleados++;

    while(opcionMenu >= 1 && opcionMenu <=5)
    {
         opcionMenu=empleado_construirMenu();
         switch(opcionMenu)
         {
            case 1:
                empleado_buscarIndiceVacio(empleados,limite,&indiceVacio);
                empleado_altaEmpleado(empleados,indiceVacio,limite);
                contadorEmpleados++;
                myFlush();
                pausarPantalla();
                limpiarPantalla();
                break;

            case 2:
                utn_getEntero(&auxId,3,"Ingrese el ID a buscar: ","ERROR!", 0, 3000);
                if(empleado_busquedaPorID(empleados,limite,auxId)!= NULL)
                {

                    empleado_modificarEmpleadoPorId(empleados,auxId);
                }


            break;

            case 3:
                utn_getEntero(&auxId,3,"Ingrese el ID a borrar: ","ERROR!", 0, 3000);
                if(empleado_busquedaPorID(empleados,limite,auxId)!= NULL)
                {
                    empleado_borrarPorID(empleados,limite,auxId);
                }

                break;

            case 4: ///Se mostraran primero los empleados ordenados y luego de presionar ENTER el calculo de salarios

                    empleado_ordenarApellidoYSector(empleados,limite,0);
                    empleado_imprimirListaEmpleados(empleados,limite);

                    for(i=0;i<limite;i++)
                    {
                        if(!empleados[i].isEmpty)
                        {
                            sumaSalarios = sumaSalarios + empleados[i].salario;
                        }
                    }

                    salarioPromedio = sumaSalarios / contadorEmpleados;

                    for(i=0;i<limite;i++)
                    {
                        if(empleados[i].salario > salarioPromedio && !empleados[i].isEmpty)
                        {
                            contadorEmpleadosSueldo++;
                        }
                    }

                    printf("\nEl total de salarios es %.2f",sumaSalarios);
                    printf("\nEl promedio de salarios es %.2f",salarioPromedio);
                    printf("\nEl total de empleados que superan el promedio es %d\n",contadorEmpleadosSueldo);
                    pausarPantalla();
                    limpiarPantalla();


                break;


            case 5: printf("Adios");
            break;

            default: printf("error ingrese una opcion valida");
         }
    }
    return 0;

}

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
    array_getStringInt(&pBuffer[indice].edad,3,"\nIngrese la edad: ","ERROR",3);
    array_getStringFloat(&pBuffer[indice].salario,10,"\nIngrese el salario: ","ERROR",3);
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

    for(i=0;i<limite;i++){
        if(pBuffer[i].isEmpty==0){
            printf("\nID: %d",pBuffer[i].id);
            printf("\nNombre: %s, %s",pBuffer[i].nombre, pBuffer[i].apellido );
            printf("\nSalario: %.2f",pBuffer[i].salario);
            printf("\nEdad: %d",pBuffer[i].edad);
            printf("\nSector: %d\n",pBuffer[i].sector);

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


/**
*\brief Ordena todos los elementos de un array
*\param array Es el array que recibe para ordenar
*\param size Es el tamaño del array
*\param orden Es el numero que indica ordenar de forma ascendente o descendente
*\return Retorna 0 si no retorna -1
*/

int empleado_ordenarApellido(Empleado* pBuffer,int limite,int orden)
{
    int retorno = -1;
    int i;
    int j;

    if(pBuffer != NULL && limite > 0)
    {

        if(orden == 1)
        {
            retorno = 0;

            for(i=0;i<limite;i++)
            {
                for(j=i+1;j<limite;j++)
                {
                    if(strcmp(pBuffer[i].apellido,pBuffer[j].apellido) > 0)
                    {
                        swap(pBuffer+i,pBuffer+j);
                    }
                }
            }
        }
        else if(orden == 0)
        {
            retorno = 0;

            for(i=0;i<limite;i++)
            {
                for(j=i+1;j<limite;j++)
                {
                    if(strcmp(pBuffer[i].apellido,pBuffer[j].apellido) < 0)
                    {
                        swap(pBuffer+i,pBuffer+j);
                    }
                }
            }
        }


    }
    return retorno;
}

int empleado_sortSector(Empleado* pBuffer,int limite,int orden)
{
    int retorno = -1;
    int i;
    int j;

    if(pBuffer != NULL && limite > 0)
    {

        if(orden == 1)
        {
            retorno = 0;

            for(i=0;i<limite;i++)
            {
                for(j=i+1;j<limite;j++)
                {
                    if(pBuffer[i].sector > pBuffer[i-1].sector)
                    {
                        swap(pBuffer+i,pBuffer+j);
                    }
                }
            }
        }
        else if(orden == 0)
        {
            retorno = 0;

            for(i=0;i<limite;i++)
            {
                for(j=i+1;j<limite;j++)
                {
                    if(pBuffer[i].sector < pBuffer[i-1].sector)
                    {
                        swap(pBuffer+i,pBuffer+j);
                    }
                }
            }
        }


    }
    return retorno;


}


/**
* \brief    ordena un array de empleados por insercion, por 2 criterios,
*           primero por apellido y en caso de coincidir, por sector
* \param array Es el array que se recorre
* \param len Es el limite de empleados que puede guardar el array
* \param orden El orden debe ser 0 (Ascendente) o 1 (Descendente)
* \return El retorno es 0 si se realizo el ordenamiento, si no el retorno es -1.
*/
int empleado_ordenarApellidoYSector(Empleado* pBuffer, int limite, int orden)
{
    int retorno=-1;
    int i;
    int j;
    Empleado auxiliar;

    if(pBuffer != NULL && limite > 0 && (orden == 0 || orden == 1))
    {
        for(i=1; i < limite; i++)
        {
            auxiliar = pBuffer[i];
            j = i - 1;
            if(orden == 0)
            {
                while ((j >= 0) && !comparacionApellidoYSector(&pBuffer[j], &auxiliar))
                {
                    pBuffer[j + 1] = pBuffer[j];
                    j--;
                }
                pBuffer[j + 1] = auxiliar;
            }
            if(orden == 1)
            {
                while ((j >= 0) && !comparacionApellidoYSector(&auxiliar, &pBuffer[j]))
                {
                    pBuffer[j + 1] = pBuffer[j];
                    j--;
                }
                pBuffer[j + 1] = auxiliar;
            }
        }
        retorno = 0;
    }
    return retorno;
}

/**
* \brief compara a los empleados, primero por apellido y en caso de coincidir, por sector
* \param arrayUno es el primer empleado que se va a comparar
* \param arrayDos es el segundo empleado que se va a comparar
* \return si el primero es mayor devuelve 0(para que se realice el swap), si no -1
*/
int comparacionApellidoYSector(Empleado* empleado1, Empleado* empleado2)
{
    int retorno=-1;
    if(empleado1 != NULL && empleado2 != NULL)
    {
        if( strcmp(empleado1->apellido, empleado2->apellido) > 0 ||
            (strcmp(empleado1->apellido, empleado2->apellido) == 0 && empleado1->sector > empleado2->sector))
        {
            retorno = 0;
        }
    }
    return retorno;
}
