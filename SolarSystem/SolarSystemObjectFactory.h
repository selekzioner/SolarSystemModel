#pragma once

#include "SolarSystemObject.h"

namespace SolarSystemModel {
	enum class SolarSystemMode { Real, Demonstrative };
	
	class SolarSystemObjectFactory {
	public:
		virtual ~SolarSystemObjectFactory() = default;
		static SolarSystemObjectPtr Create(std::string&& name);
		static inline SolarSystemMode mode;
	};

	class SolarSystemDependentObjectFactory final : public SolarSystemObjectFactory {
	public:
		static SolarSystemObjectPtr Create(std::string&& name, const SolarSystemObject& connectedObj);
	};

	class SaturnRingsFactory final : public SolarSystemObjectFactory {
	public:
		static SolarSystemObjectPtr Create(std::string&& name, const SolarSystemObject& connectedObj);
	};
}