#pragma once

#include "SolarSystemObject.h"

namespace SolarSystemModel {
	class SolarSystemObjectFactory {
	public:
		static SolarSystemObjectPtr Create(std::string&& name);
	};
}