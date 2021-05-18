#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_0>

#include "Vertex.h"
#include "Texture.h"

class Mesh;
using MeshPtr = std::unique_ptr<Mesh>;

class Mesh final {
public:
	Mesh();
	~Mesh();

	void Initialize();
	void Render(QOpenGLShaderProgram& program);

	Vertices vertices;
	Indices indices;
	Textures textures;

private:
	QOpenGLBuffer _vertexBuf, _indexBuf;
	QOpenGLFunctions_3_0 _openGlFunctions;
};
