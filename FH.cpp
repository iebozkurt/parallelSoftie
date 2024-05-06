#include "BreedingProgram.hpp"
#include "SoftieDog.hpp"

int main() {
    SoftieDog::initializeRNG();
    
    BreedingProgram program(500); // 500 dogs in the breeding program
    program.runSimulation(1000); // Run up to 100 generations or until 10% softies are reached

    return 0;
}