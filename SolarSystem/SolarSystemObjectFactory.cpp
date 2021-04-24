#include "SolarSystemObjectFactory.h"

SolarSystemModel::SolarSystemObjectPtr SolarSystemModel::SolarSystemObjectFactory::Create(std::string&& name)
{
	const static std::map<std::string, SolarSystemObjectParameters> parameters {
		{"Sun", {0.696f, 0.f, 0.1f, 0.f}},
		{"Mercury", {0.024f, 5.8f, 0.0045f, 0.07139f}},
		{"Venus", {0.061f, 10.8f, -0.0011f, 0.02796f}},
		{"Earth", {0.064f, 15.0f, 0.2618f, 0.01720f}},
		{"Mars", {0.034f, 22.8f, 0.2554f, 0.00914f}},
		{"Jupiter", {0.715f, 77.8f, 0.6347f, 0.00145f}},
		{"Saturn", {0.603f, 143.3f, 0.5872f, 0.00058f}},
		{"Uranus", {0.256f, 287.2f, -0.3653f, 0.00021f}},
		{"Neptune", {0.248f, 449.5f, 0.3903f, 0.00011f}}
	};
	
	if (parameters.find(name) == parameters.end()) {
		return nullptr;
	}
	return std::make_shared<SolarSystemObject>(std::move(name), parameters.at(name));
}
