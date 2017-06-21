#pragma once
#include "Texture.h"
#include <string>

namespace SDL
{
	class ResourceManager;
}

class TextureData;

class CubeMap : public Texture
{
public:
	CubeMap(const std::string& top,const std::string& bottom,const std::string& left,const std::string& right,const std::string& front, const std::string& back,SDL::ResourceManager*);
	CubeMap(TextureData* top, TextureData* bottom, TextureData* left, TextureData* right, TextureData* front, TextureData* back);
};

