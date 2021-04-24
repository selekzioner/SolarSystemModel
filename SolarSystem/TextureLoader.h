#pragma once

#include "Texture.h"

enum class TLResult { tlOK = 1, tlFAIL = 0 };

class TextureLoader final {
public:
	static TLResult Load(const std::string& path, TexturePtr& texture);
};

