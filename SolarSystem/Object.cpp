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

void Object::Render(QOpenGLShaderProgram& program, const QMatrix4x4& view, const QMatrix4x4& proj)
{
	
	const auto matrix = proj * view * _modelMatrix;
	program.setUniformValue("MVPmatrix", matrix);
	_mesh.Render(program);
	Update();
}

void Object::SetPos(const QVector3D& pos)
{
	_pos = pos;
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

