#ifndef TILED_MAP_H
#define TILED_MAP_H
#include "Sprite2D.h"
#include "TMX/Tmx.h"
#include <string>
#include <vector>
#include "Physics2D.h"
#include "Geometry.h"
#include <map>

namespace Johnny
{
    class FrameBuffer;
    class RenderTexture;
    
	struct AnimationTile
	{
		int x,y;
		int animID;
		int layer;
	};

	struct TileAnimation
	{
		std::vector<TextureRegion> regions;
		std::vector<int> times;
		Texture* texture;
		int curRegion;
		int curTime;
	};

    class TiledMap : public Sprite2D, public Tmx::Map
    {
    public:
        TiledMap(const std::string& file);
        ~TiledMap();
        
        bool init() override;
        bool update() override;
        bool render() override;
        void quit() override;
        
        std::vector<b2Body*>* getBodies() {return &m_bodies;}
        b2Body* toCollisionBody(const Tmx::Object*);
        void setRenderObjects(bool b) {m_renderObjects = b;}
        
        void destroyTile(int,int,int);
        void setTile(int,int,int,int,int);

    private:
        int getIDofTileset(const Tmx::Tileset*);
        const Tmx::Tileset* getTileset(int);
        void getSrcRegionForTileGID(TextureRegion*,int);
        void getSrcRegionForTileID(TextureRegion*,int,int,int);
        int getTileIDForTileGID(int);
        Colorb colorStringToColor(const std::string&);
        
        void loadTexture();
        void loadTilesets();
        void loadLayers();
        
        void loadTileLayer(const Tmx::TileLayer*,int);
        void loadObjectGroup(const Tmx::ObjectGroup*);
        void loadImageLayer(const Tmx::ImageLayer*);
        
        void loadCollisionObjects(const Tmx::Tile*,int,int);
        void loadCollisionEllipse(const Tmx::Object*,int,int);
        void loadCollisionPolygon(const Tmx::Object*,int,int);
        void loadCollisionPolyline(const Tmx::Object*,int,int);
        void loadCollisionRectangle(const Tmx::Object*,int,int);
        
        void loadAnimations(const Tmx::TileLayer*,int);
        void updateAnimations();
        void renderAnimations();

        void addTexture();
        void renderLayers();

        bool m_works = true;
        int* m_tilesX = nullptr;
        Colorb m_background;
        std::vector<b2Body*> m_bodies;
        std::map<int,TileAnimation> m_animations;
        std::vector<AnimationTile> m_animTiles;
        std::vector<RenderTexture*> m_renderTextures;
        FrameBuffer* m_mainTextureFrameBuffer = nullptr;
        std::map<Texture*,FrameBuffer*> m_frameBuffersOfTileSets;
        Texture* m_clearTexture = nullptr;
        bool m_renderObjects = false;
    };
}

#endif
