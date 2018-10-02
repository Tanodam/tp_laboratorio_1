#include "utn.h"
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "array.h"
static int getFloat(float*pBuffer);
int getString(char* bufferString,int limite);
static int isFloat(char* pBuffer);
static int getInt(int*pBuffer);
static int isInt(char *pBuffer);

/**
*\brief Solicita un int al usuario y lo devuelve validado mediante la funcion IsInt.
*\param pArray pFloat a la direccion de memoria donde se va almacenar el float validado
*\param msg[] es el mensaje que se le va a mostrar al usuario
*\param msgError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param minimo es el numero minimo aceptado
*\param maximoes el numero maximo aceptado
*\return Exito=0 y Error=1
*
*/
int utn_getEntero(int* pEntero,int reintentos,char* msg,char*msgError,int min,int max){
    int retorno = -1;
    int buffer;

    if(pEntero!=NULL&& msg !=NULL && msgError!=NULL && min<= max && reintentos>=0){
        do
        {
            reintentos--;
            printf("%s",msg);
            if(getInt(&buffer) == 0 && buffer >= min && buffer<=max){
                    *pEntero= buffer;
                    retorno = 0;
                    break;
            }else{
                printf("%s",msgError);
            }
        }while(reintentos >= 0);
    }
    return retorno;
}
/**
*\brief Solicita un floar al usuario y lo devuelve validado mediante la funcion IsFloat.
*\param pArray pFloat a la direccion de memoria donde se va almacenar el float validado
*\param msg[] es el mensaje que se le va a mostrar al usuario
*\param msgError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param minimo es el numero minimo aceptado
*\param maximoes el numero maximo aceptado
*\return Exito=0 y Error=1
*
*/
int utn_getFloat(float*pFloat,int reintentos,char* msg,char*msgError,float min,float max)
{
    int retorno = -1;
    float buffer;

    if(pFloat!=NULL&& msg !=NULL && msgError!=NULL && min<= max && reintentos>=0){
        do
        {
            reintentos--;
            printf("%s: ",msg);
            if(getFloat(&buffer) == 0 && buffer >= min && buffer<=max){
                    *pFloat= buffer;
                    retorno = 0;
                    break;
            }else{
                printf("%s",msgError);
            }
        }while(reintentos >= 0);
    }
    return retorno;
}
/**
*\brief Funcion estatica que se encarga de tomar datos por consola
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string que se tomo por consola
*\return Exito=0 y Error=-1
*/
static int getInt(int* pBuffer)
{
    char bufferString[200];
    int retorno =-1;
    if(getString(bufferString,200)==0 && isInt(bufferString)==0){
        *pBuffer=atoi(bufferString);
        retorno=0;
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetInt] Valida que el usuario solo haya ingresado caracteres del 0 al 9
*\param pBuffer Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=0 y Error=-1
*/
static int isInt(char *pBuffer)
{
    int retorno=-1;
    int i=0;
    do{
        if(*(pBuffer+i)<48||*(pBuffer+i)>57){
                break;
        }
        i++;
    }while (i<strlen(pBuffer));
    if(i==strlen(pBuffer)){
        retorno=0;
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetFloat] Valida que el usuario solo haya ingresado caracteres del 0 al 9
*\param pBuffer Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=0 y Error=-1
*/
static int isFloat(char* pBuffer)
{
    int retorno=-1;
    int i=0;
    int contadorDePuntos=0;
    do{
        if(*(pBuffer+i)==','||*(pBuffer+i)=='.'){
            *(pBuffer+i)='.';
            contadorDePuntos++;
            if(contadorDePuntos==2){
                break;
            }
        }else if(*(pBuffer+i)<48||*(pBuffer+i)>57){
                break;
        }
        i++;
    }while (i<strlen(pBuffer));
    if(i==strlen(pBuffer)){
        retorno=0;
    }
    return retorno;
}
/**
*\brief Funcion  que se encarga de tomar datos por consola y valida que la cantidad de caracteres sea -1
        que el limite del array y que el ultimo caracter sea el \n
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string que se tomo por consola
*\param limiteArray es el tamaño del array de caracteres donde se va a almacenar el string
*\return Exito=0 y Error=-1
*/
int getString(char* pBuffer,int limite)
{
    char bufferString[4096];
    int retorno =-1;
    if (pBuffer != NULL && limite >0){
        myFlush();
        fgets(bufferString,sizeof(bufferString),stdin);
        if (bufferString[strlen(bufferString)-1]=='\n'){
            bufferString[strlen(bufferString)-1]='\0';
        }
        if(strlen(bufferString)<= limite){
            strncpy(pBuffer,bufferString,limite);
            retorno=0;
        }
    }
    return retorno;
}
/**
*\brief Funcion estatica que se encarga de tomar datos por consola
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string que se tomo por consola
*\return Exito=0 y Error=-1
*/
static int getFloat(float*pBuffer){
    char bufferString[200];
    int retorno =-1;
    if(getString(bufferString,200)==0 && isFloat(bufferString)==0){
        *pBuffer=atof(bufferString);
        retorno=0;
    }
    return retorno;
}
