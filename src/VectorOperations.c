#include "VectorOperations.h"

double InnerProduct(double *v, double *u, int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        result += v[i] * u[i];
    }

    return result;
}

double Norm(double *v, int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        result += v[i] * v[i];
    }

    return result;
}
