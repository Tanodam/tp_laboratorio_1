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
/**
*\brief Funcion generica para solicitar un numero al usuario
*/
static int getInt(int* numeroIngresado)
{
    myFlush();
    return scanf("%d", numeroIngresado);
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
*\brief Ejecuta la aplicacion Calculadora
*\param numeroA= Es la variable donde se va a guardar el numero A ingresado por el usuario. Se inicializa en 0.
*\param numeroB= Es la variable donde se va a guardar el numero B ingresado por el usuario. Se inicializa en 0.
*\param resultadoSuma= Es la variable donde se va a guardar el resultado de la funcion "suma"
*\param resultadoResta= Es la variable donde se va a guardar el resultado de la funcion "resta"
*\param resultadoMultiplicacion= Es la variable donde se va a guardar el resultado de la funcion "multiplicacion"
*\param resultadoCociente= Es la variable donde se va a guardar el resultado de la funcion "cociente"
*\param resultadoFactorialA= Es la variable donde se va a guardar el resultado de la funcion "factorial"
correspondiente al numero A
*\param resultadoFactorialB= Es la variable donde se va a guardar el resultado de la funcion "factorial"
corespondiente al numero B.
*\param respuestaNumerica= Es la variable donde se va a guardar la opcion numerica ingresada por el usuario
*\param flagNumeroA_Ingresado= Es la variable donde se va a guardar el flag que corrobora que el
usuario haya ingresado el primer numero.
*\return 0= Cuando se completo el programa
*
*/
int comienzaCalculadora()
{
    float numeroA=0;
    float numeroB=0;
    float resultadoSuma;
    float resultadoResta;
    float resultadoMultiplicacion;
    float resultadoCociente;
    long resultadoFactorialA;
    long resultadoFactorialB;
    int respuestaNumerica;
    int flagNumeroA_Ingresado=0;

    printf("Bienvenido a Calculadora\nTP LABORATORIO 1\nAlumno: Damian Desario\t Legajo:104327\nCurso: 1°H\n");
    pausarPantalla();
    do
    {
        limpiarPantalla();
        respuestaNumerica=utn_construirMenuNumeros(numeroA, numeroB);// Construye el menu e indica en pantalla los numeros ingresados
        switch(respuestaNumerica)
        {
            case 1:
                numeroA=ingresaOperando('A');//Solicita el numeroA al usuario
                flagNumeroA_Ingresado = 1; //Valida que el usuario ingreso el primer numero y permite usar el CASE 3
                system("clear");
                break;

            case 2:// Solicita el numeroB al usuario
                numeroB=ingresaOperando('B');
                limpiarPantalla();
                break;

            case 3: //Calcula todas las variables
                myFlush();
                if(flagNumeroA_Ingresado!=1) //Valida que el usuario haya ingresado aunque sea el numeroA
                {
                    printf("No puede iniciar el programa sin indicar un numero\n");
                    pausarPantalla();
                    limpiarPantalla();
                    break;
                }
                printf("\nCALCULANDO..\n");
                resultadoSuma=suma(numeroA, numeroB);

                resultadoResta=resta(numeroA, numeroB);
                //printf("b) El resultado de la resta A-B es: %.2f \n", resultado);

                if(numeroB!=0)//Valida que el numberoB sea distinto de CERO para realizar la division
                    {
                        resultadoCociente=cociente(numeroA, numeroB);

                    }
                else //Informa que el divisor es CERO
                    {
                        printf("\nc)NO SE PUDO CALCULAR EL COCIENTE PORQUE EL DIVISOR ES 0.\n");
                    }


                resultadoMultiplicacion=multiplicacion(numeroA, numeroB);
                resultadoFactorialA=factorial(numeroA);
                resultadoFactorialB=factorial(numeroB);
                pausarPantalla();
                limpiarPantalla();
                break;

            case 4: //Informa todos los resultados
                myFlush();
                if(flagNumeroA_Ingresado!=1) //Valida que el usuario haya ingresado aunque sea el numeroA
                {
                    printf("No puede iniciar el programa sin indicar un numero\n");
                    pausarPantalla();
                    limpiarPantalla();
                    break;
                }
                printf("\nA) El resultado de la suma A+B es: %.2f \n", resultadoSuma);
                printf("b) El resultado de la resta A-B es: %.2f \n", resultadoResta);

                if(numeroB!=0)//Valida que el divisor sea distinto de CERO apra mostrar el resultado
                    {
                        printf("c) El resultado del cociente A/B es: %.2f \n", resultadoCociente);
                    }

                printf("d) El resultado del producto A*B es: %.2f \n", resultadoMultiplicacion);
                printf("e) El resultado del factorial de A y B es: A!=%ld y B!=%ld\n", resultadoFactorialA, resultadoFactorialB);
                numeroA=0;
                numeroB=0;
                flagNumeroA_Ingresado=0;
                pausarPantalla();
                limpiarPantalla();
                break;

            case 5:
                break;

        }
        }while(respuestaNumerica!=5);
    return 0;
}
