#pragma once

#include "Camera.h"
#include "SolarSystem.h"

namespace SolarSystemModel {
	class SolarSystemCameraAdapter {
	public:
		explicit SolarSystemCameraAdapter(SolarSystem& solarSystem);
		
		void ConnectWithObject(const std::string& name);
		void Update();

		void Rotate(const QVector2D& dir);
		void Magnify(int dir);

		void SetDemonstrativeView();
		void SetTopView();
		
		const Camera& GetCamera() const;
	private:
		Camera _camera;
		SolarSystem& _solarSystem;
		SolarSystemObjectPtr _connectedObj;
		unsigned _magnification = 15;
		float _cameraVelocity = 0.05f;
		float _anglePhi = 0.f, _angleThetta = 0.f;
	};
}
