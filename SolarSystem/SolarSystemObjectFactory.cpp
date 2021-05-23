#include "SolarSystemObjectFactory.h"

using namespace SolarSystemModel;

const static std::map<std::string, SolarSystemObjectParameters> rParameters {
	{"Sun", {6.96f, 0.f, 0.203f, 0.f}},
	{"Mercury", {0.024f, 57.9f, 0.045f, 0.0297f}},
	{"Venus", {0.061f, 108.2f, -0.011f, 0.0117f}},
	{"Earth", {0.064f, 149.6f, 2.618f, 0.0072f}},
	{"Moon", {0.017f, 0.384f, 0.966f, 0.3663f}},
	{"Mars", {0.034f, 227.9f, 2.554f, 0.0038f}},
	{"Jupiter", {0.715f, 778.6f, 6.347f, 0.0006f}},
	{"Saturn", {0.603f, 1433.5f, 5.872f, 0.0002f}},
	{"Uranus", {0.256f, 2872.5f, -3.653f, 0.0001f}},
	{"Neptune", {0.248f, 4495.1f, 3.903f, 0.0001f}},
	{"SaturnRings", {0.015f, 0.8f, 0.f, 0.5f}}
};

const static std::map<std::string, SolarSystemObjectParameters> dParameters {
	{"Sun", {	1.0f, 0.f, 0.203f, 0.f}},
	{"Mercury", {0.024f, 2.f, 0.045f, 0.0297f}},
	{"Venus", {0.061f, 4.f, -0.011f, 0.0117f}},
	{"Earth", {0.064f, 6.f, 2.618f, 0.0072f}},
	{"Moon", {0.017f, 0.384f, 0.966f, 0.3663f}},
	{"Mars", {0.034f, 10.f, 2.554f, 0.0038f}},
	{"Jupiter", {0.615f, 12.f, 6.347f, 0.0072f}},
	{"Saturn", {0.540f, 15.f, 5.872f, 0.0030f}},
	{"Uranus", {0.256f, 17.f, -3.653f, 0.0025f}},
	{"Neptune", {0.248f, 19.f, 3.903f, 0.002f}},
	{"SaturnRings", {0.015f, 0.8f, 0.f, 0.5f}}
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