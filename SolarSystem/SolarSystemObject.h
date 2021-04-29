#pragma once

#include "Object.h"

namespace SolarSystemModel {
	class SolarSystemObject;
	using SolarSystemObjectPtr = std::shared_ptr<SolarSystemObject>;

	struct SolarSystemObjectParameters {
		float radius, orbitRadius, angleVelocity, orbitAngleVelocity;
	};
	
	class SolarSystemObject : public Object {
	public:
		explicit SolarSystemObject(std::string&& name, const SolarSystemObjectParameters& params);

		void SetBoostFactor(float factor);
		SolarSystemObjectParameters GetParams() const;

	protected:
		bool InitMesh() override;
		void Update() override;
		
		SolarSystemObjectParameters _params;
		float _boostFactor = 1.f;
	};

	class SolarSystemDependentObject : public SolarSystemObject {
	public:
		SolarSystemDependentObject(std::string&& name,
			const SolarSystemObjectParameters& params, const SolarSystemObject& connectedObj);
	private:
		void Update() override;
		
		const SolarSystemObject& _connectedObj;
	};

	class Rings final : public SolarSystemDependentObject {
	public:
		Rings(std::string&& name,
			const SolarSystemObjectParameters& params, const SolarSystemObject& connectedObj);
	private:
		bool InitMesh() override;
	};
}