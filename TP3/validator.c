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
int array_StringFloatEsValido (char* pArray, int limiteArray)
{
    int i=0;
    int retorno = 0;
    int contadorPuntos = 0;


    if(pArray != NULL && limiteArray > 0)
    {
        retorno = 1;
        for(i=0; i < limiteArray && pArray[i] != '\0'; i++)
        {
            switch(pArray[i])
            {
            case 46: //Punto
                if(i==0 || i==(strlen(pArray)-1))
                {
                    retorno = 0;
                    break;
                }
                contadorPuntos++;
                break;
            default:          ///0                 9
                if((pArray[i] < 48 || pArray[i] > 57) || contadorPuntos > 1)
                {
                    retorno = 0;
                }
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
int array_StringIntEsValido(char* array, int size)
{
    int retorno = 0;
    int i;

    if(array != NULL && size > 0)
    {
        retorno = 1;
        for(i=0;i < size && array[i] != '\0';i++)
        {
            if((array[i] < '0') && (array[i] > '9'))
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
*\return Exito=1 y Error=0
*/
int array_StringCharEsValido (char* pArray, int limiteArray)
{
    int retorno=-1;
    int i;
    int indiceEspacio=0;

    if((pArray!= NULL && limiteArray > 0) && (strlen(pArray) > 0))
    {
        retorno = 1;

        for (i=1; i<limiteArray && pArray[i] != '\0'; i++) ///Recorre el array hasta el ultimo caracter ingresado, no incluye el \0
        {
            switch(pArray[i])
            {
            case 39: ///Apostrofe
                break;
            case 45: ///Apostrofe
                break;
            case 32: ///Espacio
                indiceEspacio=i;
                if(indiceEspacio!=0)
                {
                    pArray[indiceEspacio+1]=toupper(pArray[indiceEspacio+1]);
                }
                break;
            default:           ///a                  z
                if((pArray[i] < 97) || (pArray[i] > 122))///Verifica que no haya espacios ni caracteres fuera de rango
                {
                    ///A                   Z
                    if((pArray[i] < 65) || (pArray[i] > 90))
                    {
                        retorno = 0;
                    }
                }
                break;
            }
        }
    }
    return retorno;
}

/**
* \brief Evalua si es un Cuil o Cuit (XX-XXXXXXXX-X)
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 1, si no 0
*
*/
int isValidCuilOrCuit(char *pBuffer, int limite)
{
    int retorno = 0;
    int i;
    if( pBuffer != NULL && limite > 0 && strlen(pBuffer) == 13 &&
            pBuffer[2] == '-' && pBuffer[11] == '-')
    {
        retorno = 1;
        for(i=0; i < limite && pBuffer[i] != '\0'; i++)
        {
            if((pBuffer[i] < '0' || pBuffer[i] > '9') && i!=2 && i!=11)
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Verifica si el string recibido tiene solo letras
 * \param array Es el array para validar su tipo
 * \return 1 si contiene solo ' ' y letras y 0 si no lo es
 *
 */
int array_StringCharEsValidoDos(char* array,int size)
{
    int retorno = 0;
    int i;
    int digitosIngresados;

    digitosIngresados = strlen(array);

    if(array != NULL)
    {
        retorno = 1;
        for(i=0; i < digitosIngresados && array[i] != '\0'; i++)
        {
            if((tolower(array[i]) < 'a' || tolower(array[i]) > 'z') && array[i]!= ' ' && array[i]!= '-')
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
* \brief Evalua si se trata de un entero
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el numero maximo de cifras
* \return En caso de exito retorna 1, si no 0
*
*/
int isValidEntero(char *array, int size)
{
    int retorno = 0;
    int i;

    if(array != NULL && size > 0)
    {
        retorno = 1;
        for(i=0;i < size && array[i] != '\0';i++)
        {
            if((array[i] < '0') && (array[i] > '9'))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
