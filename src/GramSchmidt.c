#include "GramSchmidt.h"

#include <stdio.h>

#include "VectorOperations.h"

void GramSchmidt(double **B, double **u, double **mu, int N) {
    for (int i = 0; i < N; i++) {
        // Copy ith vector from B to u
        for (int l = 0; l < N; l++) {
            u[i][l] = B[i][l];
        }

        for (int k = 0; k < i; k++) {
            double norm = InnerProduct(u[k], u[k], N);

            // Catch fp error where norm should be zero
            if (norm < 10e-10) {
                continue;
            }

            // Compute GS coefficient from i,k
            // Multiply by 1/norm to try and reduce fp error
            mu[i][k] = InnerProduct(B[i], u[k], N) * (1 / norm);

            // Subtract component of kth vector from ith vector
            for (int j = 0; j < N; j++) {
                u[i][j] -= mu[i][k] * u[k][j];
            }
        }
    }
}
