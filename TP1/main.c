#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "utn.h"

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
*\return
*
*/
int main()
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
