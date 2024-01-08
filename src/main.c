#include <stdio.h>
#include <stdlib.h>
#include "GramSchmidt.h"

int main()
{
    int n = 3;

    double **basis = (double **)malloc(n * sizeof(double *));

    if (basis == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        basis[i] = (double *)malloc(n * sizeof(double));

        if (basis[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

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

    // basis[0][0] = 3;
    // basis[0][1] = 1;
    // basis[1][0] = 2;
    // basis[1][1] = 2;

    basis[0][0] = 4;
    basis[0][1] = 1;
    basis[0][2] = 2;
    basis[1][0] = 4;
    basis[1][1] = 7;
    basis[1][2] = 2;
    basis[2][0] = 3;
    basis[2][1] = 1;
    basis[2][2] = 7;

    GramSchmidt(basis, u, mu, n);

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
