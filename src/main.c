#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "LLL.h"
#include "GramSchmidt.h"
#include "Enumeration.h"
#include "ParseArguments.h"

int main(int argc, char *argv[])
{
    int n;

    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "]") != NULL)
        {
            n = i;
            break;
        }
    }

    double **basis = ParseArguments(argc, argv, n);

    double **u = (double **)malloc(n * sizeof(double *));

    if (u == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        u[i] = (double *)malloc(n * sizeof(double));

        if (u[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    double **mu = (double **)malloc(n * sizeof(double *));

    if (mu == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        mu[i] = (double *)malloc(n * sizeof(double));

        if (mu[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    LLL(basis, u, mu, 0.75, n);

    GramSchmidt(basis, u, mu, n);

    double result;

    result = Enumeration(u, mu, 100000000000000000, n);

    printf("%lf \n", sqrt(result));

    for (int i = 0; i < n; i++)
    {
        free(basis[i]);
    }
    free(basis);

    for (int i = 0; i < n; i++)
    {
        free(u[i]);
    }
    free(u);

    for (int i = 0; i < n; i++)
    {
        free(mu[i]);
    }
    free(mu);

    return 0;
}
