#include "GramSchmidt.h"

#include <stdio.h>

#include "VectorOperations.h"

// void GramSchmidt(double **B, double **u, double **mu, int N) {
//     for (int i = 0; i < N; i++) {
//         // Copy ith vector from B to u
//         for (int l = 0; l < N; l++) {
//             u[i][l] = B[i][l];
//         }

//         for (int k = 0; k < i; k++) {
//             double norm = InnerProduct(u[k], u[k], N);

//             // Catch fp error where norm should be zero
//             if (norm < 10e-10) {
//                 continue;
//             }

//             // Compute GS coefficient from i,k
//             // Multiply by 1/norm to try and reduce fp error
//             mu[i][k] = InnerProduct(B[i], u[k], N) * (1 / norm);

//             // Subtract component of kth vector from ith vector
//             for (int j = 0; j < N; j++) {
//                 u[i][j] -= mu[i][k] * u[k][j];
//             }
//         }
//     }
// }

void GramSchmidt(double **B, double **u, double **mu, int n) {
    for (int i = 0; i < n; i++) {
        for (int l = 0; l < n; l++) {
            u[i][l] = B[i][l];
            // mu[i][l] = 0;
        }

        for (int k = 0; k < i; k++) {
            double squaredNorm = InnerProduct(u[k], u[k], n);

            if (squaredNorm < 10e-10) {
                continue;
            }

            mu[i][k] =
                InnerProduct(B[i], u[k], n) / squaredNorm;

            for (int j = 0; j < n; j++) {
                u[i][j] -= mu[i][k] * u[k][j];
            }
        }
    }
}

// void GramSchmidt(double **b, double **u, double **mu, int n) {
//     for (int i = 0; i < n; i++) {
//         u[0][i] = b[0][i];
//     }

//     for (int i = 1; i < n; i++) {
//         double *w = b[i];

//         for (int j = 0; j <= i - 1; j++) {
//             double squaredNorm = InnerProduct(u[j], u[j], n);

//             if (squaredNorm < 10e-10) {
//                 continue;
//             }

//             mu[i][j] =
//                 InnerProduct(b[i], u[j], n) / squaredNorm;

//             for (int k = 0; k < n; k++) {
//                 w[k] += mu[i][j] * u[j][k];
//             }
//         }

//         for (int k = 0; k < n; k++) {
//             u[i][k] = b[i][k] - w[k];
//         }
//     }
// }
