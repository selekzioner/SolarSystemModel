#define _USE_MATH_DEFINES

#include "SolarSystemCameraAdapter.h"

using namespace SolarSystemModel;

SolarSystemCameraAdapter::SolarSystemCameraAdapter(SolarSystem& solarSystem)
: _solarSystem(solarSystem)
{
}

void SolarSystemCameraAdapter::ConnectWithObject(const std::string& name)
{
	_connectedObj = _solarSystem.GetObj(name);
	if (_connectedObj) {
		_camera.up = { 0.f, 1.f, 0.f };
		_magnification = 15;
	}
}

void SolarSystemCameraAdapter::Update()
{
	if (_connectedObj) {
		const auto radius = static_cast<float>(_magnification) * _connectedObj->GetParams().radius;
		_camera.pos.setX(_connectedObj->GetPos().x() + radius * cos (_angleThetta) * sin(_anglePhi));
		_camera.pos.setY(_connectedObj->GetPos().y() + radius * sin(_angleThetta));
		_camera.pos.setZ(_connectedObj->GetPos().z() + radius * cos(_angleThetta) * cos(_anglePhi));
		_camera.front = - _camera.pos + _connectedObj->GetPos();
	}
}

void SolarSystemCameraAdapter::Rotate(const QVector2D& dir)
{
	const auto normDir = dir.normalized();
	if (_connectedObj) {
		_anglePhi += _cameraVelocity * normDir.x();
		_angleThetta += _cameraVelocity * normDir.y();

		_anglePhi = _anglePhi < 2 * static_cast<float>(M_PI) - _cameraVelocity / 2 ? _anglePhi : 0.f;
		if (std::abs(_angleThetta) > static_cast<float>(M_PI) / 2 - _cameraVelocity / 2)
			_angleThetta -= _cameraVelocity * normDir.y();
	}
}

void SolarSystemCameraAdapter::Magnify(const int dir)
{
	const auto normDir = dir / std::abs(dir);
	const auto newMagn = _magnification + normDir;
	
	if (newMagn > 5 && newMagn < 100)
		_magnification = newMagn;
}

const Camera& SolarSystemCameraAdapter::GetCamera() const
{
	return _camera;
}

void SolarSystemCameraAdapter::SetDemonstrativeView()
{
	_connectedObj = _solarSystem.GetObj("Sun");
	_angleThetta = M_PI / 6;
	_magnification = 55;
}

void SolarSystemCameraAdapter::SetTopView()
{
	_connectedObj = _solarSystem.GetObj("Sun");
	_angleThetta = M_PI / 2 - _cameraVelocity / 2;
	_magnification = 75;
}
