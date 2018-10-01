#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "string.h"
#include "ctype.h"
#include "utn.h"


/**
*\brief [Funcion interna de GetMail] Valida que el usuario haya ingresado un mail correcto
*\param pArray Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=1 y Error=-0
*/
int array_StringMailEsValido (char* pArray, int limiteArray)
{
    int retorno = 0;
    int i;
    int indexArroba = 0, indexPunto = 0;
    int contadorArroba=0;

    if(pArray!= NULL && limiteArray > 0)
    {
        retorno = 1;
        for (i=0; i<strlen(pArray)-1; i++)
        {
///Valida que en ninguna parte del array haya espacios
            if (pArray[i] == ' ')
            {
                retorno = 0;
                break;
            }
///Valida que antes del arroba haya solo letras, numeros, punto(.), guion alto(-) y guion bajo(_)
            if (indexArroba == 0 && (pArray[i] < 'a' || pArray[i] > 'z') &&
                (pArray[i] < '0' || pArray[i] > '9') && (pArray[i] != '.' && pArray[i] == '-' && pArray[i] == '_'))
                {
                    retorno = 0;
                    break;
                }
///Valida que el usuario ingrese el arroba
            if (pArray[i] == '@')
            {
                contadorArroba++;
                if (indexArroba == 0 && contadorArroba==1) ///Guarda el indice para saber que el usuario esta ingresando el dominio y verifica que no haya mas de un arroba
                {
                    indexArroba = i;
                }
                else
                {
                    retorno = 0;
                    break;
                }
            }
///Valida que despues del arroba en el primer indice solo haya caracteres alfabeticos
            if (pArray[i-1] == '@' && (pArray[i] < 'a' || pArray[i] > 'z'))
            {
                retorno = 0;
                break;
            }
///Valida que despues del arroba haya almenos un punto
            if (pArray[i] == '.' && indexArroba != 0)
            {
                indexPunto = i;
            }
///Valida todo lo que esta entre el arroba y el primer punto
            if (indexArroba != 0 && indexPunto == 0 && pArray[i] != '@')
            {
                if ((pArray[i] < 'a' || pArray[i] > 'z') && (pArray[i] < '0' || pArray[i] > '9'))
                {
                    retorno = 0;
                    break;
                }
            }
///Valida que en el dominio haya solos caracteres alfabeticos
            if (indexArroba != 0 && indexPunto != 0 && pArray[i] != '.')
            {
                if (pArray[i] < 'a' || pArray[i] > 'z')
                {
                    retorno = 0;
                    break;
                }
                else
                {
                    retorno = 1;
                }
            }
///Valida que en el ultimo indice solo haya caracteres alfabeticos
            if (i==strlen(pArray)-2 && (pArray[i] < 'a' || pArray[i] > 'z'))
            {
                retorno = 0;
                break;
            }
///Valida que se hayan escritos el arroba y el punto del dominio
            if (indexArroba == 0 || indexPunto == 0)
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetStringFloat] Valida que el usuario solo haya ingresado caracteres del 0 al 9
*\param pArray Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=0 y Error=-1
*/
int array_StringFloatEsValido (char* pArray, int limiteArray)
{
    int retorno = 0;
    int i;
    int indexPuntos=0;
    int contadorPuntos=0;

    if  ((pArray != NULL && limiteArray > 0 && strlen(pArray) > 0) &&
        (( pArray[0] == '+' && pArray[1] != '.') || (pArray[0]>='0' && pArray[0]<='9')))
    {
        retorno = 1;
        for (i=1; i < limiteArray && pArray[i] != '\0'; i++) ///Recorre el array hasta el ultimo caracter ingresado, no incluye el \0
            {
                if(pArray[i]=='.')
                {
                    contadorPuntos++;
                }
                if((pArray[i]<'0' && pArray[i]>'9') || contadorPuntos >1)
                {
                    retorno = 0;
                    break;
                }
            }
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetStringFloat] Valida que el usuario solo haya ingresado caracteres del 0 al 9
*\param pArray Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=0 y Error=-1
*/
int array_StringIntEsValido(char* pArray, int limiteArray)
{
    int retorno = 0;
    int i;


    if  ((pArray != NULL && limiteArray > 0 && strlen(pArray) > 0))
    {
        retorno = 1;
        for (i=1; i < limiteArray && pArray[i] != '\0'; i++) ///Recorre el array hasta el ultimo caracter ingresado, no incluye el \0
            {
                if(!(pArray[i] >= '0' || pArray[i] <= '9'))
                {
                    retorno = 0;
                    break;
                }
            }
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetStringChar] Valida que el usuario solo haya ingresado caracteres de la A a la Z
*\param pArray Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=1 y Error=-0
*/
int array_StringCharEsValido (char* pArray, int limiteArray)
{
    int retorno=-1;
    int i;

    if((pArray!= NULL && limiteArray > 0) && (strlen(pArray) > 0))
    {
        retorno = 1;

        for (i=0; i<strlen(pArray)-1; i++) ///Recorre el array hasta el ultimo caracter ingresado, no incluye el \0
            {
                if(pArray[i] == ' ' || (pArray[i] < 'a' || pArray[i] > 'z')) ///Verifica que no haya espacios ni caracteres fuera de rango
                {
                    retorno = 0;
                    break;
                }
            }
    }
    return retorno;
}
/**
*\brief [Funcion interna de GetStringInt] Valida que el usuario solo haya ingresado caracteres del 0 al 9
*\param pArray Puntero a la direccion de memoria donde esta almacenada el string a validar
*\param limiteArray tamaño del array
*\return Exito=0 y Error=-1
*/
char array_StringTelefonoEsValido (char* pArray, int limiteArray)
{
    int retorno=0;
    int i;
    int contadorGuiones=0;

    for (i=0; i<strlen(pArray)-1; i++) ///Recorre el array hasta el ultimo caracter ingresado, no incluye el \0
        {
            retorno = 1;
            if(pArray[i] == '-')
            {
                contadorGuiones++;
            }
            if(pArray[i]!= '-' && (pArray[i] == ' ' || pArray[i] == '.') &&
               (pArray[i] < '0' || pArray[i] > '9'))
            {
                retorno = 0;
                break;
            }
            if(contadorGuiones>=1 || contadorGuiones<=2)
            {
                retorno = 1;
                break;
            }
            else
            {
                printf("Faltan guiones\n");
            }

        }
        return retorno;
}
