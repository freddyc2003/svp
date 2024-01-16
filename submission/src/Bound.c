#include <math.h>

#include "VectorOperations.h"

double Bound(double **u, int n) {
    double vol = 1.0;

    for (int i = 0; i < n; i++) {
        vol *= sqrt(InnerProduct(u[i], u[i], n));
    }

    double pow_vol = exp((1.0 / n) * log(vol));

    double lambda = sqrt(1 + (n / 4.0)) * pow_vol;

    return lambda;
}
