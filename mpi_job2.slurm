#!/bin/bash
#SBATCH --job-name=mpi5_job
#SBATCH --output=mpi5_%j.out
#SBATCH --error=mpi_job.err
#SBATCH --nodes=4
#SBATCH --time=01:00:00
#SBATCH --partition=classroom

module load openmpi
mpiexec -np 5 ./SoftieMPIBreeding
