#pragma once
#include <vector>
#include <QVector3D>
#include <QVector2D>

struct Vertex {
	QVector3D pos;
	QVector2D texCoord;
};

using Vertices = std::vector<Vertex>;
using Indices = std::vector<unsigned>;