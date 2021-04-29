#define _USE_MATH_DEFINES

#include <cmath>

#include "SolarSystemObject.h"

using namespace SolarSystemModel;

SolarSystemObject::SolarSystemObject(std::string&& name, const SolarSystemObjectParameters& params)
: Object(std::move(name)), _params(params)
{
}

void SolarSystemObject::SetBoostFactor(const float factor)
{
	const auto newFrame = _boostFactor * static_cast<float>(_frame) / factor;
	_boostFactor = factor;
	_frame = static_cast<unsigned>(newFrame);
}

SolarSystemObjectParameters SolarSystemObject::GetParams() const
{
	return _params;
}

bool SolarSystemObject::InitMesh()
{
	const auto lats = 100;
	const auto longs = 100;
	
	const auto latStep = 2 * static_cast<float>(M_PI) / lats;
	const auto longStep = static_cast<float>(M_PI) / longs;
	Vertex vertex;

	for (auto i = 0u; i <= static_cast<unsigned>(longs); ++i) {
		const auto stackAngle = static_cast<float>(M_PI / 2) - static_cast<float>(i) * longStep;
		const auto xy = _params.radius * cos(stackAngle);
		const auto z = _params.radius * sin(stackAngle);

		for (auto j = 0u; j <= static_cast<unsigned>(lats); ++j) {
			const auto sectorAngle = static_cast<float>(j) * latStep;

			const auto x = xy * cos(sectorAngle);
			const auto y = xy * sin(sectorAngle);
			vertex.pos = { x, y, z };

			vertex.texCoord = { static_cast<float>(j) / lats , static_cast<float>(i) / longs };

			_mesh.vertices.push_back(vertex);
		}
	}

	for (auto i = 0u; i < lats; ++i) {
		auto k1 = i * (longs + 1);
		auto k2 = k1 + longs + 1;

		for (auto j = 0u; j < longs; ++j, ++k1, ++k2) {
			if (i != 0) {
				_mesh.indices.push_back(k1);
				_mesh.indices.push_back(k2);
				_mesh.indices.push_back(k1 + 1u);
			}

			if (i != (lats - 1)) {
				_mesh.indices.push_back(k1 + 1u);
				_mesh.indices.push_back(k2);
				_mesh.indices.push_back(k2 + 1u);
			}
		}
	}
	return true;
}

void SolarSystemObject::Update()
{
	_modelMatrix.setToIdentity();
	const auto orbitAngleVelocity =_params.orbitAngleVelocity * _boostFactor;
	const auto angleVelocity =_params.angleVelocity * _boostFactor;

	_pos.setX(_params.orbitRadius
		* cos(orbitAngleVelocity * static_cast<float>(_frame)));
	_pos.setZ(_params.orbitRadius
		* sin(orbitAngleVelocity * static_cast<float>(_frame)));
	_modelMatrix.translate(_pos);

	_modelMatrix.rotate(angleVelocity
		* static_cast<float>(_frame), 0.f, 1.f, 0.f);
	_modelMatrix.rotate(-90.f, 1, 0, 0);

	++_frame;
}

SolarSystemDependentObject::SolarSystemDependentObject(std::string&& name,
	const SolarSystemObjectParameters& params, const SolarSystemObject& connectedObj)
: SolarSystemObject(std::move(name), params), _connectedObj(connectedObj)
{
}

void SolarSystemDependentObject::Update()
{
	_modelMatrix.setToIdentity();
	const auto orbitAngleVelocity = _params.orbitAngleVelocity * _boostFactor;
	const auto angleVelocity = _params.angleVelocity * _boostFactor;

	_pos.setX(_connectedObj.GetPos().x() + _params.orbitRadius
		* cos(orbitAngleVelocity * static_cast<float>(_frame)));
	_pos.setZ(_connectedObj.GetPos().z() + _params.orbitRadius
		* sin(orbitAngleVelocity * static_cast<float>(_frame)));
	_modelMatrix.translate(_pos);

	_modelMatrix.rotate(angleVelocity
		* static_cast<float>(_frame), 0.f, 1.f, 0.f);
	_modelMatrix.rotate(-90.f, 1, 0, 0);

	++_frame;
}
