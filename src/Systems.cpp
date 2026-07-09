#include "Systems.h"
#include "Simulation.h"
#include <iostream>


std::mt19937 gen(42);


void SpawnSatellite(entt::registry& registry, int i) {
    bool success = false;
    perturb::StateVector sv;
                                                                // функция, которая создает объект спутник на основе TLE
                                                                // и выгружает их в регистр.
                                                                // здесь предусмотрена защита от неправильных генераций
                                                                // в случае, если библиотека perturb, обрабатывающая TLE. возвращает ошибку
                                                                // или координаты равны 0, то для спутника генерируются новое TLE
                                           
    while (!success) {                                          
        TLE params = CreateSatelliteTLE(GenOrbit(gen), i);      
                                                                

  
        auto sat = perturb::Satellite::from_tle(params.TLE_1, params.TLE_2);

        if (sat.last_error() == perturb::Sgp4Error::NONE) {
            auto error = sat.propagate(sat.epoch(), sv);

            if (error == perturb::Sgp4Error::NONE && (sv.position[0] != 0 || sv.position[1] != 0 || sv.position[2] != 0)) {
             
                auto satellite = registry.create();
                registry.emplace<SatelliteState>(satellite, std::move(sat));

                auto& pos = registry.emplace<Position>(satellite);
                pos.x = sv.position[0];
                pos.y = sv.position[1];
                pos.z = sv.position[2];

                success = true;
            }
        }
    }
}




void PositionUpdateAllSatellite(perturb::JulianDate& currentTime, entt::registry& registry) {  // функция, которая высчитывает положение спутника на орбите в конкретный момент времени 
    auto view = registry.view<SatelliteState, Position>();                                     // на вход подается време по юлианскому календарю и  регистр с нашими спутниками

    for (auto [entity, satStat, pos] : view.each()) {
        perturb::StateVector sv;


        auto error = satStat.sat.propagate(currentTime, sv);


        if (error == perturb::Sgp4Error::NONE) {
            pos.x = sv.position[0];
            pos.y = sv.position[1];
            pos.z = sv.position[2];
        }
    }
}


perturb::DateTime GetCurrentDateTime() { //функция, которая переводит герегорианскиий календарь в юлианский
    auto now = system_clock::now();
    auto dp = floor<days>(now);
    year_month_day ymd{ dp };
    hh_mm_ss time{ floor<milliseconds>(now - dp) };

    return perturb::DateTime{
        static_cast<int>(ymd.year()),
        static_cast<int>(static_cast<unsigned>(ymd.month())), 
        static_cast<int>(static_cast<unsigned>(ymd.day())),
        static_cast<int>(time.hours().count()),
        static_cast<int>(time.minutes().count()),
        static_cast<double>(time.seconds().count()) + static_cast<double>(time.subseconds().count()) / 1000.0
    };
}


