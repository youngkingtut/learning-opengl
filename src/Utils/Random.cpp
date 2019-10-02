#include "Random.h"

namespace Random {
    std::mt19937 rng;
    bool initialized{false};

    float getRandomFloat(float lower, float upper) {
        if(!initialized) {
            std::random_device rd;
            std::mt19937 rng{rd()};
            initialized = true;
        }

        std::uniform_real_distribution<> distribution{lower, upper};
        return distribution(rng);
    }

    int getRandomInt(int lower, int upper) {
        if(!initialized) {
            std::random_device rd;
            std::mt19937 rng{rd()};
            initialized = true;
        }

        std::uniform_int_distribution<> distribution{lower, upper};
        return distribution(rng);
    }

    bool getRandomBool() {
        std::uniform_int_distribution<> distribution{0, 1};
        return 0 == distribution(rng);
    }
}
