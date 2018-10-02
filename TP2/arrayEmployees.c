#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "arrayEmployees.h"
#include "array.h"

static int empleado_obtenerID();
/**
*\brief Funcion que obtiene el proximo ID
*\return Retorna el ID
*/
static int empleado_obtenerID()
{
    static int ID=-1;
    ID++;
    return ID;
}
/**
*\brief Ejecuta el programa
*\param Empleado* empleados es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return Retorna void
*/
int arrancaPrograma(Empleado* empleados, int limiteEmpleados)
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

    empleado_inicializarArray(empleados,limiteEmpleados);
///Harcodeado forzado de informacion falsa para test, uncomment para utilizar
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Damian","Luna",1850.25,3);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Leandro","Garcia",1650.25,6);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Lucas","Pinero",1000.12,8);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Gabriel","Egea",2000,4);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Alejandro","Baliba",1600,5);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Florencia","Picallo",1630.25,1);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Pedro","Andujar",1850.25,2);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Yamila","Bofelli",1001.12,3);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Emiliano","Gomez",2012,4);
//    contadorEmpleados++;
//    empleado_ingresoForzado(empleados,limiteEmpleados,"Pablo","Coco",1600,5);
//    contadorEmpleados++;
//    flagDatosCargados=1;

    while(retorno!=0)
    {
        limpiarPantalla();
         opcionMenu=empleado_construirMenu();
         switch(opcionMenu)
         {
            case 1:
                if(!empleado_buscarIndiceVacio(empleados,limiteEmpleados,&indiceVacio))
                {
                empleado_altaEmpleado(empleados,indiceVacio,limiteEmpleados);
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
                    if(empleado_busquedaPorID(empleados,limiteEmpleados,auxId)!= NULL)
                    {
                    empleadoSeleccionado = empleado_busquedaPorID(empleados,limiteEmpleados,auxId);
                    limpiarPantalla();
                    empleado_modificarEmpleado(empleadoSeleccionado,limiteEmpleados);
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
                    if(empleado_busquedaPorID(empleados,limiteEmpleados,auxId)!= NULL)
                    {
                    empleadoSeleccionado = empleado_busquedaPorID(empleados,limiteEmpleados,auxId);
                    limpiarPantalla();
                    limpiarPantalla();
                    empleado_borrarPorID(empleadoSeleccionado,limiteEmpleados);
                    contadorEmpleados--;
                    printf("\nEliminacion realizada\n");
                    pausarPantalla();
                    if(!contadorEmpleados)
                        {   limpiarPantalla();
                            flagDatosCargados=0;
                            printf("Ya no hay usuarios en el sistema\n");
                            pausarPantalla();
                        }
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
                    empleado_ordenarApellidoYSector(empleados,limiteEmpleados,0);
                    empleado_imprimirListaEmpleados(empleados,limiteEmpleados);

                    for(i=0;i<limiteEmpleados;i++)
                    {
                        if(!empleados[i].isEmpty)
                        {
                            sumaSalarios = sumaSalarios + empleados[i].salario;
                        }
                    }

                    salarioPromedio = sumaSalarios / contadorEmpleados;

                    for(i=0;i<limiteEmpleados;i++)
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
/**
*\brief Funcion que inicializa todos los estados de .IsEmpty en 1 para indicar que el campo esta vacio.
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return Retorno todos los campos de IsEmpty en 1
*/
int empleado_inicializarArray(Empleado* array,int limite)
{
    int i;
    for(i=0;i<limite;i++){
        array[i].isEmpty=1;
    }
    return 0;
}
/**
*\brief Funcion que busca un indice vacio comprando que el campo IsEmpty sea 1
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\param indice es el indice del campo IsEmpty que se va a consultar
*\return Exito=0 Error=1
*/
int empleado_buscarIndiceVacio(Empleado* array,int limite,int*indice)
{
    int i;
    int retorno=-1;
    for(i=0;i<limite;i++){
        if(array[i].isEmpty==1){
            *indice=i;
            retorno=0;
            break;
        }
    }
    return retorno;
}
/**
*\brief Funcion que realiza el alta de un empleado
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param indice es el indice del campo IsEmpty que se va a consultar
*\param limite es la cantidad de empleados
*\return Exito=0 Error=1
*/
int empleado_altaEmpleado(Empleado* array,int indice, int limite)
{
    int retorno=-1;
    char nombre[51];
    char apellido[51];
    float salario = 0;
    int sector;

    if( array != NULL && limite > 0 && array[indice].isEmpty &&

            !array_getNombre(nombre,51,"\nIngrese su nombre: ", "ERROR!",3) &&
            !array_getNombre(apellido,51,"\nIngrese su apellido: ", "ERROR!",3) &&
            !array_getStringFloat(&salario,10,0,100000,"\nIngrese el salario del empleado $:  ","ERROR!",50)&&
            !array_getStringInt(&sector,3,"\nIngrese el sector del empleado: ","ERROR!",3))

        {
            strncpy(array[indice].nombre,nombre,51);
            strncpy(array[indice].apellido,apellido,51);
            array[indice].salario = salario;
            array[indice].sector = sector;
            array[indice].isEmpty = 0;
            array[indice].id = empleado_obtenerID();
            retorno = 0;
        }
        return retorno;
}
/**
*\brief Funcion que modifica un empleado
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return Exito=0 Error=1
*/
int empleado_modificarEmpleado(Empleado* array,int limite)
{
    int retorno=-1;
    char nombre[51];
    char apellido[51];
    float salario = 0;
    int sector=0;

    printf("Se va a modificar el siguiente empleado\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\nID: %d\n\n",
    array->nombre, array->apellido, array->salario, array->sector, array->id);
    pausarPantalla();
    if(     array != NULL && limite > 0 &&
            !array_getNombre(nombre,51,"\nIngrese su nombre: ", "ERROR!",3) &&
            !array_getNombre(apellido,51,"\nIngrese su apellido: ", "ERROR!",3) &&
            !array_getStringFloat(&salario,10,0,100000,"\nIngrese el salario del empleado: ","ERROR!",50)&&
            !array_getStringInt(&sector,3,"\nIngrese el sector del empleado: ","ERROR!",3))
        {
            strncpy(array->nombre,nombre,51);
            strncpy(array->apellido,apellido,51);
            array->salario = salario;
            array->sector = sector;
            retorno = 0;
        }
        return retorno;
}
/**
*\brief Funcion que busca un empleado por su ID.
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\param ID es el identificador de usuario que hay que encontrar
*\return Retorna el indice donde esta alojado la informacion del empleado - NULL si no encuentra nada
*/
Empleado* empleado_busquedaPorID(Empleado* array, int limite, int ID)
{
    int i;
    Empleado* retorno=NULL;
    for (i=0;i<limite;i++){
        if(!array[i].isEmpty && array[i].id==ID)
        {
            retorno = array+i;
            break;
        }

    }
    return retorno;
}
/**
*\brief Funcion que borra un empleado cambiando el estado del valor de IsEmpty
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return void
*/
void empleado_borrarPorID(Empleado* array,int limite)
{
    printf("Se va a borrar el siguiente empleado\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\nID: %d\n\n",
    array->nombre, array->apellido, array->salario, array->sector, array->id);
    pausarPantalla();
    if(array != NULL && limite>0)
    {
        array->isEmpty=1;
    }
}
/**
*\brief Funcion que imprime todos los campos de la estructura empleados
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\return Exito=0 Error=1
*/
int empleado_imprimirListaEmpleados(Empleado* array,int limite)
{
    int i;
    limpiarPantalla();

    for(i=0;i<limite;i++){
        if(array[i].isEmpty==0){
            printf("\nID: %d",array[i].id);
            printf("\nNombre: %s, %s",array[i].nombre, array[i].apellido );
            printf("\nSalario: %.2f",array[i].salario);
            printf("\nSector: %d\n",array[i].sector);

        }
    }
        pausarPantalla();
        limpiarPantalla();
    return 0;
}
/**
*\brief Construye el menu principal del ABM y valida la opcion seleccionada
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
/**
*\brief Funcion que hardcodea todos los campos de la estructura con informacion falsa para testeo
*\param Empleado* array es el puntero que recibe a la estructua Empleados para trabajar con ella y sus campos
*\param limite es la cantidad de empleados
*\param nombre es el string a copiar en en el campo nombre de la estructura
*\param apellido es el string a copiar en en el campo nombre de la estructura
*\param salario es el float a copiar en en el campo salario de la estructura
*\param nombre es el int a copiar en en el campo sector de la estructura
*\return Exito=0 Error=1
*/
int empleado_ingresoForzado(Empleado* array,int limite,char* nombre,char* apellido,float salario,int sector)
{
    int auxiliar;

    empleado_buscarIndiceVacio(array,limite,&auxiliar);
    array[auxiliar].id=empleado_obtenerID();
    strncpy(array[auxiliar].nombre,nombre,50);
    strncpy(array[auxiliar].apellido,apellido,50);
    array[auxiliar].salario=salario;
    array[auxiliar].sector=sector;
    array[auxiliar].isEmpty=0;
    return 0;
}
/**
* \brief Funcion que ordena el array comparando apellidos, si el apellido es igual, ordena el sector.
* \param array Es el array que se recorre
* \param limite Es el limite de empleados
* \param orden Es el numero que indica el sentido del ordenamiento [0] (Ascendente) [1] (Descendente)
* \return El retorno es 0 si se realizo el ordenamiento, si no el retorno es -1.
*/
int empleado_ordenarApellidoYSector(Empleado* array, int limite, int orden)
{
    int retorno=-1;
    int i;
    int j;
    Empleado auxiliar;

    if(array != NULL && limite > 0 && (orden == 0 || orden == 1))
    {
        for(i=1; i < limite; i++)
        {
            auxiliar = array[i];
            j = i - 1;
            if(orden == 0)
            {
                while ((j >= 0) && !empleado_comparacionApellidoYSector(&array[j], &auxiliar))
                {
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = auxiliar;
            }
            if(orden == 1)
            {
                while ((j >= 0) && !empleado_comparacionApellidoYSector(&auxiliar, &array[j]))
                {
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = auxiliar;
            }
        }
        retorno = 0;
    }
    return retorno;
}
/**
* \brief Funcion que compara empleados por apellido y por sector [Funcion interna de ordenarApellidoYSector]
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
