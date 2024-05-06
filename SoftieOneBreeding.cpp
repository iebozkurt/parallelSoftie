#include <iostream>
#include <bitset>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <chrono>
#include <climits>



class SoftieDog {
private:
    std::bitset<8> coatLengthBits;
    std::bitset<6> coatSoftnessBits;
    std::bitset<3> backgroundBrightness;
    std::bitset<3> backgroundColor;
    std::bitset<3> foregroundBrightness;
    std::bitset<3> foregroundColor;
    std::bitset<1> pawColor;
    std::bitset<1> tailColor;
    std::bitset<8> tailLengthBits;
    std::bitset<2> tailAppearance;
    std::bitset<10> weightBits;
    std::bitset<7> pawAreaBits;
    std::bitset<3> pawWebbedBits;
    std::bitset<6> dispositionBits;
    int age;
    

    // Helper to generate random bitset
    template<size_t N>
    static std::bitset<N> generateRandomBitset() {
        std::uniform_int_distribution<unsigned long> dist(0, (1UL << N) - 1);
        return std::bitset<N>(dist(rng));
    }

public:
    static std::mt19937 rng; // Random number generator
    // Static initializer for the random number generator
    static void initializeRNG() {
        auto hr_time = std::chrono::high_resolution_clock::now();
        auto time_since_epoch = hr_time.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch).count();
        rng.seed(static_cast<unsigned>(millis));
    }

    // Constructor
    SoftieDog(unsigned long coatLength = 0, unsigned long softness = 0, unsigned long bgBrightness = 0,
              unsigned long bgColor = 0, unsigned long fgBrightness = 0, unsigned long fgColor = 0,
              unsigned long pColor = 0, unsigned long tColor = 0, unsigned long tailLength = 0,
              unsigned long tailApp = 0, unsigned long weight = 0, unsigned long pawArea = 0,
              unsigned long pawWebbed = 0, unsigned long disposition = 0)
        : coatLengthBits(coatLength), coatSoftnessBits(softness), backgroundBrightness(bgBrightness),
          backgroundColor(bgColor), foregroundBrightness(fgBrightness), foregroundColor(fgColor),
          pawColor(pColor), tailColor(tColor), tailLengthBits(tailLength), tailAppearance(tailApp),
          weightBits(weight), pawAreaBits(pawArea), pawWebbedBits(pawWebbed), dispositionBits(disposition), age(0) {}
    
    SoftieDog(int a ,unsigned long data) {
        unsigned long mask = (1UL << 6) - 1; // Using 6 bits as the largest single field mask needed
        dispositionBits = (data & ((1UL << 6) - 1)); data >>= 6;
        pawWebbedBits = (data & ((1UL << 3) - 1)); data >>= 3;
        pawAreaBits = (data & ((1UL << 7) - 1)); data >>= 7;
        weightBits = (data & ((1UL << 10) - 1)); data >>= 10;
        tailAppearance = (data & ((1UL << 2) - 1)); data >>= 2;
        tailLengthBits = (data & ((1UL << 8) - 1)); data >>= 8;
        tailColor = (data & ((1UL << 1) - 1)); data >>= 1;
        pawColor = (data & ((1UL << 1) - 1)); data >>= 1;
        foregroundColor = (data & ((1UL << 3) - 1)); data >>= 3;
        foregroundBrightness = (data & ((1UL << 3) - 1)); data >>= 3;
        backgroundColor = (data & ((1UL << 3) - 1)); data >>= 3;
        backgroundBrightness = (data & ((1UL << 3) - 1)); data >>= 3;
        coatSoftnessBits = (data & ((1UL << 6) - 1)); data >>= 6;
        coatLengthBits = (data & ((1UL << 8) - 1)); // The remaining bits are for the coat length
        age =0;
    }

    SoftieDog(bool randomize) {
        if (randomize) {
            coatLengthBits = generateRandomBitset<8>();
            coatSoftnessBits = generateRandomBitset<6>();
            backgroundBrightness = generateRandomBitset<3>();
            backgroundColor = generateRandomBitset<3>();
            foregroundBrightness = generateRandomBitset<3>();
            foregroundColor = generateRandomBitset<3>();
            pawColor = generateRandomBitset<1>();
            tailColor = generateRandomBitset<1>();
            tailLengthBits = generateRandomBitset<8>();
            tailAppearance = generateRandomBitset<2>();
            weightBits = generateRandomBitset<10>();
            pawAreaBits = generateRandomBitset<7>();
            pawWebbedBits = generateRandomBitset<3>();
            dispositionBits = generateRandomBitset<6>();
        }
        age = 0;
    }

    // Setters
    void setCoatLength(unsigned long length) { coatLengthBits = length; }
    void setCoatSoftness(unsigned long softness) { coatSoftnessBits = softness; }
    void setBackgroundBrightness(unsigned long brightness) { backgroundBrightness = brightness; }
    void setBackgroundColor(unsigned long color) { backgroundColor = color; }
    void setForegroundBrightness(unsigned long brightness) { foregroundBrightness = brightness; }
    void setForegroundColor(unsigned long color) { foregroundColor = color; }
    void setPawColor(unsigned long color) { pawColor = color; }
    void setTailColor(unsigned long color) { tailColor = color; }
    void setTailLength(unsigned long length) { tailLengthBits = length; }
    void setTailAppearance(unsigned long appearance) { tailAppearance = appearance; }
    void setWeight(unsigned long weight) { weightBits = weight; }
    void setPawArea(unsigned long area) { pawAreaBits = area; }
    void setPawWebbed(unsigned long webbed) { pawWebbedBits = webbed; }
    void setDisposition(unsigned long disposition) { dispositionBits = disposition; }
    
    void incrementAge(){age+=1;}
    bool isReadyToDie(){if( age >3) return true; return false;}
    // Getters
    unsigned long getCoatLength() const { return coatLengthBits.to_ulong(); }
    unsigned long getCoatSoftness() const { return coatSoftnessBits.to_ulong(); }
    unsigned long getBackgroundBrightness() const { return backgroundBrightness.to_ulong(); }
    unsigned long getBackgroundColor() const { return backgroundColor.to_ulong(); }
    unsigned long getForegroundBrightness() const { return foregroundBrightness.to_ulong(); }
    unsigned long getForegroundColor() const { return foregroundColor.to_ulong(); }
    unsigned long getPawColor() const { return pawColor.to_ulong(); }
    unsigned long getTailColor() const { return tailColor.to_ulong(); }
    unsigned long getTailLength() const { return tailLengthBits.to_ulong(); }
    unsigned long getTailAppearance() const { return tailAppearance.to_ulong(); }
    unsigned long getWeight() const { return weightBits.to_ulong(); }
    unsigned long getPawArea() const { return pawAreaBits.to_ulong(); }
    unsigned long getPawWebbed() const { return pawWebbedBits.to_ulong(); }
    unsigned long getDisposition() const { return dispositionBits.to_ulong(); }
    int getAge() const { return age;}
    // Display the dog's characteristics
    void displayCharacteristics() const {
        std::cout << "Softie Dog Characteristics: " << std::endl;
        std::cout << "Coat Length: " << getCoatLength() << " inches" << std::endl;
        std::cout << "Coat Softness: " << getCoatSoftness() << std::endl;
        std::cout << "Background Brightness: " << getBackgroundBrightness() << std::endl;
        std::cout << "Background Color: " << getBackgroundColor() << std::endl;
        std::cout << "Foreground Brightness: " << getForegroundBrightness() << std::endl;
        std::cout << "Foreground Color: " << getForegroundColor() << std::endl;
        std::cout << "Paw Color: " << getPawColor() << std::endl;
        std::cout << "Tail Color: " << getTailColor() << std::endl;
        std::cout << "Tail Length: " << getTailLength() << " inches" << std::endl;
        std::cout << "Tail Appearance: " << getTailAppearance() << std::endl;
        std::cout << "Weight: " << getWeight() << " kg" << std::endl;
        std::cout << "Paw Area: " << getPawArea() << " sq. in." << std::endl;
        std::cout << "Paw Webbed: " << getPawWebbed() << std::endl;
        std::cout << "Disposition: " << getDisposition() << std::endl;
    }

    unsigned long toUnsignedLong() const {
        unsigned long data = 0;
        data |= coatLengthBits.to_ulong(); data <<= 6;
        data |= coatSoftnessBits.to_ulong(); data <<= 3;
        data |= backgroundBrightness.to_ulong(); data <<= 3;
        data |= backgroundColor.to_ulong(); data <<= 3;
        data |= foregroundBrightness.to_ulong(); data <<= 3;
        data |= foregroundColor.to_ulong(); data <<= 1;
        data |= pawColor.to_ulong(); data <<= 1;
        data |= tailColor.to_ulong(); data <<= 8;
        data |= tailLengthBits.to_ulong(); data <<= 2;
        data |= tailAppearance.to_ulong(); data <<= 10;
        data |= weightBits.to_ulong(); data <<= 7;
        data |= pawAreaBits.to_ulong(); data <<= 3;
        data |= pawWebbedBits.to_ulong(); data <<= 6;
        data |= dispositionBits.to_ulong();
        return data;
    }

    bool isSoftie() const {
        return (getCoatLength() >= 8 &&                    // Coat length 8 inches or more
                coatSoftnessBits.to_ulong() <= 1 &&        // Extremely soft
                backgroundColor.to_ulong() == 0 &&         // Background color is white
                foregroundColor.to_ulong() == 1 &&         // Foreground color is brown
                pawColor.to_ulong() == 0 &&                // White paws
                tailColor.to_ulong() == 1 &&               // Black tail
                getTailLength() >= 4 && getTailLength() <= 6 && // Tail length between 4 and 6 inches
                tailAppearance.to_ulong() == 0 &&          // Tail points straight up
                getWeight() >= 90 &&                      // Weight is 90 kg or heavier
                getPawArea() >= 9 &&                       // Paw print area 9 sq. in. or more
                pawWebbedBits.to_ulong() == 7 &&           // Fully webbed toes
                dispositionBits.to_ulong() <= 1);          // Extremely mild tempered
    }


    // Compute a fitness score based on Softie standards
    int softieFitness() const {
        int score = 0;
        score += (getCoatLength() >= 8) ? 1 : 0;
        score += (coatSoftnessBits.to_ulong() <= 1) ? 1 : 0;
        score += (backgroundColor.to_ulong() == 0) ? 1 : 0;
        score += (foregroundColor.to_ulong() == 1) ? 1 : 0;
        score += (pawColor.to_ulong() == 0) ? 1 : 0;
        score += (tailColor.to_ulong() == 1) ? 1 : 0;
        score += (getTailLength() >= 4 && getTailLength() <= 6) ? 1 : 0;
        score += (tailAppearance.to_ulong() == 0) ? 1 : 0;
        score += (getWeight() >= 90) ? 1 : 0;
        score += (getPawArea() >= 9) ? 1 : 0;
        score += (pawWebbedBits.to_ulong() == 7) ? 1 : 0;
        score += (dispositionBits.to_ulong() <= 1) ? 1 : 0;
        return score;
    }

     void mutate(int i) {
        std::uniform_int_distribution<int> mutation_dist(0, 63); // For picking random bit positions
        std::uniform_int_distribution<int> num_mutations_dist(0,3 ); // For number of mutations
        int num_mutations = num_mutations_dist(rng)+i;
        while (num_mutations--) {
            int mutation_point = mutation_dist(rng);
            if (mutation_point < 8) { // Mutate coatLengthBits
                coatLengthBits.flip(mutation_point);
            } else if (mutation_point < 14) { // Mutate coatSoftnessBits
                coatSoftnessBits.flip(mutation_point - 8);
            }  else if (mutation_point < 17) { // Mutate backgroundBrightness
            backgroundBrightness.flip(mutation_point - 14);
            } else if (mutation_point < 20) { // Mutate backgroundColor
                backgroundColor.flip(mutation_point - 17);
            } else if (mutation_point < 23) { // Mutate foregroundBrightness
                foregroundBrightness.flip(mutation_point - 20);
            } else if (mutation_point < 26) { // Mutate foregroundColor
                foregroundColor.flip(mutation_point - 23);
            } else if (mutation_point < 27) { // Mutate pawColor
                pawColor.flip(mutation_point - 26);
            } else if (mutation_point < 28) { // Mutate tailColor
                tailColor.flip(mutation_point - 27);
            } else if (mutation_point < 36) { // Mutate tailLengthBits
                tailLengthBits.flip(mutation_point - 28);
            } else if (mutation_point < 38) { // Mutate tailAppearance
                tailAppearance.flip(mutation_point - 36);
            } else if (mutation_point < 48) { // Mutate weightBits
                weightBits.flip(mutation_point - 38);
            } else if (mutation_point < 55) { // Mutate pawAreaBits
                pawAreaBits.flip(mutation_point - 48);
            } else if (mutation_point < 58) { // Mutate pawWebbedBits
                pawWebbedBits.flip(mutation_point - 55);
            } else if (mutation_point < 64) { // Mutate dispositionBits
                dispositionBits.flip(mutation_point - 58);
            }
        }
    }
};


std::mt19937 SoftieDog::rng;

class BreedingProgram {
    std::vector<SoftieDog> dogs;
    std::vector<int> numbers;
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
        for (int i = 0; i < (int)(dogs.size()/2) ; i++) {
        numbers.push_back(i);  // Add number to vector
        }
    }

    void simulateGeneration() {        
        std::vector<SoftieDog> newGeneration;
        std::uniform_int_distribution<int> mate(1,dogs.size()-1);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine engine(seed);
        std::shuffle(numbers.begin(), numbers.end(), engine);
        

        for (int i = 0; i < dogs.size()/2; ++i) {
            
            int mate_index = numbers[i];
            int litter_size = litter_size_dist(SoftieDog::rng);
            unsigned long l = dist(SoftieDog::rng);
            unsigned long n ,c =0;
            c = ~c;
            n = l ^c;
            for (int j = 0; j < litter_size; ++j) {
                c = (dogs[i].toUnsignedLong() & l) | (dogs[mate_index].toUnsignedLong() & n );
                SoftieDog puppy(0,c);
                puppy.mutate((dogs[i].getAge()+dogs[mate_index].getAge())/2); // Mutate the puppy's genetic data
                newGeneration.push_back(puppy);
            }
        }
        
        for (int i = 0; i < dogs.size(); ++i) {
            dogs[i].incrementAge();
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

int main() {

    SoftieDog::initializeRNG();
    BreedingProgram program(500); // 500 dogs in the breeding program
    program.runSimulation(1000); // Run up to 100 generations or until 10% softies are reached

    return 0;
}