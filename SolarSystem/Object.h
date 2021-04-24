#pragma once

#include "Mesh.h"

class Object;
using ObjectPtr = std::shared_ptr<Object>;

class Object {
public:
	explicit Object(std::string&& name);
	virtual ~Object() = default;
	
	void Initialize();
	void Render(QOpenGLShaderProgram& program);

	QMatrix4x4 GetModelMatrix() const;
	QVector3D GetPos() const;

	std::string Name() const;

protected:
	virtual bool InitMesh();
	virtual void Update() = 0;
	
	Mesh _mesh;
	std::string _name;

	QVector3D _pos = { 0.f, 0.f, 0.f };
	QMatrix4x4 _modelMatrix;
	unsigned _frame = 0;
};
