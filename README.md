[![Chat-GPT-Image-Nov-10-2025-02-55-04-PM.png](https://i.postimg.cc/sDH2HF44/Chat-GPT-Image-Nov-10-2025-02-55-04-PM.png)](https://postimg.cc/fJXZkrFV)

# parallelSoftie

parallelSoftie is a playground for experimenting with a "Softie" dog breeding simulation that is implemented in three ways: a sequential baseline, an MPI-only variant, and a hybrid MPI + OpenMP version. Each simulation evolves bitset-encoded dog genomes across generations until at least 10% of the population qualifies as a "softie" according to several visual and personality traits.

## Softie dog model
* The `SoftieDog` genome packs traits such as coat length/softness, background and foreground colors, paw/tail appearance, weight, and disposition into fixed-width bitsets. Random genomes are created with `std::mt19937` to seed initial populations and to support mutation.
* Generations are advanced by selecting parents, combining their genomes with bitwise masks, applying age-weighted mutation, and discarding dogs that age out after four seasons. Populations are then sorted by a "softie fitness" score and trimmed to keep only the fittest dogs for the next generation.

## Executables
The repository contains three main executables that share the same core genetics but explore different levels of parallelism:

| Program | Parallelism | Default population | Stopping criteria |
| --- | --- | --- | --- |
| `SoftieOneBreeding` | Sequential | 500 dogs | Stops at 10% softies or 1,000 generations. |
| `SoftieMPIBreeding` | MPI across 5 ranks | 100 dogs per rank | Stops when 50 total softies are found across ranks. |
| `SoftieMPI+OpenMP` | MPI across 5 ranks + OpenMP within each rank | 100 dogs per rank | Same collective stopping rule as the MPI-only build. |

Hybrid MPI + OpenMP breeding uses shared-memory parallel loops to generate litters concurrently and aggregates them with critical sections before global selection.

## Build requirements
* C++ compiler with C++17 support (tested with `c++`/`g++`).
* MPI toolchain that provides `mpicxx` and `mpiexec` (OpenMPI or MPICH).
* OpenMP support for the hybrid build.
* `make` for convenient multi-target builds.

The provided `makefile` builds all three executables and exposes a `clean` target.

```bash
make            # builds SoftieMPI+OpenMP, SoftieMPIBreeding, SoftieOneBreeding
make clean      # removes compiled executables
```

## Running the simulations
### Sequential baseline
```bash
./SoftieOneBreeding
```
This prints timing information and stops once the softie threshold is reached.

### MPI-only breeding
```bash
mpiexec -np 5 ./SoftieMPIBreeding
```
The MPI build expects exactly five ranks; rank 0 enforces the requirement and aborts otherwise. Each rank breeds 100 dogs, exchanges its two fittest candidates with neighbors, and continues until the cluster has collectively bred 50 softies.

### Hybrid MPI + OpenMP breeding
```bash
export OMP_NUM_THREADS=2   # or tune for your node
mpiexec -np 5 ./SoftieMPI+OpenMP
```
This executable layers OpenMP parallel regions on top of MPI domain decomposition to accelerate litter generation. The runtime behavior and rank coordination mirror the MPI-only version.

## Batch jobs
Sample Slurm scripts illustrate how to run each variant on a cluster. They load OpenMPI modules, configure rank counts, and in the hybrid case expose `OMP_NUM_THREADS` for tuning.

* `mpi_job.slurm` — single-node, five-rank MPI job for `SoftieMPIBreeding`.
* `mpi_job2.slurm` — multi-node template that still launches five ranks of `SoftieMPIBreeding`.
* `openmp_job.slurm` — hybrid MPI + OpenMP submission (update the executable name if you rebuild it elsewhere).

## Experimental results
The repository retains benchmark output from previous runs in the `MPI1 Runs`, `MPI2 Runs`, and `MPI + OMP` directories. These logs can help you compare runtime characteristics between builds or validate future optimizations.

## Next steps
* Adjust litter sizes, mutation rates, or population sizes in `BreedingProgram` to explore different evolutionary pressures.
* Experiment with more ranks or threads to see how the hybrid strategy scales.
* Extend the genome encoding with new traits or scoring metrics to evolve more complex Softie behaviors.
