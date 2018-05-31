#ifndef PRNG_H_
#define PRNG_H_

#include <random>

class PRNG {
    private:
        std::uniform_real_distribution<float> distribution[16];
        std::mt19937 generator[16];

    public:
        PRNG();
        float get_rand(unsigned index);
};

#endif