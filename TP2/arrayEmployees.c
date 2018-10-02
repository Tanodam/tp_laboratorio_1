#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "arrayEmployees.h"
#include "array.h"

static void swap(Empleado* empelado1,Empleado* empleado2);

/**
*\brief Realiza el swap entre dos elementos
*\param valorA es el puntero del primer elemento
*\param valorB es el puntero del segundo elemento
*\return Retorna void
*/
static void swap(Empleado* empelado1,Empleado* empleado2)
{
    Empleado auxiliar;

    auxiliar = *empelado1;
    *empelado1 = *empleado2;
    *empleado2 = auxiliar;
}

/**
*\brief Ejecuta el programa
*\param Empleado* empleados es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return Retorna void
*/
int arrancaPrograma(Empleado* empleados, int limite)
{
    int retorno = -1;
    int opcionMenu = 1;
    int indiceVacio;
    int auxId;
    int contadorEmpleados=0;
    int contadorEmpleadosSueldo=0;
    float sumaSalarios=0;
    float salarioPromedio=0;
    int i;
    int flagDatosCargados=0;

    Empleado* empleadoSeleccionado;

    empleado_inicializarArray(empleados,limite);

//    empleado_ingresoForzado(empleados,limite,"Damian","Luna",1850.25,3);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Leandro","Garcia",1650.25,6);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Lucas","Pinero",1000.12,8);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Gabriel","Egea",2000,4);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Alejandro","Baliba",1600,5);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Florencia","Picallo",1630.25,1);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Pedro","Andujar",1850.25,2);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Yamila","Bofelli",1001.12,3);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Emiliano","Gomez",2012,4);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limite,"Pablo","Coco",1600,5);
//    contadorEmpleados++;
//    flagDatosCargados=1;

    while(retorno!=0)
    {
        limpiarPantalla();
         opcionMenu=empleado_construirMenu();
         switch(opcionMenu)
         {
            case 1:
                empleado_buscarIndiceVacio(empleados,limite,&indiceVacio);
                if(indiceVacio > limite)
                {
                empleado_altaEmpleado(empleados,indiceVacio,limite);
                contadorEmpleados++;
                flagDatosCargados=1;
                pausarPantalla();
                limpiarPantalla();
                }
                else
                {
                    printf("No hay espacio disponible\n");
                    pausarPantalla();
                }
                break;

            case 2:
                if(flagDatosCargados!=0)
                {
                    array_getStringInt(&auxId,4,"Ingrese el ID que hay que modificar ", "ERROR! Ingrese un numero valido\n", 3);
                    if(empleado_busquedaPorID(empleados,limite,auxId)!= NULL)
                    {
                    empleadoSeleccionado = empleado_busquedaPorID(empleados,limite,auxId);
                    limpiarPantalla();
                    empleado_modificarEmpleado(empleadoSeleccionado,limite);
                    printf("\nModificacion realizada\n");
                    pausarPantalla();
                    }
                    else
                    {
                        printf("\nNo existe el ID\n");
                        pausarPantalla();
                    }
                }
                else
                {
                    printf("NO HAY DATOS CARGADOS\n");
                    pausarPantalla();
                }
            break;

            case 3:
                if(flagDatosCargados!=0)
                {
                    array_getStringInt(&auxId,4,"Ingrese el ID que hay que borrar ", "ERROR! Ingrese un numero valido\n", 3);
                    if(empleado_busquedaPorID(empleados,limite,auxId)!= NULL)
                    {
                    empleadoSeleccionado = empleado_busquedaPorID(empleados,limite,auxId);
                    limpiarPantalla();
                    limpiarPantalla();
                    empleado_borrarPorID(empleadoSeleccionado,limite);
                    contadorEmpleados--;
                    printf("\nEliminacion realizada\n");
                    pausarPantalla();
                    }
                    else
                    {
                        printf("No existe el ID\n");
                        pausarPantalla();
                    }
                }
                else
                {
                    printf("NO HAY DATOS CARGADOS\n");
                    pausarPantalla();
                }
                break;

            case 4: ///Se mostraran primero los empleados ordenados y luego de presionar ENTER el calculo de salarios
                    if(flagDatosCargados!=0)
                    {

                    contadorEmpleadosSueldo=0;
                    sumaSalarios=0;
                    salarioPromedio=0;
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
                    }
                else
                {
                    printf("NO HAY DATOS CARGADOS\n");
                    pausarPantalla();
                }
                break;


            case 5:
                retorno = 0;
                break;
         }
    }
    return retorno;
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
    int retorno=-1;
    char nombre[51];
    char apellido[51];
    float salario = 0;
    int sector;

    if( pBuffer != NULL && limite > 0 && pBuffer[indice].isEmpty &&

            !array_getNombre(nombre,51,"\nIngrese su nombre: ", "ERROR!",3) &&
            !array_getNombre(apellido,51,"\nIngrese su apellido: ", "ERROR!",3) &&
            !array_getStringFloat(&salario,10,0,100000,"\nIngrese el salario del empleado: ","ERROR!",50)&&
            !array_getStringInt(&sector,3,"\nIngrese el sector del empleado: ","ERROR!",3))

        {
            strncpy(pBuffer[indice].nombre,nombre,51);
            strncpy(pBuffer[indice].apellido,apellido,51);
            pBuffer[indice].salario = salario;
            pBuffer[indice].sector = sector;
            pBuffer[indice].isEmpty = 0;
            pBuffer[indice].id = empleado_obtenerID();
            retorno = 0;
        }
        return retorno;
}

int empleado_modificarEmpleado(Empleado* pBuffer,int limite)
{
    int retorno=-1;
    char nombre[51];
    char apellido[51];
    float salario = 0;
    int sector=0;

    printf("Se va a modificar el siguiente empleado\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\nID: %d\n\n",
    pBuffer->nombre, pBuffer->apellido, pBuffer->salario, pBuffer->sector, pBuffer->id);
    pausarPantalla();
    if( pBuffer != NULL && limite > 0 &&
            !array_getNombre(nombre,51,"\nIngrese su nombre: ", "ERROR!",3) &&
            !array_getNombre(apellido,51,"\nIngrese su apellido: ", "ERROR!",3) &&
            !array_getStringFloat(&salario,10,0,100000,"\nIngrese el salario del empleado: ","ERROR!",50)&&
            !array_getStringInt(&sector,3,"\nIngrese el sector del empleado: ","ERROR!",3))

        {
            strncpy(pBuffer->nombre,nombre,51);
            strncpy(pBuffer->apellido,apellido,51);
            pBuffer->salario = salario;
            pBuffer->sector = sector;
            retorno = 0;
        }
        return retorno;
}

Empleado* empleado_busquedaPorID(Empleado* pBuffer, int limite, int ID){
    int i;
    Empleado* retorno=NULL;
    for (i=0;i<limite;i++){
        if(!pBuffer[i].isEmpty && pBuffer[i].id==ID)
        {
            retorno = pBuffer+i;
            break;
        }

    }
    return retorno;
}
int empleado_existeID(Empleado* pBuffer,int limite, int identificador)
{
    int j;
    int retorno=-1;

    for(j=0;j<limite;j++)
        {
        if(pBuffer[j].id == identificador)
        {
            printf("Entro");
            retorno = 0;
            break;
        }
        else
        {
            printf("No se encontro el ID\n");
            retorno = 1;
            break;
        }
        }
    return retorno;
}
void empleado_borrarPorID(Empleado* pBuffer,int limite)
{
    printf("Se va a borrar el siguiente empleado\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\nID: %d\n\n",
    pBuffer->nombre, pBuffer->apellido, pBuffer->salario, pBuffer->sector, pBuffer->id);
    pausarPantalla();
    if(pBuffer != NULL && limite>0)
    {
        pBuffer->isEmpty=1;
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


int empleado_ingresoForzado(Empleado* pBuffer,int limite,char* nombre,char* apellido,float salario,int sector){
    int aux;

    empleado_buscarIndiceVacio(pBuffer,limite,&aux);
    pBuffer[aux].id=empleado_obtenerID();
    strncpy(pBuffer[aux].nombre,nombre,50);
    strncpy(pBuffer[aux].apellido,apellido,50);
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
                while ((j >= 0) && !empleado_comparacionApellidoYSector(&pBuffer[j], &auxiliar))
                {
                    pBuffer[j + 1] = pBuffer[j];
                    j--;
                }
                pBuffer[j + 1] = auxiliar;
            }
            if(orden == 1)
            {
                while ((j >= 0) && !empleado_comparacionApellidoYSector(&auxiliar, &pBuffer[j]))
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
int empleado_comparacionApellidoYSector(Empleado* empleado1, Empleado* empleado2)
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
