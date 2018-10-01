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
    int edad;

}Empleado;

int empleado_inicializarArray(Empleado* pBuffer,int limite);
int empleado_buscarIndiceVacio(Empleado* pBuffer,int limite,int*indice);
int empleado_imprimirListaAsociados(Empleado* pBuffer,int limite);
int empleado_altaEmpleado(Empleado* pBuffer,int indice, int limite);
int empleado_modificarEmpleadoPorId(Empleado* pBuffer,int indice);
Empleado* empleado_busquedaPorID(Empleado* pBuffer,int limite,int ID);
void empleado_borrarPorID(Empleado* pBuffer,int limite, int indice);
int empleado_existeID(Empleado* pBuffer,int limite, int ID);
int empleado_imprimirListaEmpleados(Empleado* pBuffer,int limite);
int empleado_construirMenu();
int empleado_construirModificar();
int empleado_ingresoForzado(Empleado* pBuffer,int limite,char* nombre,char* apellido,int edad,float salario,int sector);
int empleado_ordenarApellido(Empleado* pBuffer,int limite,int orden);
int empleado_sortSector(Empleado* pBuffer,int limite,int orden);





#endif // ARRAYEMPLOYEES_H_INCLUDED
