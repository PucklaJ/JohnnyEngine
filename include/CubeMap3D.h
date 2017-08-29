#pragma once
#include "../include/Texture.h"
#include <string>

namespace Johnny
{
	class ResourceManager;
	class TextureData;

	/*! \brief This is a CubeMapTexture
	 *
	 */
	class CubeMap3D : public Texture
	{
	public:
		/*! \brief Creates a new CubeMap3D from files
		 * \param top The filepath of the texture used for the top plane
		 * \param bottom The filepath of the texture used for the bottom plane
		 * \param left The filepath of the texture used for the left plane
		 * \param right The filepath of the texture used for the right plane
		 * \param front The filepath of the texture used for the front plane
		 * \param back The filepath of the texture used for the back plane
		 * \param res The resource manager form which to load the texturefiles
		 */
		CubeMap3D(const std::string& top, const std::string& bottom, const std::string& left, const std::string& right, const std::string& front, const std::string& back, ResourceManager* res);
		/*! \brief Creates a new CubeMap3D from TextureDatas
		 * \param top The TextureData of the texture used for the top plane
		 * \param bottom The TextureData of the texture used for the bottom plane
		 * \param left The TextureData of the texture used for the left plane
		 * \param right The TextureData of the texture used for the right plane
		 * \param front The TextureData of the texture used for the front plane
		 * \param back The TextureData of the texture used for the back plane
		 */
		CubeMap3D(TextureData* top, TextureData* bottom, TextureData* left, TextureData* right, TextureData* front, TextureData* back);
	};
}

