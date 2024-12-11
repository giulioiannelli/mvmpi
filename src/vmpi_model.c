#include "vmpi_model.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>

double simulate_vmpi(int N, double lambda, double c) {
    int *spins = (int *)malloc(N * sizeof(int));
    double *history = (double *)malloc(N * sizeof(double));
    initialize_spins(spins, N);
    initialize_history(history, N);

    double magnetization = 0.0;

    for (int t = 0; t < MAX_TIME; ++t) {
        update_spins(spins, history, N, lambda, c);
        update_history(history, spins, N, c);
        magnetization = calculate_magnetization(spins, N);
    }

    free(spins);
    free(history);

    return magnetization;
}
