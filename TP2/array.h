#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#define false 0
#define true 1
#define DATO_INVALIDO -1

void myFlush();
void limpiarPantalla();
void pausarPantalla();

char array_getNombre(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos);
char array_getMail(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos);
char array_getTelefono(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos);
int array_getStringFloat(float* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos);
int array_getStringInt(int* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos);
int array_mostrar(int* pArray, int limiteArray);
int array_calcularMaximo(int* pArray, int limiteArray, int* pMaximo);
int array_init(int* pArray, int limiteArray, int valor);

void array_imprimirIntArray(int* pArray, int limiteArray);
int array_ordenarArrayInsercion(int* pArray, int limiteArray);



#endif // ARRAY_H_INCLUDED
