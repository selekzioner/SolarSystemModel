#pragma once

#include "SolarSystemObject.h"
#include "Camera.h"

namespace SolarSystemModel {
	class SolarSystem {
	public:
		void Initialize();
		void Render(const Camera& camera);

		SolarSystemObjectPtr GetObj(const std::string& name) const;
	private:
		QOpenGLShaderProgram _shader;
		std::vector<SolarSystemObjectPtr> _objects;
	};
}

