#include "utils.h"
#include <stdlib.h>
#include <math.h>

void initialize_spins(int *spins, int N) {
    for (int i = 0; i < N; ++i) {
        spins[i] = (rand() % 2) * 2 - 1; // Randomly assign +1 or -1
    }
}

// void initialize_spins(int *spins, int N) {
//     for (int i = 0; i < N / 2; ++i) {
//         spins[i] = 1; // First half +1
//     }
//     for (int i = N / 2; i < N; ++i) {
//         spins[i] = -1; // Second half -1
//     }
// }

double stable_pdf(double history, double c) {
    double log_term = history * log(c); // Compute n_i * ln(c)
    if (log_term > 700) {
        // Prevent overflow: if exp(log_term) >> 1, return ~1
        return 1.0;
    } else if (log_term < -700) {
        // Prevent underflow: if exp(log_term) << 1, return ~0
        return 0.0;
    }
    return exp(log_term) / (1 + exp(log_term));
}

void initialize_history(double *history, int N) {
    for (int i = 0; i < N; ++i) {
        history[i] = 0.0;
    }
}
void update_spins(int *spins, double *history, int N, double lambda, double c) {
    for (int i = 0; i < N; ++i) {
        double pdf_ei = stable_pdf(history[i], c);
        double random_val = rand() / (double)RAND_MAX;

        if (random_val < lambda * pdf_ei) {
            spins[i] = 1;
        } else if (random_val < lambda) {
            spins[i] = -1;
        } else {
            spins[i] = spins[rand() % N];
        }
    }
}


void update_history(double *history, int *spins, int N, double c) {
    for (int i = 0; i < N; ++i) {
        if (spins[i] == 1) {
            history[i] += 1; // Increment for +1
        } else {
            history[i] -= 1; // Decrement for -1
        }
    }
}


double calculate_magnetization(int *spins, int N) {
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += spins[i];
    }
    return (double)sum / N;
}
