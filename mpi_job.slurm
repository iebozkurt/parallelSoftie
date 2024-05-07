#!/bin/bash
#SBATCH --job-name=mpi1_job
#SBATCH --output=mpi1_%j.out.out
#SBATCH --error=mpi_job.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=5
#SBATCH --time=01:00:00
#SBATCH --partition=classroom

module load openmpi
mpiexec -np 5 ./SoftieMPIBreeding
