//
//  fv_106.c
//  handbook
//
//  Created by Abhishek Bansal on 03/04/13.
//
//
// personal finance calculations

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* function prototypes */
void table (double (*pf)(double i, int m, double n), double a, int m, double n);
double md1(double i, int m, double n);
double md2(double i, int m, double n);
double md3(double i, int m, double n);

main() /*calculate the future value of a series of monthly deposits */
{
    int m; /* number of compounding periods per year */
    double n; /* number of years */
    double a; /* amount of each monthly payment */
    char freq; /* frequency of compounding indicator */
    
    /* enter the input data */
    printf("\nFUTURE VALUE OF A SERIES OF MONTHLY DEPOSITS\n\n");
    printf("Amount of each monthly payment: ");
    scanf("%lf", &a);
    printf("Number of Years: ");
    scanf("%lf", &n);
    
    /* enter frequency of counting */
    do {
        printf("Frequency of Compounding (A, S, Q, M, D, C): ");
        scanf("%1s", &freq);
        freq = toupper(freq); /* convert to upper case */
        
        if (freq == 'A') {
            m = 1;
            printf("\nAnnual Compounding\n");
        }
        else if (freq == 'S')   {
            m = 2;
            printf("\nSemiannual Compounding\n");
        }
        else if (freq == 'Q')   {
            m = 4;
            printf("\nQuarterly Compounding");
        }
        else if (freq == 'M')   {
            m = 12;
            printf("\nMonthly Compounding\n");
        }
        else if (freq == 'D')   {
            printf("\nDaily Compounding\n");
        }
        else if (freq == 'C')   {
            printf("\nConntinous Compounding\n");
        }
        else    {
            printf("\nERROR - Please Repeat\n\n");
        }
    } while (freq != 'A' && freq != 'S' && freq != 'Q' &&
             freq != 'M' && freq != 'D' && freq != 'C');
    /* carry out the calculations */
    if (freq == 'C')            /* continous compounding */
        table(md3, a, m, n);
    else if (freq == 'D')       /* daily compounding */
        table(md2, a, m, n);
    else
        table(md1, a, m, n);    /* annual, semiannual, quarterly or monthly compounding */
        
}

void table (double (*pf)(double i, int m, double n), double a, int m, double n)
/* table generator (this function accepts a pointer to another function as an argument) 
    
    NOTE: double (*pf)(double i, int m, double n) is a POINTER TO A FUNCTION */
{
    int count;      /* loop counter */
    double i;       /* annual interest rate */
    double f;       /* future value */
    
    printf("\nInterest  Rate    Future Amount\n\n");
    for (count = 1; count <= 20; ++count)   {
        i = 0.01 * count;
        f = a * (*pf)(i, m, n);     /* ACCESS THE FUNCTION PASSED AS POINTER */
        printf("    %2d                 %.2f\n", count, f);
    }
    return;
    
}

double md1(double i, int m, double n)
/* monthly deposits, periodic compounding */

{
    double factor, ratio;
    
    factor = 1 + i/m;
    ratio = 12 * (pow(factor, m*n)-1)/i;
    return ratio;
}

double md2(double i, int m, double n)
/* monthly deposits, daily compounding */
{
    double factor, ratio;
    factor = 1 + i/m;
    ratio = (pow(factor, m*n)-1)/(pow(factor, m/12)-1);
    return ratio;
}

double md3(double i, int m, double n)
/* monthly deposits, continous compounding */
{
    double ratio;
    
    ratio = (exp(i*n)-1)/(exp(i/12)-1);
    return ratio;
}