#include <math.h>
#include <stdio.h>

#include "VectorOperations.h"

double Bound(double **u, int N) {
    double vol = 1.0;

    for (int i = 0; i < N; i++) {
        vol *= sqrt(InnerProduct(u[i], u[i], N));
    }

    double pow_vol = exp((1.0 / N) * log(vol));

    double lambda = sqrt(1 + (N / 4.0)) * pow_vol;

    // double result = sqrt(N / (2.0 * M_PI * M_E)) * pow_vol;

    return lambda;
}
