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
		_camera.up = {0.f, 1.f, 0.f};
		_magnification = 7;
	}
	else {
		_camera.pos = { 0.f,  100.f,  0.f };
		_camera.front = { 0.f, -1.f, 0.f };
		_camera.up = { 0.f, 0.f, 1.f };
	}
}

void SolarSystemCameraAdapter::Update()
{
	if (_connectedObj) {
		/*auto newPos = _connectedObj->GetPos();
		newPos.setZ(newPos.z() - _magnification * _connectedObj->GetParams().radius);
		_camera.pos = newPos;
		_camera.front =  - newPos + _connectedObj->GetPos();*/
		const auto radius = _magnification * _connectedObj->GetParams().radius;
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
		const auto radius = _camera.pos.distanceToPoint(_connectedObj->GetPos());
		_anglePhi += _cameraVelocity * normDir.x();
		_angleThetta += _cameraVelocity * normDir.y();

		_anglePhi = _anglePhi < 360.f - _cameraVelocity / 2 ? _anglePhi : 0.f;
		_angleThetta = _angleThetta < 360.f - _cameraVelocity / 2 ? _angleThetta : 0.f;
		//_angle += _cameraAngleVelocity;
		//_angle = _angle < 360.f - _cameraAngleVelocity / 2 ? _angle : 0.f;
		/*_camera.pos.setX(normDir.x() * radius * cos(_angle));
		_camera.pos.setY(normDir.y() * radius * sin(_angle));
		_camera.pos.setZ(normDir.z() * radius * sin(_angle));*/
		//_camera.front = _connectedObj->GetPos() - _camera.pos;
	}
	else {
		_camera.pos.setX(_camera.pos.x() + normDir.x() * _cameraVelocity);
		_camera.pos.setY(_camera.pos.y() + normDir.y() * _cameraVelocity);
	}
	
}

void SolarSystemCameraAdapter::SetMagnification(const unsigned magnification)
{
	_magnification = magnification;
}

const Camera& SolarSystemCameraAdapter::GetCamera() const
{
	return _camera;
}
