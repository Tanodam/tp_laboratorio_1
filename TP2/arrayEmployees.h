#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED
typedef struct
{
    int id;
    char nombre[51];
    char apellido[51];
    float salario;
    int isEmpty;
    int sector;

}Empleado;

int empleado_inicializarArray(Empleado* array,int limite);
int empleado_buscarIndiceVacio(Empleado* array,int limite,int*indice);
int empleado_altaEmpleado(Empleado* array,int indice, int limite);
int empleado_modificarEmpleado(Empleado* array,int limite);
Empleado* empleado_busquedaPorID(Empleado* array, int limite, int ID);
void empleado_borrarPorID(Empleado* pBuffer,int limite);
int empleado_imprimirListaEmpleados(Empleado* pBuffer,int limite);
int empleado_construirMenu();
int empleado_ingresoForzado(Empleado* pBuffer,int limite,char* nombre,char* apellido,float salario,int sector);
int empleado_ordenarApellidoYSector(Empleado* pBuffer, int limite, int orden);
int empleado_comparacionApellidoYSector(Empleado* empleado1, Empleado* empleado2);
int arrancaPrograma(Empleado* empleados, int limite);





#endif // ARRAYEMPLOYEES_H_INCLUDED
