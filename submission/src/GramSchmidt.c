#include "GramSchmidt.h"

#include <stdio.h>

#include "VectorOperations.h"

void GramSchmidt(double **B, double **u, double **mu, int n) {
    for (int i = 0; i < n; i++) {
        // Copy ith vector from B to u
        for (int l = 0; l < n; l++) {
            u[i][l] = B[i][l];
        }

        for (int k = 0; k < i; k++) {
            double squaredNorm = InnerProduct(u[k], u[k], n);

            // Catch fp error where norm should be zero
            if (squaredNorm < 10e-10) {
                continue;
            }

            // Compute GS coefficient for i,k
            mu[i][k] = InnerProduct(B[i], u[k], n) / squaredNorm;

            // Subtract component of kth vector from ith vector
            for (int j = 0; j < n; j++) {
                u[i][j] -= mu[i][k] * u[k][j];
            }
        }
    }
}
