#version 330

uniform sampler2D Texture;
in vec2 texCoord;

void main(void)
{
  gl_FragColor = texture2D(Texture, texCoord);
}
