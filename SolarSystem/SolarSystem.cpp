#include "SolarSystem.h"
#include "SolarSystemObjectFactory.h"

using namespace SolarSystemModel;

void SolarSystem::Initialize()
{
  _shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/object.vsh");
  _shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/object.fsh");
  _shader.link();
  _shader.bind();

  _objects.push_back(SolarSystemObjectFactory::Create("Sun"));
  _objects.push_back(SolarSystemObjectFactory::Create("Mercury"));
  _objects.push_back(SolarSystemObjectFactory::Create("Venus"));
  _objects.push_back(SolarSystemObjectFactory::Create("Earth"));
  _objects.push_back(SolarSystemObjectFactory::Create("Mars"));
  _objects.push_back(SolarSystemObjectFactory::Create("Jupiter"));
  _objects.push_back(SolarSystemObjectFactory::Create("Saturn"));
  _objects.push_back(SolarSystemObjectFactory::Create("Uranus"));
  _objects.push_back(SolarSystemObjectFactory::Create("Neptune"));

  for (auto& obj : _objects) {
    obj->Initialize();
  }
}

void SolarSystem::Render(const Camera& camera)
{
  QMatrix4x4 projection;
  projection.perspective(30.f, 1.7f, 0.1f, 100000.0f);

  for (auto& obj : _objects) {
    const auto matrix = projection * camera.GetViewMatrix() * obj->GetModelMatrix();
    _shader.setUniformValue("MVPmatrix", matrix);

    obj->Render(_shader);
  }
}

SolarSystemObjectPtr SolarSystem::GetObj(const std::string& name) const
{
  const auto it = std::find_if(_objects.begin(), _objects.end(),
  [&](const SolarSystemObjectPtr& obj) {
		return obj->Name() == name;
	});
  if (it == _objects.end()) {
    return nullptr;
  }
  return *it;
}
