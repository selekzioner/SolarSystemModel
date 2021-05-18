#pragma once

#include "Mesh.h"

class Object;
using ObjectPtr = std::shared_ptr<Object>;

class Object {
public:
	explicit Object(std::string&& name);
	virtual ~Object() = default;
	
	virtual void Initialize();
	virtual void Render(QOpenGLShaderProgram& program, const QMatrix4x4& view, const QMatrix4x4& proj);

	void SetPos(const QVector3D& pos);

	QMatrix4x4 GetModelMatrix() const;
	QVector3D GetPos() const;

	std::string Name() const;

	virtual void Update() = 0;

protected:
	virtual bool InitMesh();

	Mesh _mesh;
	std::string _name;

	QVector3D _pos = { 0.f, 0.f, 0.f };
	QMatrix4x4 _modelMatrix;
	unsigned _frame = 0;
};
