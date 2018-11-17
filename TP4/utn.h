#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED

int utn_getEntero(int*pEdad,int reintentos,char* msg,char*msgError,int max,int min);
int utn_getFloat(float*pFloat,int reintentos,char* msg,char*msgError,float min,float max);
int getStrings(char* pBuffer,int limite);
int utn_confirmarLetras(char* mensaje, char* msjError, int reintentos);


#endif // UTN_H_INCLUDED
