#pragma once

#include "Object.h"

namespace SolarSystemModel {
	class SolarSystemObject;
	using SolarSystemObjectPtr = std::shared_ptr<SolarSystemObject>;

	struct SolarSystemObjectParameters {
		float radius, orbitRadius, angleVelocity, orbitAngleVelocity;
	};
	
	class SolarSystemObject : public Object
	{
	public:
		explicit SolarSystemObject(std::string&& name, const SolarSystemObjectParameters& params);

		SolarSystemObjectParameters GetParams() const;

	protected:
		bool InitMesh() override;
		void Update() override;
	
	private:
		SolarSystemObjectParameters _params;
	};
}