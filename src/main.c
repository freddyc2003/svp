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

    // Infer the dimensions of the lattice basis from the number of arguments
    n = sqrt(argc - 1);

    // If is not a perfect square input basis is not square
    if (pow(round(n), 2) != argc - 1) {
        printf("Invalid input\n");
        return 1;
    }

    // Allocate a 2D array of size n x n for the lattice basis
    double **basis = (double **)malloc(n * sizeof(double *));

    if (basis == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Allocate memory for each vector in the lattice basis
    for (int i = 0; i < n; i++) {
        basis[i] = (double *)malloc(n * sizeof(double));

        if (basis[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    // Parse the command line arguments and store in the basis array
    int errno = ParseArguments(argc, argv, basis, n);

    // Error occured when parsing the input halt the program
    if (errno == 1) {
        return 1;
    }

    // Allocate memory for a 2D array to store the orthogonalised basis vectors
    double **u = (double **)malloc(n * sizeof(double *));

    if (u == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Allocate memory for each vector in the orthogonalised basis
    for (int i = 0; i < n; i++) {
        u[i] = (double *)calloc(n, sizeof(double));

        if (u[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    // Allocate memory for a 2D array to store gram schmidt coefficients
    double **mu = (double **)malloc(n * sizeof(double *));

    if (mu == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        // Make sure they are all zeros as they might not be overwritten
        mu[i] = (double *)calloc(n, sizeof(double));

        if (mu[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    // Apply the gram schmidt process to the lattice basis
    GramSchmidt(basis, u, mu, n);

    // LLL delta parameter
    double delta = 0.75;

    // Apply the LLL reduction to the lattice basis
    LLL(basis, u, mu, delta, n);

    // Recompute u and mu on the reduced lattice basis
    GramSchmidt(basis, u, mu, n);

    // Use Gaussian heuristic to calculate upper bound on the shortest vector
    double bound = Bound(u, n);

    // To store the norm of the shortest vector
    double result;

    // Run enumeration on the reduced basis
    result = Enumeration(u, mu, bound, n);

    printf("%.15f \n", sqrt(result));

    // Write the result to result.txt
    WriteResult(sqrtl(result));

    // Deallocate the memory for the basis 2D array
    for (int i = 0; i < n; i++) {
        free(basis[i]);
    }
    free(basis);

    // Deallocate the memory for the 2D array u
    for (int i = 0; i < n; i++) {
        free(u[i]);
    }
    free(u);

    // Deallocate the memory for the 2D array mu
    for (int i = 0; i < n; i++) {
        free(mu[i]);
    }
    free(mu);

    return 0;
}
