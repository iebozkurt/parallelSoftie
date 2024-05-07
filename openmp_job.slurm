#!/bin/bash
#SBATCH --job-name=mpi+omp
#SBATCH --output=mpi+omp_%j.out
#SBATCH --error=mpi_job.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=5
#SBATCH --time=01:00:00
#SBATCH --partition=classroom

module load openmpi
export OMP_NUM_THREADS=2
mpiexec -np 5 ./SoftieMPI_OpenMP