#include "Simulation.h"

OrbitParameters GenOrbit(std::mt19937& gen) {															// функция-генератор для параметров
	OrbitParameters OrbParametrsSatellite;

	static std::uniform_real_distribution<double> dist_RadiusOfTheOrbit(6700.0, 8500.0);
	OrbParametrsSatellite.RadiusOfTheOrbit = dist_RadiusOfTheOrbit(gen);

	static std::uniform_real_distribution<double> dist_Eccentricity(0.0,0.5);
	OrbParametrsSatellite.Eccentricity = dist_Eccentricity(gen);

	static std::uniform_real_distribution<double> dist_Inclination(0.0, 180.0);
	OrbParametrsSatellite.Inclination = dist_Inclination(gen);

	static std::uniform_real_distribution<double> dist_LongitudeOfTheAscendingNode(0.0, 360.0);
	OrbParametrsSatellite.LongitudeOfTheAscendingNode = dist_LongitudeOfTheAscendingNode(gen);

	static std::uniform_real_distribution<double> dist_ArgumentOfPericenter(0.0, 360.0);
	OrbParametrsSatellite.ArgumentOfPericenter = dist_ArgumentOfPericenter(gen);

	static std::uniform_real_distribution<double> dist_MeanAnomaly(0.0, 360.0);
	OrbParametrsSatellite.MeanAnomaly = dist_MeanAnomaly(gen);

	return OrbParametrsSatellite;
};




TLE CreateSatelliteTLE(const OrbitParameters parametrs, int n_satellite) {														// функция, которая собирает параметры в TLE
																																// она принимает на вход параметры и номер спутника
    double n_orbits = std::sqrt(398600.4418 / std::pow(parametrs.RadiusOfTheOrbit, 3)) * (86400.0 / 6.283185307179586);			
																																
																																	
    std::string line1 = std::format("1 {:05d}U 26188A   26188.00000000  .00000000  00000-0  00000-0 0    0", n_satellite);			
																																	
   
    std::string line2 = std::format("2 {:05d} {:8.4f} {:8.4f} {:07d} {:8.4f} {:8.4f} {:11.8f}0",
        n_satellite,
        parametrs.Inclination,
        parametrs.LongitudeOfTheAscendingNode,
        (int)(parametrs.Eccentricity * 10000000),
        parametrs.ArgumentOfPericenter,
        parametrs.MeanAnomaly,
        n_orbits);

    
    line1.resize(69, ' ');
    line2.resize(69, ' ');

    return { line1, line2 };
}
