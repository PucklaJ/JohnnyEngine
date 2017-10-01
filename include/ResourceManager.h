#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <vector>
#include <string>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

namespace Johnny
{
	class MainClass;
	class Texture;
	class Mesh3D;
	class Model3D;
	class SpotLight3D;
	class DirectionalLight3D;
	class PointLight3D;

	/*! \brief A class which stores data which is loaded in from Assimp
	 *
	 */
	class Scene
	{
	public:
		/*! \brief Adds the Model3Ds as Entity3Ds to a MainClass 
		 *  \param m The MainClass to add to
		 */
		void addAsEntities(MainClass* m);

		/*! \brief Gets a Model3D with a name from the loaded array
		 *  \param name The name of the Model3D to load
		 *  \return The Model3D with the given name and nullptr if no Model3D was found with that name
		 */
		Model3D* getModel(const std::string& name);

		std::vector<Model3D*> models;					    //!< All loaded Model3Ds
		std::vector<SpotLight3D*> spotLights;			    //!< All loaded SpotLight3Ds (unused)
		std::vector<DirectionalLight3D*> directionalLights; //!< All loaded DirectionLight3Ds (unused)
		std::vector<PointLight3D*> pointLights;				//!< All loaded PointLight3Ds (unused)
	};

	/*! \brief A class which stores data of a texture
	 *
	 */
	class TextureData
	{
	public:
		~TextureData();

		GLubyte* data = nullptr; //!< The pixel data
		GLsizei width = 0;		 //!< The width of the texture in pixels
		GLsizei height = 0;		 //!< The height of the texture in pixels
		GLint numChannels = 0;   //!< The number of channels in the texture
        
        /*! \brief Converts the TextureData into a Texture
         *  \param target The target to which the Texture should be bound
         *  \param filtering The filter method which should be applied
         *  \param format The format in which the pixels are stored
         *  \return The newly created Texture
         */
        Texture* toTexture(GLenum target = GL_TEXTURE_2D,GLenum filtering = GL_LINEAR,GLenum format = GL_RGBA);
        /*! \brief Converts to TextureData to a SDL_Surface
		 *  \param pixelFormat The format in which the pixels are stored
		 *  \return The newly created SDL_Surface
		 */
        SDL_Surface* toSDL_Surface(Uint32 pixelFormat = SDL_PIXELFORMAT_RGBA8888);
	};

	/*! \brief A class which handles all resources such as Textures, Models, Shaders etc.
	 *
	 */
    class ResourceManager
    {
        public:
            ResourceManager();
            virtual ~ResourceManager();

            /*! \brief Loads a Texture
             *  \param file The filepath of the texture relative to res/textures
             *  \param filtering The filtermethod which should be applied to the Texture
             *  \return The loaded Texture or nullptr if the file wasn't found
             */
            Texture* loadTexture(const std::string& file,GLenum filtering = GL_LINEAR);
            /*! \brief Loads the data of a texture
             *  \param file The file path of the texture relative to res/textures
             *  \return The TextureData of nullptr if the file wasn't found
             */
			TextureData* loadTextureData(const std::string& file);
			/*! \brief Loads the contents of a shader source file
			 *  \param file The file path of the source file from which to load the contents relative to res/shaders
			 *  \param defineChanges A map which contains defines and their values which will be changed in the shader source file (if nullptr no defines will be changed)
			 *  \return The contents of the shader source file or "" if the file wasn't found
			 */
			std::string loadShader(const std::string& file,std::map<std::string,std::string>* defineChanges = nullptr);
			/*! \brief Loads a .obj file with the OBJLoader
			 *  \param file The file path of the .obj file to load relative to res/models
			 *  \return The loaded Mesh3D or nullptr if the file wasn't found
			 */ 
			Mesh3D* loadMesh(const std::string& file);
			/*! \brief Loads a file with Assimp
			 *  \param file The file path of the file to load relative to res/models
			 *  \return The loaded Scene or nullptr if the file wasn't found
			 */
			Scene* loadScene(const std::string& file);
			/*! \brief Loads a font
			 *  \param file The file path of the .ttf or .otf file relative to res/fonts
			 *  \param pointSize The size of the with whic the font should be loaded
			 *  \return The loaded font
			 */
			TTF_Font* loadFont(const std::string& file, unsigned short pointSize);
            
            /*! \brief Deletes all loaded Textures
             *
             */
            void clearTextures();
            /*! \brief Deletes a single loaded Texture
             *  \param tex The Texture to delete
             */
            void deleteTexture(Texture* tex);
            /*! \brief Deletes all loaded TextureDatas
             *
             */
			void clearTextureDatas();
			/*! \brief Deletes a single loaded TextureData
			 *  \param tex The TextureData to delete
			 */
			void deleteTextureData(TextureData* tex);
			/*! \brief Deletes all loaded shader source file contents
			 *
			 */
			void clearShaders();
			/*! \brief Deletes all loaded Mes3Ds
			 *
			 */
			void clearMeshes();
			/*! \brief Deletes a single loaded Mesh3D
			 *  \param mesh The Mesh3D to delete
			 */
			void deleteMesh(Mesh3D* mesh);
			/*! \brief Deletes all loaded Scenes
			 *
			 */
			void clearScenes();
			/*! \brief Deletes a single loaded Scene
			 *  \param s The Scene to delete
			 */
			void deleteScene(Scene* s);
			/*! \brief Deletes all loaded fonts
			 *  
			 */
			void clearFonts();
			/*! \brief Deletes a single font
			 *  \param font The font to delete
			 */
			void deleteFont(TTF_Font* font);
            
            /*! \brief Checks if a Texture is loaded
             *  \param tex The Texture to check
             *  \return true if the Texture is loaded and false if not
             */
            bool isLoaded(Texture* tex);
            /*! \brief Checks if a Mesh3D is loaded
             *  \param mesh The Mesh3D to check
             *  \return true if the Mesh3D is loaded and false if not
             */
			bool isLoaded(Mesh3D* mesh);
			/*! \brief Checks if a Scene is loaded
			 *  \param s The Scene to check
			 *  \return true if the Scene is loaded and false if not
			 */
			bool isLoaded(Scene* s);
			/*! \brief Checks if a TextureData is loaded
			 *  \param tex The TextureData to check
			 *  \return true if the TextureData is loaded and false if not
			 */
			bool isLoaded(TextureData* tex);
			/*! \brief Checks if a given font is loaded
			 *  \param font The font to check
			 *  \return true if the given font is loaded and false otherwhise
			 */
			bool isLoaded(TTF_Font* font);
            
            /*! \brief Deletes all resources
             *
             */
            void clear();

        private:
        	/*! \brief Processes a aiScene and loads its content
        	 *  \param as The aiScene to load from
        	 *  \param s The Scene to load to
        	 *  \param switchYandZ Defines if the y and z coordinate of the vertex position should be switched
			 */
			void processScene(const aiScene* as, Scene* s,bool switchYandZ);
			/*! \brief Processes a aiNode and loads its content
			 *  \param node The aiNode from which to load
        	 *  \param as The aiScene the aiNode belongs to
        	 *  \param s The Scene to load to
        	 *  \param switchYandZ Defines if the y and z coordinate of the vertex position should be switched
			 */
			void processNode(aiNode* node, const aiScene* as, Scene* s,bool switchYandZ);


			/*! \brief Gets the file name of a full path
			 *  \param directory The file path to get the file name from
			 *  \return The name of the file specified by directory
			 */
			std::string getFileName(const std::string& directory);

            std::map<std::string,Texture*> m_textures;          //!< The map that stores all Textures
			std::map<std::string, TextureData*> m_textureBytes; //!< The map that stores all TextureDatas
			std::map<std::string, std::string> m_shaders;		//!< The map that stores all shader source file contents
			std::map<std::string, Mesh3D*> m_meshes;  			//!< The map that stores all Mesh3Ds
			std::map<std::string, Scene*> m_scenes;				//!< The map that stores all Scenes
			std::map<std::pair<std::string,unsigned short>, TTF_Font*> m_fonts; //!< The map which stores all fonts with the corresponding filepath and point size

    };
}



#endif // RESOURCEMANAGER_H
