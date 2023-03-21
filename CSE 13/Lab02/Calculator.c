// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Average(double operand1, double operand2);
double AbsoluteValue(double operand1);
double CelsiusToFahrenheit(double operand1);
double FahrenheitToCelsius(double operand1);
double Tangent(double operand1);
double Round(double operand1);
//add more prototypes here

void CalculatorRun(void) {
    printf("\n\nWelcome to Jerret's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);
    while (1) {
        // Your code here
        char chr;
        //double operand;
        double operand1;
        double operand2;
        double total;
        printf("\nEnter a mathematical operation to perform (*,/,+,-,a,c,f,t,r): ");
        scanf(" %c", &chr);

        if ((chr == ('q'))) {
            break;
        }

        if ((chr == ('*'))) {
            printf("\tEnter the first operand: ");
            scanf(" %lf", &operand1);
            printf("\tEnter the second operand: ");
            scanf(" %lf", &operand2);
            total = Multiply(operand1, operand2);
            printf("\tResult of (%lf * %lf): %lf\n", operand1, operand2, total);
        }

        if ((chr == ('/'))) {
            printf("\tEnter the first operand: ");
            scanf(" %lf", &operand1);
            printf("\tEnter the second operand: ");
            scanf(" %lf", &operand2);
            total = Divide(operand1, operand2);
            if ((total == (0.0))) {
                printf("\tDivide by zero error!");
            } else {
                printf("\tResult of (%lf / %lf): %lf\n", operand1, operand2, total);
            }
        }

        if ((chr == ('+'))) {
            printf("\tEnter the first operand: ");
            scanf(" %lf", &operand1);
            printf("\tEnter the second operand: ");
            scanf(" %lf", &operand2);
            total = Add(operand1, operand2);
            printf("\tResult of (%lf + %lf): %lf\n", operand1, operand2, total);
        }

        if ((chr == ('-'))) {
            printf("\tEnter the first operand: ");
            scanf(" %lf", &operand1);
            printf("\tEnter the second operand: ");
            scanf(" %lf", &operand2);
            total = Subtract(operand1, operand2);
            printf("\tResult of (%lf - %lf): %lf\n", operand1, operand2, total);
        }

        if ((chr == ('a'))) {
            printf("\tEnter the operand: ");
            scanf(" %lf", &operand1);
            total = AbsoluteValue(operand1);
            printf("\tResult of absolute value(%lf): %lf\n", operand1, total);
        }

        if ((chr == ('f'))) {
            printf("\tEnter the operand: ");
            scanf(" %lf", &operand1);
            total = FahrenheitToCelsius(operand1);
            printf("\tResult of fahrenheit to celsius(%lf): %lf\n", operand1, total);
        }

        if ((chr == ('c'))) {
            printf("\tEnter the operand: ");
            scanf(" %lf", &operand1);
            total = CelsiusToFahrenheit(operand1);
            printf("\tResult of celsius to fahrenheit(%lf): %lf\n", operand1, total);
        }

        if ((chr == ('m'))) {
            printf("\tEnter the first operand: ");
            scanf(" %lf", &operand1);
            printf("\tEnter the second operand: ");
            scanf(" %lf", &operand2);
            total = Average(operand1, operand2);
            printf("\tResult of average(%lf and %lf): %lf\n", operand1, operand2, total);
        }

        if ((chr == ('t'))) {
            printf("\tEnter the operand: ");
            scanf(" %lf", &operand1);
            total = Tangent(operand1);
            printf("\tResult of tangent(%lf): %lf\n", operand1, total);
        }
    }
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return (operand1 + operand2);
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return (operand1 - operand2);
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return (operand1 * operand2);
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    if ((operand2 == (0.0))) {
        return 0.0;
    } else {
        return (operand1 / operand2);
    }
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand1) {
    return (abs(operand1));
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand1) {
    return ((operand1 - 32) * 5 / 9);
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand1) {
    return (operand1 * 9 / 5 + 32);
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    return ((operand1 + operand2) / 2);
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand1) {
    double Radians = (operand1 * 3.14159265358979 / 180);
    return (tan(Radians));
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/