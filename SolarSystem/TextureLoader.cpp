#include "TextureLoader.h"

TLResult TextureLoader::Load(const std::string& path, TexturePtr& texture)
{
	const auto textureImage = QImage(path.c_str());

	if (!textureImage.isNull()) {
		texture.reset(new QOpenGLTexture(textureImage));
		texture->setWrapMode(QOpenGLTexture::MirroredRepeat);
		texture->setMinificationFilter(QOpenGLTexture::Nearest);
		return TLResult::tlOK;
	}
	return TLResult::tlFAIL;
}
