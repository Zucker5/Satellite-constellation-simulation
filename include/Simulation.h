#include "Components.h"
#include <random>
#include "perturb/perturb.hpp"
#include <cmath>
#include <format>

OrbitParameters GenOrbit(std::mt19937&);

TLE CreateSatelliteTLE(const OrbitParameters, int);

