# Makefile

# Compiler settings - can change according to your system environment
MPICXX = mpicxx
CXX = c++

# Compiler flags
OMP_FLAGS = -fopenmp

# Targets
all: SoftieMPI+OpenMP SoftieMPIBreeding SoftieOneBreeding

SoftieMPI+OpenMP: SoftieMPI+OpenMP.cpp
	$(MPICXX) $(OMP_FLAGS) -o SoftieMPI+OpenMP SoftieMPI+OpenMP.cpp

SoftieMPIBreeding: SoftieMPIBreeding.cpp
	$(MPICXX) -o SoftieMPIBreeding SoftieMPIBreeding.cpp

SoftieOneBreeding: SoftieOneBreeding.cpp
	$(CXX) -o SoftieOneBreeding SoftieOneBreeding.cpp

clean:
	rm -f SoftieMPI+OpenMP SoftieMPIBreeding SoftieOneBreeding

.PHONY: all clean
