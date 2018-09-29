
int utn_getEntero(int*pEdad,int reintentos,char* msg,char*msgError,int max,int min);
/**
    utn_getchar:valida una entrada al usuario en formato char
    @param pResultado: puntero donde guardar el char obtenido
    @return 0 is ok, -1 error
*/

int utn_mostrarArray(int * pArray,int limite);

int utn_calcularNumeroMaximo(int *pArray,int limite,int *maximo);

int utn_initArray(int * pArray,int limite,int valor);

int utn_cargaNumeroAleatoriosEnArrays(int* pArray,int len,int min, int max);
/** Calcula el promedio de un array de enteros:
@parametros
pArray: puntero al array
limite: numero de indices del array
promedio: puntero a la variable donde cargar el resultado
valorOmision: numero el cual me indique que el indice esta vacio,para omitir su suma
return: retorna -1 si el array esta cargado solo de valores de omision, 0 is ok
*/
int utn_promedioArray(int*pArray,int limite,float *promedio,int valorOmision);

/** Ordenar array de mayor a menor o de mayor a menor
@parametros
pArray: puntero al array
limite: limite del array
flagMaxMin: colocar 1 para ordenar de menor a mayor o 0 de mayor a menor
*/
int utn_ordenarArray(int *pArray,int limite,int flagMaxMin);
int utn_getFloat(float*pFloat,int reintentos,char* msg,char*msgError,float min,float max);
int utn_getLetras(char *pBuffer,int limite,int reintentos,char* msj,char*msjError);
int ordenarInsertion(int* pArray,int limite);
/**int printPersona(Persona* pBuffer);
int utn_altaPersona(Persona* pPersona,int reintentos,int lenString,int min,int max);*/

int utn_getLetrasYNumeros(char* pBuffer,int limite,char* msj);
int utn_getEmial(char *pBuffer,int limite,int reintentos,char* msj,char*msjError);
