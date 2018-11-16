#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* Employee_new();
Employee* Employee_newConParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);

int Employee_setId(Employee* this,char* id);
int Employee_setNombre(Employee* this,char* nombre);
int Employee_setHorasTrabajadas(Employee* this,char* horasTrabajadas);
int Employee_setSueldo(Employee* this,char* sueldo);

int Employee_getId(Employee* this,int* id);
int Employee_getNombre(Employee* this,char* nombre);
int Employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int Employee_getSueldo(Employee* this,int* sueldo);

int Employee_delete(Employee* this);
int Employee_nuevoEmpleado(void* pArrayListEmployee);
int Employee_getNextID(void* pArrayListEmployee);
int Employee_editarEmpleado(void* pArrayListEmployee);
int employee_mostrar(Employee* this);
int Employee_modificarEmpleado(Employee* this, char* mensaje, int (*validacion)(char*),int (*set)(Employee*,char*));
int employee_eliminarEmpleado(void* pArrayListEmployee,void* listaEmpleadosBaja);

int Employee_criterioID(void* thisA, void* thisB);
int Employee_criterioNombre(void* thisA,void* thisB);
int Employee_criterioSueldo(void* thisA, void* thisB);
void seleccionarCriterioOrdenamiento(void* pArrayListEmployee);

int ll_map(void* this, int (*pFunc)(void*));
int employee_filtrarEmpleadosHoras(void* pElemento);

#endif // employee_H_INCLUDED
