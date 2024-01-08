#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double **ParseArguments(int argc, char **argv, int n)
{
    double **basis = (double **)malloc(n * sizeof(double *));

    if (basis == NULL)
    {
        printf("Memory allocation failed.\n");
    }

    for (int i = 0; i < n; i++)
    {
        basis[i] = (double *)malloc(n * sizeof(double));

        if (basis[i] == NULL)
        {
            printf("Memory allocation failed.\n");
        }
    }

    int vector = 0;
    int c = 0;

    for (int i = 1; i < argc; i++)
    {
        char *argument = argv[i];

        // printf("Argument %d (before): %s\n", i, argument);

        int k = 0;

        for (int j = 0; argument[j] != '\0'; j++)
        {
            if (argument[j] != '[' && argument[j] != ']')
            {
                argument[k] = argument[j];
                k++;
            }
        }

        argument[k] = '\0';

        // printf("Argument %d (after): %s\n", i, argument);

        double result = strtod(argument, NULL);

        // printf("Converted value: %lf\n", result);

        basis[vector][c] = result;

        c += 1;

        // printf("basis[%d][%d] \n", vector, c);

        if (c == n)
        {
            vector += 1;
            c = 0;
        }
    }

    return basis;
}
