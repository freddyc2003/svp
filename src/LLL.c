#include <math.h>
#include <stdio.h>

#include "GramSchmidt.h"
#include "VectorOperations.h"

void sizeReduce(double **B, double **u, double **mu, int k, int n) {
    for (int j = k - 1; j >= 0; j--) {
        if (fabs(mu[k][j]) > 0.5) {
            double coff = round(mu[k][j]);

            for (int i = 0; i < n; i++) {
                B[k][i] -= coff * B[j][i];
            }

            mu[k][j] -= coff;

            // Partially update the gs coefficients
            for (int i = 0; i < j; i++) {
                mu[k][i] -= coff * mu[j][i];
            }
        }
    }
}

void LLL(double **B, double **u, double **mu, double delta, int n) {
    int k = 1;

    while (k < n) {
        sizeReduce(B, u, mu, k, n);

        // If Lovasz condition fails
        if (InnerProduct(u[k], u[k], n) <
            (delta - pow(mu[k][k - 1], 2)) *
                InnerProduct(u[k - 1], u[k - 1], n)) {
            // Swap B[k] and B[k + 1]
            double *temp = B[k];
            B[k] = B[k - 1];
            B[k - 1] = temp;

            // Update u and mu
            GramSchmidt(B, u, mu, n);

            k = fmax(k - 1, 1);
        } else {
            k += 1;
        }
    }
}
