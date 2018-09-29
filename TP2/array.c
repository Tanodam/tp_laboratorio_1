#include <stdio_ext.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#include "utn.h"
#include "array.h"
#include "validator.h"
#include "arrayEmployees.h"

#define BUFFER_STR 4097
static int getString (char* pArray, int limiteaArray);


/**
*\brief Funcion generica para Windows/Linux para limpiar el buffer de entrada
*/
void myFlush()
{
    __fpurge(stdin);//Para Linux
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
    //system("pause"); //Para Windows
    printf("Presione ENTER para continuar");
    myFlush();
    getchar();

}
static int getString (char* pArray, int limiteaArray)
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
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringCharEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string validado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
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
                myFlush();

                for(i=0;i<limiteArray;i++)
                {
                    myFlush();
                    buffer[i]=tolower(buffer[i]); //Convierto todos los caracteres del array a minusculas para validarlos
                }
                if(array_StringCharEsValido(buffer, limiteArray)&& strlen(buffer)!=0) ///Valido los caracteres, si se cumple 1 y si no
                {
                    myFlush();
                    buffer[0]=toupper(buffer[0]); ///Convierto a mayusculas el primer caracter.
                    strncpy(pArray,buffer,limiteArray);///Copio en el puntero a pArray el valor de string
                    myFlush();
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
        }while(contadorIntentos <= reintentos);
    }

    return retorno;
}
/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringCharEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string validado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
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
        }while(contadorIntentos <= reintentos);
    }

    return retorno;
}

/**
*\brief Solicita string al usuario y lo devuelve validado mediante la funcion StringCharEsValido.
*\param pArray Puntero a la direccion de memoria donde se va almacenar el string validado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\return Exito=0 y Error=1
*
*/
char array_getTelefono(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos)
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
                myFlush();
                if(array_StringTelefonoEsValido(buffer, limiteArray)==1) ///Valido los caracteres, si se cumple 1 y si no
                {
                    strncpy(pArray,buffer,limiteArray); ///Copio en el puntero a pArray el valor de string
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
        }while(contadorIntentos <= reintentos);
    }

    return retorno;
}
char array_getStringFloat(char* pArray, int limiteArray, char* mensaje, char* mensajeError, int reintentos)
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
            if(getString(buffer,limiteArray)==0)
            {
                if(array_StringFloatEsValido(buffer, limiteArray)==1)
                {
                    strncpy(pArray,buffer,limiteArray);
                    retorno = 0;

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
        }while(contadorIntentos <= reintentos);
    }

    return retorno;
}
int array_mostrar(int* pArray, int limiteArray)
{
    int i;
    for(i=0;i<limiteArray;i++)
    {
        printf("\nIndex:%d - Value:%d - Add: %p",i,pArray[i],&pArray[i]);
    }
    return 0;
}
int array_calcularMaximo(int* pArray, int limiteArray, int* pMaximo)
{

    int retorno=-1;
    int i;
    int maximo;
    int flagPrimerMaximo = false;

    if(pArray != NULL && limiteArray > 0)
    {

        for(i=0;i<limiteArray;i++)
        {
            if(pArray[i] != DATO_INVALIDO)
            {
                if(flagPrimerMaximo == false)
                {
                    maximo = pArray[i];
                    flagPrimerMaximo = true;
                }
                else if(pArray[i] > maximo)
                {
                    maximo = pArray[i];
                }
            }
        }

        if(flagPrimerMaximo == 0)
        {
            retorno = -2;
        }
        else
        {
            retorno = 0;
        }
    }
    return retorno;
}
int array_init(int* pArray, int limiteArray, int valor)
{
    int retorno=-1;
    int i;

    if(pArray != NULL && limiteArray > 0)
    {
        for(i=0;i<limiteArray;i++)
        {
            pArray[i] = valor;
        }
        retorno = 0;
    }
    return retorno;
}
void array_swap(int* elementoA, int*elementoB)
{
    int auxiliar;
    auxiliar= *elementoA;
    *elementoA= *elementoB;
    *elementoB=auxiliar;

}
void array_ordenarArray(int* pArray, int limiteArray, int orden)
{
    int i;
    //int auxiliar;
    int continuar = 1;

    while(continuar)
    {
        continuar = 0;
        for (i = 1; i < limiteArray; i++)
        {
            if (pArray[i] < pArray[i - 1] && orden==0)
            {
                array_swap(&pArray[i], &pArray[i-1]);
//                auxiliar = pArray[i];
//                pArray[i] = pArray[i - 1];
//                pArray[i - 1] = auxiliar;
                continuar = 1;
            }
            else if (pArray[i] > pArray[i - 1] && orden==1)
            {
                array_swap(&pArray[i], &pArray[i-1]);
//                auxiliar = pArray[i];
//                pArray[i] = pArray[i - 1];
//                pArray[i - 1] = auxiliar;
                continuar = 1;
            }
        }
    }
}
void array_imprimirIntArray(int* pArray, int limiteArray)
{
	int i;
	for(i = 0; i < limiteArray; i++)
	{
	    printf("\n%d",pArray[i]);
	}
}
int array_ordenarArrayInsercion(int* pArray, int limiteArray)
{
	int i;
	int j;
	int auxiliar;

	for(i = 1; i < limiteArray; i++)
	{
		auxiliar = pArray[i];
		j = i;
		while(j > 0 && auxiliar > pArray[j - 1]) //Cambiar simbolo entre auxilar - pArray para cambiar orden
		{
			pArray[j] = pArray[j - 1];
			j--;
		}
		pArray[j] = auxiliar;
	}
	return 0;
}
