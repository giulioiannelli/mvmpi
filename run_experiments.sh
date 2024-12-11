#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <N> <lambda> <c> <K>"
    exit 1
fi

# Read command-line arguments
N=$1          # Number of agents
lambda=$2     # Lambda parameter
c=$3          # c parameter
K=$4          # Number of experiments

# Ensure the results directory exists
mkdir -p results

# Run K simulations
for i in $(seq 1 $K); do
    output_file="results/magnetization_${i}.txt"
    seed=$(( $(date +%s) + $i )) # Generate a unique seed
    echo "Running experiment $i with seed $seed, saving to $output_file"
    ./build/vmpi_simulation $N $lambda $c $output_file $seed
done

echo "All experiments completed."
