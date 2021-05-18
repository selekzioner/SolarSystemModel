#include "Mesh.h"

Mesh::Mesh()
: _vertexBuf(QOpenGLBuffer::VertexBuffer), _indexBuf(QOpenGLBuffer::IndexBuffer)
{
}

Mesh::~Mesh()
{
  _vertexBuf.destroy();
  _indexBuf.destroy();
}

void Mesh::Initialize()
{
  _openGlFunctions.initializeOpenGLFunctions();
	
  _vertexBuf.create();
	_indexBuf.create();

  _vertexBuf.bind();
  _vertexBuf.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(Vertex)));
  _indexBuf.bind();
  _indexBuf.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(unsigned)));
}

void Mesh::Render(QOpenGLShaderProgram& program)
{
  _vertexBuf.bind();
  _indexBuf.bind();

  _openGlFunctions.glEnable(GL_DEPTH_TEST);
	
  program.enableAttributeArray("posAttr");
  program.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(Vertex));

  program.enableAttributeArray("texAttr");
  program.setAttributeBuffer("texAttr", GL_FLOAT, offsetof(Vertex, texCoord), 2, sizeof(Vertex));

  if (textures[0]) {
    program.setUniformValue("Texture", 0);
    _openGlFunctions.glActiveTexture(GL_TEXTURE0);
    textures[0]->bind();
  }

  _openGlFunctions.glPolygonMode(GL_FRONT, GL_FILL);
  _openGlFunctions.glDrawElements(GL_TRIANGLES, _indexBuf.size(), GL_UNSIGNED_INT, nullptr);

  _openGlFunctions.glDisable(GL_DEPTH_TEST);
}