#include "Object.h"
#include "MeshLoader.h"
#include "TextureLoader.h"

Object::Object(std::string&& name)
: _name(name)
{
}

void Object::Initialize()
{
	if (!InitMesh()) {
		return;
	}
	_mesh.Initialize();

	_mesh.textures.resize(1);
	TextureLoader::Load(std::string("Textures/" + _name + ".jpg"), _mesh.textures[0]);
}

void Object::Render(QOpenGLShaderProgram& program)
{
	Update();
	_mesh.Render(program);
}

QMatrix4x4 Object::GetModelMatrix() const
{
	return _modelMatrix;
}

QVector3D Object::GetPos() const
{
	return _pos;
}

std::string Object::Name() const
{
	return _name;
}

bool Object::InitMesh()
{
	if (MeshLoader::Load(std::string("Meshes/" + _name + ".obj"),
		_mesh.vertices, _mesh.indices) == MLResult::mlFAIL) {
		return false;
	}
	return true;
}

