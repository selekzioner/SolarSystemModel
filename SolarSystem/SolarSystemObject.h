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

		virtual void SetBoostFactor(float factor);
		SolarSystemObjectParameters GetParams() const;
		
		void Update() override;
	protected:
		bool InitMesh() override;
		
		SolarSystemObjectParameters _params;
		float _boostFactor = 1.f;
		bool _isStoped = false;
	};

	class SolarSystemDependentObject final : public SolarSystemObject {
	public:
		SolarSystemDependentObject(std::string&& name,
			const SolarSystemObjectParameters& params, const SolarSystemObject& connectedObj);
	private:
		void Update() override;
		
		const SolarSystemObject& _connectedObj;
	};

	class SaturnRings final : public SolarSystemObject {
	public:
		SaturnRings(std::string&& name,
			const SolarSystemObjectParameters& params, const SolarSystemObject& connectedObj);

		void SetBoostFactor(float factor) override;
		
		void Initialize() override;
		void Render(QOpenGLShaderProgram& program, const QMatrix4x4& view, const QMatrix4x4& proj) override;

	private:
		static void InitRing(std::vector<SolarSystemObjectPtr>& rings, 
			SolarSystemObjectParameters& params, size_t beginIdx, size_t endIdx);
		void Update() override;
		
		std::vector<SolarSystemObjectPtr> _rings;
		unsigned _number = 400;
		
		const SolarSystemObject& _saturn;
	};
}