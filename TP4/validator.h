#ifndef VALIDATOR_H_INCLUDED
#define VALIDATOR_H_INCLUDED

int array_StringMailEsValido (char* pArray, int limiteArray);

int array_StringFloatEsValido (char* pArray, int limiteArray);
int array_StringCharEsValido (char* pArray, int limiteArray);
char array_StringTelefonoEsValido (char* pArray, int limiteArray);
int array_StringIntEsValido(char* pArray, int limiteArray);
int isValidCuilOrCuit(char *pBuffer, int limite);
int array_StringCharEsValidoDos(char* array,int size);
int isValidEntero(char *pBuffer, int limite);

#endif // VALIDATOR_H_INCLUDED
