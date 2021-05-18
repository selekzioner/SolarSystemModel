#include "SolarSystemObjectFactory.h"

using namespace SolarSystemModel;

const static std::map<std::string, SolarSystemObjectParameters> rParameters {
	{"Sun", {6.96f, 0.f, 0.0203f, 0.f}},
	{"Mercury", {0.024f, 57.9f, 0.045f, 0.07139f}},
	{"Venus", {0.061f, 108.2f, -0.021f, 0.02796f}},
	{"Earth", {0.064f, 149.6f, 0.2618f, 0.01720f}},
	{"Moon", {0.017f, 0.384f, 0.0966f, 0.03663f}},
	{"Mars", {0.034f, 227.9f, 0.2554f, 0.00914f}},
	{"Jupiter", {0.715f, 778.6f, 0.6347f, 0.00145f}},
	{"Saturn", {0.603f, 1433.5f, 0.5872f, 0.00058f}},
	{"Uranus", {0.256f, 2872.5f, -0.3653f, 0.00021f}},
	{"Neptune", {0.248f, 4495.1f, 0.3903f, 0.00011f}},
	{"SaturnRings", {0.015f, 0.8f, 0.f, 0.05f}}
};

const static std::map<std::string, SolarSystemObjectParameters> dParameters {
	{"Sun", {	1.0f, 0.f, 0.0203f, 0.f}},
	{"Mercury", {0.024f, 2.f, 0.045f, 0.07139f}},
	{"Venus", {0.061f, 4.f, -0.021f, 0.02796f}},
	{"Earth", {0.064f, 6.f, 0.2618f, 0.01720f}},
	{"Moon", {0.017f, 0.384f, 0.0966f, 0.03663f}},
	{"Mars", {0.034f, 10.f, 0.2554f, 0.0914f}},
	{"Jupiter", {0.715f, 12.f, 0.6347f, 0.09f}},
	{"Saturn", {0.603f, 14.f, 0.5872f, 0.058f}},
	{"Uranus", {0.256f, 16.f, -0.3653f, 0.021f}},
	{"Neptune", {0.248f, 18.f, 0.3903f, 0.011f}},
	{"SaturnRings", {0.015f, 0.8f, 0.f, 0.05f}}
};

SolarSystemObjectPtr SolarSystemObjectFactory::Create(std::string&& name)
{
	const auto& parameters = mode == SolarSystemMode::Real ? rParameters : dParameters;
	if (parameters.find(name) == parameters.end()) {
		return nullptr;
	}
	return std::make_shared<SolarSystemObject>(std::move(name), parameters.at(name));
}

SolarSystemObjectPtr SolarSystemDependentObjectFactory::Create(std::string&& name, const SolarSystemObject& connectedObj)
{
	const auto& parameters = mode == SolarSystemMode::Real ? rParameters : dParameters;
	if (parameters.find(name) == parameters.end()) {
		return nullptr;
	}
	return std::make_shared<SolarSystemDependentObject>(std::move(name), parameters.at(name), connectedObj);
}

SolarSystemObjectPtr SaturnRingsFactory::Create(std::string&& name, const SolarSystemObject& connectedObj)
{
	const auto& parameters = mode == SolarSystemMode::Real ? rParameters : dParameters;
	if (parameters.find(name) == parameters.end()) {
		return nullptr;
	}
	return std::make_shared<SaturnRings>(std::move(name), parameters.at(name), connectedObj);
}