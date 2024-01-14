#include <math.h>
#include <stdio.h>

#include "GramSchmidt.h"
#include "VectorOperations.h"

void LLL(double **B, double **u, double **mu, int delta, int N) {
    int k = 1;

    while (k < N) {
        for (int j = k - 1; j >= 0; j--) {
            if (fabs(mu[k][j]) > 0.5) {
                double m = round(mu[k][j]);

                for (int i = 0; i < N; i++) {
                    B[k][i] -= m * B[j][i];
                }

                GramSchmidt(B, u, mu, N);
            }
        }

        if (InnerProduct(u[k], u[k], N) >
            (delta - pow(mu[k][k - 1], 2)) *
                InnerProduct(u[k - 1], u[k - 1], N)) {
            k += 1;
        } else {
            double *temp = B[k];
            B[k] = B[k - 1];
            B[k - 1] = temp;

            GramSchmidt(B, u, mu, N);

            k = fmax(k - 1, 1);
        }
    }
}
