#ifndef UTILS_H
#define UTILS_H

void initialize_spins(int *spins, int N);
void initialize_history(double *history, int N);
void update_spins(int *spins, double *history, int N, double lambda, double c);
void update_history(double *history, int *spins, int N, double c);
double calculate_magnetization(int *spins, int N);

#endif
