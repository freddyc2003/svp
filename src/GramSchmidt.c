#include "GramSchmidt.h"
#include "VectorOperations.h"

void GramSchmidt(double **b, double **u, double **mu, int n)
{
    for (int i = 0; i < n; i++)
    {
        u[0][i] = b[0][i];
    }

    for (int i = 1; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            u[i][k] = b[i][k];
        }

        for (int j = i - 1; j >= 0; j--)
        {
            mu[i][j] = InnerProduct(b[i], u[j], n) / Norm(u[j], n);

            for (int k = 0; k < n; k++)
            {
                u[i][k] -= mu[i][j] * u[j][k];
            }
        }
    }
}