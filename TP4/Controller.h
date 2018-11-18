#ifndef controller_H_INCLUDED
#define controller_H_INCLUDED

int controller_loadFromText(char* path, LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee, LinkedList* listaEmpleadosBaja);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);
void controller_init();
int controller_deleteAndBackupList(LinkedList* pArrayListEmployee, LinkedList* listaEmpleadosBaja);
LinkedList* controller_cloneList(LinkedList* pArrayListEmployee);
int controller_createSubList(LinkedList* pArraylistEmployee);

#endif //controller_H_INCLUDED
