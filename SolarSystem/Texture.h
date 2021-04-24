#pragma once

#include <QOpenGLTexture>

using TexturePtr = std::shared_ptr<QOpenGLTexture>;
using Textures = std::vector<TexturePtr>;