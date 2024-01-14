#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bound.h"
#include "Enumeration.h"
#include "GramSchmidt.h"
#include "LLL.h"
#include "ParseArguments.h"
#include "VectorOperations.h"
#include "WriteResult.h"

int main(int argc, char *argv[]) {
    int n;

    n = sqrt(argc - 1);

    if (pow(round(n), 2) != argc - 1) {
        printf("Invalid input\n");
        return 1;
    }

    // for (n = 1; n < argc; n++) {
    //     if (strstr(argv[n], "]") != NULL) {
    //         break;
    //     }
    // }

    double **basis = (double **)malloc(n * sizeof(double *));

    if (basis == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        basis[i] = (double *)malloc(n * sizeof(double *));

        if (basis[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    int errno = ParseArguments(argc, argv, basis, n);

    if (errno == 1) {
        return 1;
    }

    // printf("Basis: \n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%.15f ", basis[i][j]);
    //     }
    //     printf("\n");
    // }

    double **u = (double **)malloc(n * sizeof(double *));

    if (u == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        u[i] = (double *)malloc(n * sizeof(double));

        if (u[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    double **mu = (double **)malloc(n * sizeof(double *));

    if (mu == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        mu[i] = (double *)malloc(n * sizeof(double));

        if (mu[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    GramSchmidt(basis, u, mu, n);

    // printf("Before LLL \n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%.15f ", mu[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("Before LLL \n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%.15f ", u[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("u Before LLL \n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%.15f ", u[i][j]);
    //     }
    //     printf("\n");
    // }

    LLL(basis, u, mu, 0.75, n);

    // printf("After LLL \n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%.15f ", basis[i][j]);
    //     }
    //     printf("\n");
    // }

    // // // printf("---------------- \n");

    // // // for (int i = 0; i < n; i++)
    // // // {
    // // //     for (int j = 0; j < n; j++)
    // // //     {
    // // //         printf("%.15f ", basis[i][j]);
    // // //     }
    // // //     printf("\n");
    // // // }

    // // // printf("---------------- \n");

    // GramSchmidt(basis, u, mu, n);

    double bound = Bound(u, n);

    // printf("Bound: %.15f \n", bound);

    double result;

    // // // result = Enumeration(u, mu, 50, n);
    result = Enumeration(u, mu, bound, n);

    // printf("Norm:  %.15f \n", sqrt(result));

    WriteResult(sqrtl(result));

    for (int i = 0; i < n; i++) {
        free(basis[i]);
    }
    free(basis);

    for (int i = 0; i < n; i++) {
        free(u[i]);
    }
    free(u);

    for (int i = 0; i < n; i++) {
        free(mu[i]);
    }
    free(mu);

    return 0;
}
