
#ifndef BREEDINGPROGRAM_HPP
#define BREEDINGPROGRAM_HPP

#include <iostream>
#include <bitset>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <chrono>
#include <climits>

class BreedingProgram {
    std::vector<SoftieDog> dogs;
    // std::vector<int> numbers;
    std::uniform_int_distribution<int> litter_size_dist;
    std::uniform_int_distribution<unsigned long> dist;

public:
    BreedingProgram(int numDogs) {
        litter_size_dist = std::uniform_int_distribution<int>(2, 5); // number of litter
        dist = std::uniform_int_distribution<unsigned long>(0, ULONG_MAX); // genetic random
        // Initialize the dogs array with random dogs
        dogs.reserve(numDogs);
        for (int i = 0; i < numDogs; ++i) {
            dogs.emplace_back(true); // Create random SoftieDog
        }
        // for (int i = 0; i < (int)(dogs.size()) ; i++) {
        // numbers.push_back(i);  // Add number to vector
        // }
    }

    void simulateGeneration() {        
        std::vector<SoftieDog> newGeneration;
        std::uniform_int_distribution<int> mate(1,dogs.size()-1);
        // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        // std::default_random_engine engine(seed);
        // std::shuffle(numbers.begin(), numbers.end(), engine);
        

        for (int i = 0; i < dogs.size(); ++i) {
            dogs[i].incrementAge();
            int mate_index = (i + mate(SoftieDog::rng))%dogs.size();
            int litter_size = litter_size_dist(SoftieDog::rng);
            unsigned long l = dist(SoftieDog::rng);
            unsigned long n ,c =0;
            c = ~c;
            n = l ^c;
            for (int j = 0; j < litter_size; ++j) {
                c = (dogs[i].toUnsignedLong() & l) | (dogs[mate_index].toUnsignedLong() & n );
                SoftieDog puppy(0,c);
                puppy.mutate(dogs[i].getAge()-1); // Mutate the puppy's genetic data
                newGeneration.push_back(puppy);
            }
        }
        
        for (int i = 0; i < dogs.size(); ++i) {
            if(dogs[i].isReadyToDie()){
                dogs.erase(dogs.begin()+i);
                std::cout << "dead dog index" << i << std::endl;
                }
        }
        // Combine old and new generations and keep only the top fittest
         dogs.insert(dogs.end(), newGeneration.begin(), newGeneration.end());
        std::nth_element(dogs.begin(), dogs.begin() + 500, dogs.end(), [](const SoftieDog& a, const SoftieDog& b) {
            return a.softieFitness() > b.softieFitness();
        });
        dogs.resize(500); // Keep only the top 500 fittest dogs
    }

    void runSimulation(int generations) {
        for (int i = 0; i < generations; ++i) {
            simulateGeneration();
            printFitnessLevels();
            if (countSofties() >= 50) { // Assuming 500 dogs total, 10% is 50
                std::cout << "Reached 10\% softies at generation " << i + 1 << std::endl;
                break;
            }
        }
    }

    void printFitnessLevels() {
        std::vector<int> fitnessLevels(13, 0); // Since the maximum fitness score is 12
        float avg=0;
        for (const auto& dog : dogs) {
            int fitness = dog.softieFitness();
            avg+= fitness;
            if (fitness >= 0 && fitness < fitnessLevels.size()) {
                 fitnessLevels[fitness]++;
            }
        }
        avg/=500;
        std::cout << "Fitness Average " << avg << std::endl;
        for (size_t i = 0; i < fitnessLevels.size(); i++) {
            std::cout << "Fitness Level " << i << ": " << fitnessLevels[i] << std::endl;
        }
    }

    int countSofties() {
        int softieCount = 0;
        for (const auto& dog : dogs) {
            if (dog.isSoftie()) {
                softieCount++;
            }
        }
        return softieCount;
    }
};

#endif