#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "VectorOperations.h"

double Enumeration(double **u, double **mu, double R, int n)
{
    double R_SQUARED = pow(R, 2);

    double *p = (double *)calloc((n + 1), sizeof(double));

    if (p == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Return an error code
    }

    double *v = (double *)calloc(n, sizeof(double));

    if (v == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Return an error code
    }

    v[0] = 1.0;

    double *c = (double *)calloc(n, sizeof(double));

    if (c == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Return an error code
    }

    double *w = (double *)calloc(n, sizeof(double));

    if (w == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Return an error code
    }

    int k = 0;
    int last_nonzero = 0;

    while (1)
    {
        p[k] = p[k + 1] + pow((v[k] - c[k]), 2) * Norm(u[k], n);

        if (p[k] < R_SQUARED)
        {
            if (k == 0)
            {
                R_SQUARED = p[k];
            }
            else
            {
                k -= 1;

                double temp = 0;

                for (int i = k + 1; i < n; i++)
                {
                    temp += mu[i][k] * v[i];
                }

                c[k] = -temp;
                v[k] = round(c[k]);
                w[k] = 1;
            }
        }
        else
        {
            k += 1;

            if (k == n)
            {
                free(p);
                free(v);
                free(c);
                free(w);

                return R_SQUARED;
            }

            if (k >= last_nonzero)
            {
                last_nonzero = k;

                v[k] += 1;
            }
            else
            {
                if (v[k] > c[k])
                {
                    v[k] -= w[k];
                }
                else
                {
                    v[k] += w[k];
                }

                w[k] += 1;
            }
        }
    }
}
