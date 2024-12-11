#include <stdio.h>
#include <stdlib.h> // For atoi() and atof()
#include <time.h>
#include "vmpi_model.h"
#include "utils.h"


int main(int argc, char *argv[]) {
    if (argc != 5 && argc != 6) { // Add an optional 5th argument for the seed
        printf("Usage: %s <N> <lambda> <c> <output_file> [seed]\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    double lambda = atof(argv[2]);
    double c = atof(argv[3]);
    const char *output_file_name = argv[4];

    // Set the random seed
    unsigned int seed;
    if (argc == 6) {
        seed = (unsigned int)atoi(argv[5]);
    } else {
        seed = (unsigned int)time(NULL); // Use current time as the default seed
    }
    srand(seed);

    // Create or open the output file
    FILE *output_file = fopen(output_file_name, "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }

    // Initialize system
    int *spins = (int *)malloc(N * sizeof(int));
    double *history = (double *)malloc(N * sizeof(double));
    initialize_spins(spins, N);
    initialize_history(history, N);

    // Run simulation and save magnetization at each step
    for (int t = 0; t < MAX_TIME; ++t) {
        update_spins(spins, history, N, lambda, c);
        update_history(history, spins, N, c);
        double magnetization = calculate_magnetization(spins, N);

        // Save magnetization to file
        fprintf(output_file, "%d %f\n", t, magnetization);

        if (magnetization == 1.0 || magnetization == -1.0) {
            printf("Consensus reached at time step %d with magnetization %f\n", t, magnetization);
            break;
        }
    }

    printf("Magnetization data saved to results/magnetization.txt\n");

    // Cleanup
    free(spins);
    free(history);
    fclose(output_file);

    return 0;
}
