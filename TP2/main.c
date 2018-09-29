#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "arrayEmployees.h"
#include "array.h"
#define CANTIDAD_EMPLEADOS 10

int main()
{
    int opcionMenu = 1;
    int indiceVacio;
    int auxId;
    Empleado empleados[CANTIDAD_EMPLEADOS];
    empleado_inicializarArray(empleados,CANTIDAD_EMPLEADOS);

    empleado_ingresoForzado(empleados,CANTIDAD_EMPLEADOS,"Damian","Desario",22,1850.25,18);
    empleado_ingresoForzado(empleados,CANTIDAD_EMPLEADOS,"Leandro","Torres",35,1650.25,22);
    empleado_ingresoForzado(empleados,CANTIDAD_EMPLEADOS,"Lucas","Planes",18,1000.12,1);
    empleado_ingresoForzado(empleados,CANTIDAD_EMPLEADOS,"Gabriel","Egea",46,2000,21);
    empleado_ingresoForzado(empleados,CANTIDAD_EMPLEADOS,"Alejandro","Baliba",26,1600,1);

    while(opcionMenu >= 1 && opcionMenu <=5)
    {
         opcionMenu=empleado_construirMenu();
         switch(opcionMenu)
         {
            case 1:
                empleado_buscarIndiceVacio(empleados,CANTIDAD_EMPLEADOS,&indiceVacio);
                empleado_altaEmpleado(empleados,indiceVacio,CANTIDAD_EMPLEADOS);
                myFlush();
                pausarPantalla();
                limpiarPantalla();
                break;

            case 2:
                utn_getEntero(&auxId,3,"Ingrese el ID a buscar: ","ERROR!", 0, 3000);
                if(empleado_busquedaPorID(empleados,CANTIDAD_EMPLEADOS,auxId)!= NULL)
                {

                    empleado_modificarEmpleadoPorId(empleados,auxId);
                }


            break;

            case 3:
                utn_getEntero(&auxId,3,"Ingrese el ID a borrar: ","ERROR!", 0, 3000);
                if(empleado_busquedaPorID(empleados,CANTIDAD_EMPLEADOS,auxId)!= NULL)
                {
                    empleado_borrarPorID(empleados,CANTIDAD_EMPLEADOS,auxId);
                }

                break;

            case 4:
                    empleado_sort(empleados,CANTIDAD_EMPLEADOS);


                break;


            case 5: printf("Adios");
            break;

            default: printf("error ingrese una opcion valida");
         }
    }


    return 0;
}
