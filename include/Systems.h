#include "Components.h"
#include <cassert>
#include <entt/entt.hpp>
#include <perturb/perturb.hpp>
#include <chrono>
using namespace std::chrono;

void SpawnSatellite(entt::registry&, int);

void PositionUpdateAllSatellite(perturb::JulianDate&, entt::registry&);

perturb::DateTime GetCurrentDateTime();