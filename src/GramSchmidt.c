#include <stdio.h>
#include "GramSchmidt.h"
#include "VectorOperations.h"

void GramSchmidt(double **B, double **u, double **mu, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int l = 0; l < N; l++)
        {
            u[i][l] = (double)B[i][l];
            mu[i][l] = 0;
        }

        for (int k = 0; k < i; k++)
        {
            mu[i][k] = InnerProduct(B[i], u[k], N) / Norm(u[k], N);

            for (int j = 0; j < N; j++)
            {
                u[i][j] -= mu[i][k] * u[k][j];
            }
        }
    }
}
