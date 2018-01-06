#ifndef TILED_MAP_H
#define TILED_MAP_H
#include "Sprite2D.h"
#include <TMX/Tmx.h>
#include <string>
#include <vector>
#include "Physics2D.h"
#include "Geometry.h"
#include <map>

namespace Johnny
{
    class FrameBuffer;
    class RenderTexture;
    
    /*! \brief A struct which represents a tile that is animated
     *
     */
	struct AnimationTile
	{
		int x;      //!< The x position of the tile in pixels
        int y;      //!< The y position of the tile in pixels
		int animID; //!< The id of the animation
		int layer;  //!< The index of the layer
	};

    /*! \brief A struct which represents a animation that animates a tile
     *
     */
	struct TileAnimation
	{
		std::vector<TextureRegion> regions; //!< The TextureRegions of the key frames on the tileset
		std::vector<int> times;             //!< The duration of each key frame in ms
		Texture* texture;                   //!< The Texture of the tileset
		int curRegion;                      //!< The index of the current TextureRegion
		int curTime;                        //!< The current time of the key frame
	};

    /*! \brief A class which represents a map created with Tiled as an Actor
     *
     */
    class TiledMap : public Sprite2D, public Tmx::Map
    {
    public:
        /*! \brief Creates a new TiledMap
         *  \param file The file path of the .tmx file
         */
        TiledMap(const std::string& file);
        ~TiledMap();
        
        /*! \brief The init method
         *
         *
         * It is overriding the method from Sprite2D
         */
        bool init() override;
        /*! \brief The update method
         *
         *
         * It is overriding the method from Sprite2D
         */
        bool update() override;
        /*! \brief The render method
         *
         *
         * It is overriding the method from Sprite2D
         */
        bool render() override;
        /*! \brief The quit method
         *
         *
         * It is overriding the method from Sprite2D
         */
        void quit() override;
        
        /*! \brief An array of b2Bodies which have been created with this TiledMap
         *
         */
        std::vector<b2Body*>* getBodies() {return &m_bodies;}
        /*! \brief Converts a Tmx::Object to a b2Body
         *  \param obj The Tmx::Object to convert
         *  \return The created b2Body
         */
        b2Body* toCollisionBody(const Tmx::Object* obj);
        /*! \brief Defines if the Tmx::Objects should be renderd (unused)
         *
         */
        void setRenderObjects(bool b) {m_renderObjects = b;}
        
        /*! \brief Destroys a tile at a given position
         *  \param x The x position of the tile
         *  \param y The y position of the tile
         *  \param layer The index of the layer of the tile
         */
        void destroyTile(int x,int y,int layer);
        /*! \brief Sets a tile at a given position
         *  \param x The x position of the tile
         *  \param y The y position of the tile
         *  \param layer The layer index of the tile
         *  \param tileset The tileset index from which to take the tile
         *  \param id The id of the tile to set on the tileset
         */
        void setTile(int x,int y,int layer,int tileset,int id);
        
        /*! \return An array of the loaded tilesets
         *
         */
        std::vector<Texture*>& getTilesetTextures() {return m_tilesetTextures;}
        /*! \return An array of the textures of the layers
         *
         */
        std::vector<RenderTexture*>& getLayerTextures() {return m_renderTextures;}

    private:
        /*! \param tileset The tileset to get the id from
         *  \return The id of the tileset
         */
        int getIDofTileset(const Tmx::Tileset* tileset);
        /*! \brief Gets a tileset with a given index
         *  \param index The index of the tileset
         *  \return The tileset with the index
         */
        const Tmx::Tileset* getTileset(int index);
        /*! \brief Gets the source region of a tile
         *  \param srcRegion The TextureRegion where to store the result
         *  \param gid The GID of the tile
         */
        void getSrcRegionForTileGID(TextureRegion* srcRegion,int gid);
        /*! \brief Gets the source region of a tile
         *  \param srcRegion The TextureRegion where to store the result
         *  \param numTilesX The number of tiles of the tileset on the x-Axis
         *  \param index The index of the tileset
         *  \param id The id of the tile
         */
        void getSrcRegionForTileID(TextureRegion* srcRegion,int numTilesX,int index,int id);
        /*! \brief Gets the id of a tile
         *  \param gid The GID of the tile
         *  \return The id of the tile
         */
        int getTileIDForTileGID(int gid);
        /*! \brief converts a hex color string into a Colorb
         *  \param str The hex string to convert
         *  \return The converted color
         */
        Colorb colorStringToColor(const std::string& str);
        
        /*! \brief Loads the main texture
         *
         */
        void loadTexture();
        /*! \brief Loads all data for the tilesets
         *
         */
        void loadTilesets();
        /*! \brief Loads all data of the layers
         *
         */
        void loadLayers();
        
        /*! \brief Loads a tile layer
         *  \param layer THe tile layer to load 
         *  \param layerindex The index of the layer
         */
        void loadTileLayer(const Tmx::TileLayer* layer,int layerindex);
        /*! \brief Loads a object group
         *  \param obj The object group to load
         */
        void loadObjectGroup(const Tmx::ObjectGroup* obj);
        /*! \brief Loads a image layer
         *  \param layer The image layer to load
         */
        void loadImageLayer(const Tmx::ImageLayer* layer);
        
        /*! \brief Loads all collision objects of a tile
         *  \param tile The tile to load the collision objects from
         *  \param x The x position of the tile
         *  \param y The y position of the tile
         */
        void loadCollisionObjects(const Tmx::Tile* tile,int x,int y);
        /*! \brief Loads a ellipse as b2Body
         *  \param obj The object to load the ellipse from
         *  \param x The x position of the object
         *  \param y The y position of the object 
         */
        void loadCollisionEllipse(const Tmx::Object* obj,int x,int y);
        /*! \brief Loads a polygon as b2Body
         *  \param obj The object to load the polygon from
         *  \param x The x position of the object
         *  \param y The y position of the object 
         */
        void loadCollisionPolygon(const Tmx::Object* obj,int x,int y);
        /*! \brief Loads a polyline as b2Body
         *  \param obj The object to load the polyline from
         *  \param x The x position of the object
         *  \param y The y position of the object 
         */
        void loadCollisionPolyline(const Tmx::Object* obj,int x,int y);
        /*! \brief Loads a rectangle as b2Body
         *  \param obj The object to load the rectangle from
         *  \param x The x position of the object
         *  \param y The y position of the object 
         */
        void loadCollisionRectangle(const Tmx::Object* obj,int x,int y);
        
        /*! \brief Loads all tile animations
         *  \param layer The tile layer to load the animations from
         *  \param index The layer index of the tile layer
         */
        void loadAnimations(const Tmx::TileLayer* layer,int index);
        /*! \brief Updates all tile animations
         *
         */
        void updateAnimations();
        /*! \brief Renderes all tile animations
         *
         */
        void renderAnimations();

        /*! \brief Adds a layer texture
         *
         */
        void addTexture();
        /*! \brief Renders all layers
         *
         */
        void renderLayers();

        bool m_works = true;                                      //!< true of the .tmx file could be loaded
        int* m_tilesX = nullptr;                                  //!< An array with all amounts of tiles on the x-Axis of the tilesets
        Colorb m_background;                                      //!< The background color of the map
        std::vector<b2Body*> m_bodies;                            //!< An array with all bodies loaded with the map
        std::map<int,TileAnimation> m_animations;                 //!< A map which stores all TileAnimations
        std::vector<AnimationTile> m_animTiles;                   //!< An array with all animated tiles
        std::vector<RenderTexture*> m_renderTextures;             //!< An array with all layer textures
        FrameBuffer* m_mainTextureFrameBuffer = nullptr;          //!< The FrameBuffer which is used to render on the main texture
        std::map<Texture*,FrameBuffer*> m_frameBuffersOfTileSets; //!< The map which stores the FrameBuffers of the tileset textures
        Texture* m_clearTexture = nullptr;                        //!< The texture which is used for clearing some tiles
        bool m_renderObjects = false;                             //!< Defines wether to render the objects
        
        std::vector<Texture*> m_tilesetTextures;                  //!< An array which stores all tileset textures
    };
}

#endif
