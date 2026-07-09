#pragma once
#include <string>
#include <perturb/perturb.hpp>

struct OrbitParameters
{											// структура с параметрами, которые нам нужно будет рандомно генерировать для TLE
	double RadiusOfTheOrbit;
	double Eccentricity;
	double Inclination;
	double LongitudeOfTheAscendingNode;
	double ArgumentOfPericenter;
	double MeanAnomaly;
};

struct TLE								// структура, которая хранит готовый TLE
{
	std::string TLE_1;
	std::string TLE_2;
};

struct SatelliteState {              // структура, для хранения обработанных TLE 
	perturb::Satellite sat; 

};


struct Position						// структура, для хранения координат
{
	double x;
	double y;
	double z;
};