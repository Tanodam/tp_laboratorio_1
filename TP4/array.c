#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#include "utn.h"
#include "array.h"
#include "validator.h"
#define BUFFER_STR 4097

static int getString (char* pArray, int limiteaArray);
/**
*\brief Funcion estatica que se encarga de tomar datos por consola y valida que la cantidad de caracteres sea -1
        que el limite del array y que el ultimo caracter sea el \n
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string que se tomo por consola
*\param limiteArray es el tamaño del array de caracteres donde se va a almacenar el string
*\return Exito=0 y Error=-1
*/
int static getString (char* pArray, int limiteaArray)
{
    int retorno = -1;
    char buffer[BUFFER_STR];
    int len;
    if(pArray!=NULL && limiteaArray > 0)
    {
        myFlush();
        fgets(buffer, limiteaArray,stdin);
        len=strlen(buffer);
        if(len != limiteaArray-1 || buffer[limiteaArray-2]=='\n')
        {
            buffer[len-1] = '\0';
        }
        retorno = 0;
        strncpy(pArray,buffer,limiteaArray);
    }
    return retorno;

}
/**
*\brief Funcion generica para Windows/Linux para limpiar el buffer de entrada
*/
void myFlush()
{
    __fpurge(stdin);
}
/**
*\brief Funcion que limpia la pantalla de la consola.
*/
void limpiarPantalla()
{
    system("clear");
}
/**
*\brief Funcion que pausa la consola para que el usuario pueda leer.
*/
void pausarPantalla()
{
    printf("Presione ENTER para continuar");
    myFlush();
    getchar();
}
/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringCharEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string validado
*\param limiteArray es el tamaño del array de caracteres donde se va a almacenar el string
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param reintentos cantidad de intentos que tiene disponibles el usuario
*\return Exito=0 y Error=1
*
*/
char array_getNombre(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos)
{
    int i;
    int retorno=-1;
    int contadorIntentos=0;
    char buffer[BUFFER_STR];

    if(pArray != NULL && limiteArray > 0)
    {
        do
        {
            printf("%s", mensaje);
            contadorIntentos++;
            myFlush();
            if(!getString(buffer,limiteArray))
            {
                retorno = 0;
                for(i=0; i<limiteArray; i++)
                {
                    myFlush();
                    buffer[i]=tolower(buffer[i]); //Convierto todos los caracteres del array a minusculas para validarlos
                }
                if(array_StringCharEsValido(buffer, limiteArray) && strlen(buffer)!=0) ///Valido los caracteres, si se cumple 1 y si no
                {
                    myFlush();
                    buffer[0]=toupper(buffer[0]); ///Convierto a mayusculas el primer caracter.
                    strncpy(pArray,buffer,limiteArray);///Copio en el puntero a pArray el valor de string
                    myFlush();
                    break;
                }
                else
                {
                    printf("%s\n", mensajeError);
                    if(contadorIntentos==reintentos)
                    {
                        printf("\nSe han superado los intenos maximos permitidos");
                        retorno = -1;
                        break;
                    }
                }
            }
        }
        while(contadorIntentos <= reintentos);
    }

    return retorno;
}
/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringMailEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string validado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param reintentos cantidad de intentos que tiene disponibles el usuario
*\return Exito=0 y Error=1
*
*/
char array_getMail(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos)
{
    int retorno=-1;
    int contadorIntentos=0;
    char buffer[BUFFER_STR];

    if(pArray != NULL && limiteArray > 0)
    {
        do
        {
            printf("%s", mensaje);
            contadorIntentos++;
            if(getString(buffer,limiteArray)==0)
            {
                if(array_StringMailEsValido(buffer, limiteArray)==1)
                {
                    strncpy(pArray,buffer,limiteArray);
                    retorno = 0;
                    break;
                }
                else
                {
                    printf("%s", mensajeError);
                    if(contadorIntentos==reintentos)
                    {
                        printf("\nSe han superado los intenos maximos permitidos");
                        retorno = -1;
                        break;
                    }
                }

            }
        }
        while(contadorIntentos <= reintentos);
    }

    return retorno;
}
/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringFloarEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el float validado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param reintentos cantidad de intentos que tiene disponibles el usuario
*\return Exito=0 y Error=1
*
*/
int array_getStringFloat(float* pArray, int limiteArray,int minimo, int maximo, char* mensaje, char* mensajeError, int reintentos)
{
    int retorno= -1;
    int contadorIntentos= 0;
    char buffer[BUFFER_STR];

    if(pArray != NULL && limiteArray > 0)
    {
        do
        {
            printf("%s", mensaje);
            contadorIntentos++;
            if(!getString(buffer,limiteArray)&&
                    (array_StringFloatEsValido(buffer, limiteArray)) &&
                    (atoi(buffer)<=maximo && atoi(buffer)>=minimo))
            {
                *pArray=atof(buffer);
                retorno = 0;
                break;



            }
            else
            {
                printf("%s", mensajeError);
                if(contadorIntentos==reintentos)
                {
                    printf("\nSe han superado los intenos maximos permitidos");
                    retorno = -1;
                    break;


                }
            }

        }
        while(contadorIntentos <= reintentos);
    }

    return retorno;
}
/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringIntEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el float validado.
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param reintentos cantidad de intentos que tiene disponibles el usuario
*\return Exito=0 y Error=1
*
*/
int array_getStringInt(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos)
{
    int retorno= -1;
    int contadorIntentos= 0;
    char buffer[BUFFER_STR];

    if(pArray != NULL && limiteArray > 0)
    {
        do
        {
            printf("%s", mensaje);
            contadorIntentos++;
            if(!getString(buffer,limiteArray) && array_StringIntEsValido(buffer, limiteArray))
            {
                strncpy(pArray,buffer,limiteArray);
                retorno = 0;
                break;
            }
            else
            {
                printf("%s", mensajeError);
                if(contadorIntentos==reintentos)
                {
                    printf("\nSe han superado los intenos maximos permitidos");
                    retorno= 0;
                    break;
                }
            }

        }
        while(contadorIntentos <= reintentos);
    }

    return retorno;
}
/**
* \brief Toma una cadena y evalua si es un Cuil o Cuit (XX-XXXXXXXX-X)
* \param pDocumento Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \param mensaje Es el mensaje que se muestra al usuario antes de introducir datos
* \param mensajeError Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*
*/
int array_getCuilOrCuit(  char *pDocumento, int limite, char *mensaje,
                          char *mensajeError, int reintentos)
{
    int retorno=-1;
    char buffer[4096];
    if( pDocumento != NULL && limite > 0 && mensaje != NULL &&
            mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("%s", mensaje);
            if( getString(buffer, limite) == 0 &&
                    isValidCuilOrCuit(buffer, limite))
            {
                strncpy(pDocumento, buffer, limite);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }
        while(reintentos>=0);
    }
    return retorno;
}
/**
 * \brief Solicita un texto al usuario y lo devuelve
 * \param mensaje Es el mensaje a ser mostrado
 * \param input Array donde se cargará el texto ingresado
 * \return void
 */
int array_getStringAll(char* input,int limiteArray, char* mensaje)
{
    int retorno = -1;
    char buffer[limiteArray];
    int length;

    do
    {
        myFlush();
        printf("%s",mensaje);
        fgets(buffer,limiteArray,stdin);//Se pide el dato limitado por el tamaño del array, parametro 'limiteArray'

        length = strlen(buffer);
        if(length != limiteArray-1 || buffer[limiteArray-2] == '\n')
        {
            buffer[length-1] = '\0';
            retorno = 0;
        }
        strncpy(input,buffer,limiteArray);

    }
    while(input == NULL && limiteArray < 0);

    return retorno;
}
/**
 * \brief Solicita un texto al usuario y lo devuelve
 * \param input Array donde se cargará el texto ingresado
 * \param mensaje Es el mensaje a ser mostrado
 * \param msjError Es el mensaje de error a ser mostrado
 * \return Retorna 0 si se pudo pedir y validar string si no retorna error
 */
int array_getLetras(char* pArray,int limiteArray,char* mensaje,char* msjError,int reintentos)
{
    char buffer[limiteArray];
    int retorno = -1;

    if(pArray != NULL && limiteArray > 0 && mensaje != NULL &&
            msjError != NULL && reintentos >= 0)
    {
        do
        {
            reintentos--;
            printf("%s",mensaje);
            if(getString(buffer,limiteArray) == 0 && array_StringCharEsValidoDos(buffer,limiteArray))
            {
                strncpy(pArray,buffer,limiteArray);//Se copia string cargado a variable local
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",msjError);
            }
        }
        while(reintentos >= 0);
    }
    return retorno;
}
int ingresoTeclado(char* mensaje, char* msjError, char* bufferCampo, int limiteArray, int (*validacionCampo)(char*), int reintentos)
{
    int retorno = -1;
    int contadorIntentos = 0;

    if(limiteArray > 0)
    {
        do
        {
            reintentos--;
            printf("%s", mensaje);
            contadorIntentos++;
            myFlush();
            if(!getString(bufferCampo,limiteArray))
            {
                if((*validacionCampo)(bufferCampo))
                {
                    retorno = 0;
                    break;
                }
                    else
                {
                    printf("%s", msjError);
                    if(contadorIntentos==reintentos)
                    {
                        printf("\nSe han superado los intenos maximos permitidos");
                        retorno = -1;
                        break;
                    }
                }
            }
        }
        while(contadorIntentos <= reintentos);
    }

    return retorno;
}



