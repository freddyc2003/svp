#include <math.h>
#include "GramSchmidt.h"
#include "VectorOperations.h"

void LLL(double **B, double **u, double **mu, int delta, int N)
{
    GramSchmidt(B, u, mu, N);

    int k = 1;

    while (k < N)
    {
        for (int j = k - 1; j >= 0; j--)
        {
            if (fabs(mu[k][j]) > 0.5)
            {
                for (int i = 0; i < N; i++)
                {
                    B[k][i] -= B[j][i] * round(mu[k][j]);
                }

                GramSchmidt(B, u, mu, N);
            }
        }

        if (Norm(u[k], N) >= (delta - pow(mu[k][k - 1], 2)) * Norm(u[k - 1], N))
        {
            k += 1;
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                double temp = B[k][i];

                B[k][i] = B[k - 1][i];
                B[k - 1][i] = temp;
            }

            GramSchmidt(B, u, mu, N);

            k = fmax(k - 1, 1);
        }
    }
}
