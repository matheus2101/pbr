#include "PRNG.h"

PRNG::PRNG() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    generator = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
    distribution = std::uniform_real_distribution<>(0.0, 1.0);
}

double PRNG::get_rand(unsigned index) {
    this->distribution(this->generator);
}