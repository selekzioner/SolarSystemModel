#version 330

in vec3 posAttr;
in vec2 texAttr;

uniform mat4 MVPmatrix;

out vec2 texCoord;

void main()
{
  texCoord = texAttr;
  gl_Position = MVPmatrix * vec4(posAttr, 1.0f);
}
