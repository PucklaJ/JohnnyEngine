#pragma once
#include "../include/Texture.h"
#include <string>

namespace Johnny
{
	class ResourceManager;
	class TextureData;

	class CubeMap3D : public Texture
	{
	public:
		CubeMap3D(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back, ResourceManager*);
		CubeMap3D(TextureData* top, TextureData* bottom, TextureData* left, TextureData* right, TextureData* front, TextureData* back);
	};
}

