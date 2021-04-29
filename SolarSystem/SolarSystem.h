#pragma once

#include "SolarSystemObject.h"
#include "Camera.h"
#include "SolarSystemObjectFactory.h"

namespace SolarSystemModel {
	enum class SolarSystemMode;

	class SolarSystem {
	public:
		void Initialize();
		void Render(const Camera& camera);
		void Reset(SolarSystemMode mode = SolarSystemMode::Real);

		void Boost(float factor);

		SolarSystemObjectPtr GetObj(const std::string& name) const;
	private:
		QOpenGLShaderProgram _shader;
		QOpenGLFunctions_3_0 _openGlFunctions;
		
		std::vector<SolarSystemObjectPtr> _objects;
	};
}

