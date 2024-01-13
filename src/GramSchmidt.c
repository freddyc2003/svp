#include "GramSchmidt.h"

#include <stdio.h>

#include "VectorOperations.h"

void GramSchmidt(double **B, double **u, double **mu, int N) {
    for (int i = 0; i < N; i++) {
        for (int l = 0; l < N; l++) {
            u[i][l] = (double)B[i][l];
            mu[i][l] = 0;  // not necessary?
        }

        for (int k = 0; k < i; k++) {
            printf("i = %d \n", i);
            printf("k = %d \n", k);
            for (int t = 0; t < N; t++) {
                printf("%.10f ", B[i][t]);
            }
            printf("\n");
            for (int t = 0; t < N; t++) {
                printf("%.10f ", u[k][t]);
            }

            mu[i][k] =
                InnerProduct(B[i], u[k], N) / InnerProduct(u[k], u[k], N);
            printf("mu=%.40f \n", mu[i][k]);

            for (int j = 0; j < N; j++) {
                printf("mu[i][k]=%.60f\n", mu[i][k]);
                printf("u[k][j]=%.60f\n", u[k][j]);
                printf("Helllloooo = %.60f\n", mu[i][k] * u[k][j]);
                printf("u[i][j] = %.60f\n", u[i][j]);

                if (u[i][j] == mu[i][k] * u[k][j]) {
                    printf("THEY ARE THE SAME! \n");
                }

                u[i][j] -= mu[i][k] * u[k][j];
                printf("u[i][j] = %.60f\n\n", u[i][j]);
            }
        }
    }

    printf("After gramschmidt inside GS u \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.15f ", u[i][j]);
        }
        printf("\n");
    }
}
