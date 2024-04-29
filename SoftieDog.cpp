#include <iostream>
#include <bitset>
#include <string>
#include <random>
#include <ctime>

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

    static std::mt19937 rng; // Random number generator

    // Helper to generate random bitset
    template<size_t N>
    static std::bitset<N> generateRandomBitset() {
        std::uniform_int_distribution<unsigned long> dist(0, (1UL << N) - 1);
        return std::bitset<N>(dist(rng));
    }

public:
    // Static initializer for the random number generator
    static void initializeRNG() {
        rng.seed(static_cast<unsigned>(std::time(nullptr)));
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
          weightBits(weight), pawAreaBits(pawArea), pawWebbedBits(pawWebbed), dispositionBits(disposition) {}

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
};

std::mt19937 SoftieDog::rng;

int main() {
    SoftieDog::initializeRNG();

    // Create an array of SoftieDog instances
    const int numDogs = 500; // or 100 for each of five kennels
    SoftieDog dogs[numDogs];

    // Example usage: Display characteristics of the first few dogs to check randomness
    for (int i = 0; i < 5; ++i) {
        dogs[i].displayCharacteristics();
        std::cout << "Is a Softie: " << (dogs[i].isSoftie() ? "Yes" : "No") << std::endl;
        std::cout << "Softie Fitness Score: " << dogs[i].softieFitness() << std::endl;
    }

    return 0;
}