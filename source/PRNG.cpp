#include "PRNG.h"
#include <omp.h>
#include <iostream>

PRNG::PRNG() {

    for (int i = 0; i < 16; i++) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        generator[i] = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
        distribution[i] = std::uniform_real_distribution<>(0.0, 1.0);
    }
}

double PRNG::get_rand(unsigned index) {
    return this->distribution[index](this->generator[index]);
}