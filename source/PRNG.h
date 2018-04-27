#ifndef PRNG_H_
#define PRNG_H_

#include <random>

class PRNG {
    private:
        std::uniform_real_distribution<> distribution;
        std::mt19937 generator;

    public:
        PRNG();
        double get_rand(unsigned index);
};

#endif