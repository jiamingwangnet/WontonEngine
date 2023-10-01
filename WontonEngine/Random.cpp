#include "include/WontonEngine/Math/Random.h"

std::random_device won::Random::rd;
std::mt19937 won::Random::rng{rd()};