#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include "utn.h"
#include <stdio.h>


/**
*\brief Funcion generica para Windows/Linux para limpiar el buffer de entrada
*/
void myFlush()
{
    fflush(stdin);//Para Windows
    __fpurge(stdin);//Para Linux
}

static int getInt(int* numeroIngresado)
{
    myFlush();
    return scanf("%d", numeroIngresado);
}

static int getChar(char* caracterIngresado)
{
    myFlush();
    return scanf("%c", caracterIngresado);
}

////static int getFloat(float* numeroIngresado)
//{
//    myFlush();
//    return scanf("%f", numeroIngresado);
//}
//
////static int getString(int* textoIngresado)
//{
//    myFlush();
//    return scanf("%d", textoIngresado);
//}

/**
*\brief Solicita un número al usuario, lo valida y devuelve el resultado
*\param pResultado Puntero a la variable resultado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param minimo es el numero minimo aceptado
*\param maximo es el numero maximo aceptado
*\param reintentos es el numero maximo de reintentos aceptados
*\return Exito=0 y Error=1
*
*/
int utn_getNumero(  int* pResultado,
                    char mensaje[],
                    char mensajeError[],
                    int minimo,
                    int maximo,
                    int reintentos)
{
    int numero;
    int i;

    for(i=0;i<reintentos;i++)
    {
        printf("%s", mensaje);
        myFlush();
        while(getInt(&numero)!=1)
        {

            break;
        }

        if(numero>=minimo && numero<=maximo)
        {
            *pResultado=numero;
            return 0;
        }
        else
        {
            printf("%s", mensajeError);

        }
    }
    printf("Usted ha superado la cantidad de reintentos permitidos");
    return -1;
}

/**
*\brief Solicita un caracter al usuario, lo valida y devuelve el resultado
*\param pResultado Puntero a la variable resultado
*\param mensaje[] es el mensaje que se le va a mostrar al usuario
*\param mensajeError[] es el mensaje que se le va a mostrar al usuario si hay un error en la carga de datos
*\param minimo es el caracter minimo aceptado
*\param maximo es el caracter maximo aceptado
*\param reintentos es el numero maximo de reintentos aceptados
*\return Exito=0 y Error=1
*
*/
int utn_getCaracter(    char* pResultado,
                        char mensaje[],
                        char mensajeError[],
                        char minimo,
                        char maximo,
                        int reintentos)
{
    char caracter;
    int i;

    for(i=0;i<reintentos;i++)
    {
        printf("%s", mensaje);
        myFlush();
        while(getChar(&caracter)!=1)
        {
            //myFlush();
            break;
        }

        if(caracter>=minimo && caracter<=maximo)
        {
            *pResultado=caracter;
            return 0;
        }
        else
        {
            printf("%s", mensajeError);

        }
    }
    return -1;
}
/**
*\brief Construye el menu principal de la Calculadora y valida la opcion seleccionada
*\param Valor de la variable asignada a numeroA para mostrarla en pantalla.
*\param Valor de la variable asignada a numeroB para mostrarla en pantalla.
*\return Exito=0 Devuelve la opcion ingresada y validada Error=5 Devuelve 5 porque es el case de Salida del programa.
*
*/
int utn_construirMenuNumeros(float numeroA, float numeroB)
{
        int respuesta;
        printf("1. Ingresar primer operando (A=%.2f) \n", numeroA);
        printf("2. Ingresar segundo operando (B=%.2f) \n", numeroB);
        printf("3. Calcular todas las operaciones \n");
        printf("4. Informar resultados \n");
        printf("5. Salir\n");
        myFlush();
        if(utn_getNumero(&respuesta,"Ingrese la opcion deseada (1-5):","\nERROR, intente nuevamente\n",1,5,3)!=0)
        {
            return 5;
        }

        return respuesta;
}
/**
*\brief Construye el menu principal de las opciones de los operandos y valida la opcion seleccionada
*\return Retorna el valor de la opcion seleccionada para pasarsela al switch
*/
//char utn_construirMenuLetras()
//{
//        char respuesta;
//        printf("a) Calcular la suma (A+B) \n");
//        printf("b) Calcular la resta (A-B) \n");
//        printf("c) Calcular el cociente (A/B) \n");
//        printf("d) Calcular la multiplicaci""\xe0""n (A*B) \n");
//        printf("e) Calcular el factorial (A!) \n");
//        printf("f) Salir \n");
//        myFlush();
//        if(utn_getCaracter(&respuesta,"\nIngrese una opcion\t","\nERROR, Intente de nuevo\n", 'a','f',3)!=0)
//        {
//            limpiarPantalla();
//            return 'f';
//
//        }
//
//        return respuesta;
//}
/**
*\brief Realiza la suma de los numeros A y B.
*\param Recibe el valor de la variable A
*\param Recibe el valor de la variable B
*\return Retorna el valor de la suma entre A y B
*/
float suma (float numeroA, float numeroB)
{

    float resultado;

    resultado=numeroA+numeroB;
    return resultado;
}
/**
*\brief Realiza la resta de los numeros A y B.
*\param Recibe el valor de la variable A
*\param Recibe el valor de la variable B
*\return Retorna el valor de la resta entre A y B
*/
float resta (float numeroA, float numeroB)
{
    float resultado;

    resultado=numeroA-numeroB;
    return resultado;
}
/**
*\brief Realiza el cociente de los numeros A y B.
*\param Recibe el valor de la variable A
*\param Recibe el valor de la variable B
*\return Retorna el cociente entre A y B
*/
float cociente (float numeroA, float numeroB)
{
    float resultado;

    resultado=numeroA/numeroB;
    return resultado;

}
/**
*\brief Realiza la multiplicacion de los numeros A y B.
*\param Recibe el valor de la variable A
*\param Recibe el valor de la variable B
*\return Retorna el producto entre A y B
*/
float multiplicacion (float numeroA, float numeroB)
{
    float resultado;

    resultado=numeroA*numeroB;
    return resultado;
}
/**
*\brief Realiza el cociente de los numeros A y B.
*\param Recibe el valor de la variable A
*\param Recibe el valor de la variable B
*\return Retorna el cociente entre A y B
*/
long factorial(int numero)
{
   long resultado;
   int i;
   long factorial=1;
   if(numero==1 || numero==0)
    {
        return 1;
    }
   else
   {
        for(i=1;i<=numero;i++)
        {
            factorial=factorial*i;
            resultado=factorial;
        }
   }
   return resultado;
}
/**
*\brief Le solicita un numero al usuario y valida que sea un numero
*\param Rebibe el identificador del Operando para mostrarlo en pantalla durante la carga.
*\return Retorna el numero ingresado
*/
float ingresaOperando(char identificadorOperando)
{
    float operando=0.0;
    printf("\nIngrese el operando %c: ", identificadorOperando);
    myFlush();
    while(scanf("%f", &operando)!=1 )
    {
        printf("\nError el dato ingresado no es un numero\n");
        pausarPantalla();
        limpiarPantalla();
        break;
    }
    return operando;
}
/**
*\brief Funcion que limpia la pantalla de la consola.
*/
void limpiarPantalla()
{
    //system("cls");
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
