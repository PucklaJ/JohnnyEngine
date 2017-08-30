#pragma once
#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Geometry.h"
#include "ShaderUpdater.h"
#include <map>
#include <vector>

namespace Johnny
{
	/*! \brief A enum which represents the types of the values of a UniformBuffer
	 *
	 */
	enum UBOTypes
	{
		FLOAT,
		INT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		ARRAY_FLOAT,
		ARRAY_INT,
		ARRAY_VEC2,
		ARRAY_VEC3,
		ARRAY_VEC4,
		ARRAY_MAT2,
		ARRAY_MAT3,
		ARRAY_MAT4
	};

	/*! \brief Gets the size of a UBOTypes in the uniform buffer object in bytes
	 *  \param type The type to get the size from
	 *  \param arraySize The size of the array variable
	 *  \return The size of the type in bytes
	 */
	inline GLsizei getSize(UBOTypes type,unsigned int arraySize)
	{
		switch(type)
		{
		case FLOAT: return sizeof(GLfloat);
		case INT:   return sizeof(GLint);
		case VEC2:  return 2*sizeof(GLfloat);
		case VEC3:  return 4*sizeof(GLfloat);
		case VEC4:  return 4*sizeof(GLfloat);
		case MAT2:  return 2*16;
		case MAT3:  return 3*16;
		case MAT4:  return 4*16;
		case ARRAY_MAT2:  return arraySize*2*16;
		case ARRAY_MAT3:  return arraySize*3*16;
		case ARRAY_MAT4:  return arraySize*4*16;
		default: return arraySize*16;
		}
	}

	/*! \brief A class which represents a uniform buffer object
	 *
	 */
	class UniformBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();

		/*! \brief Adds a definition of a variable to determine the size of the buffer
		 *  \param type The type of the variable
		 */
		void addVariable(UBOTypes type);
		/*! \brief Adds a definition of an array to determine the size of the buffer
		 *  \param type The type of the array (must begin with ARRAY_)
		 *  \param size The number of elements in the array
		 */
		void addArray(UBOTypes type,unsigned int size);
		/*! \brief Maps the UniformBuffer
		 *
		 */
		void map();
		/*! \brief Unmaps the UniformBuffer
		 *
		 */
		void unmap();
		/*! \brief Sets a variable of the UniformBuffer after it has been mapped
		 *  \param type The type of the variable
		 *  \param index The howmany variable of that type
		 *  \param data The contents of the variable
		 */
		void setVariable(UBOTypes type,unsigned int index,GLvoid* data);
		/*! \brief Creates the buffer (Should be called after the addVariable calls and before map and setVariable)
		 *  \param bindingPoint The buffer uniform buffer binding point to bind the buffer to
		 */
		void createBuffer(GLuint bindingPoint);

		/*! \return The size of the buffer in bytes
		 *
		 */
		GLsizei getBufferSize() const {return m_bufferSize;}
	private:
		/*! \brief Actually sets the variable
		 *  \param type The type of the variable
		 *  \param offset The offset in the buffer in bytes
		 *  \param data The content of the variable
		 *  \param arraySize The number of elements in the array if type is a type of array
		 */
		void m_setVariable(UBOTypes type,GLsizei offset,GLvoid* data,unsigned int arraySize);

		GLuint m_buffer = 0;							  //!< The name of the uniform buffer
		std::vector<UBOTypes> m_types;					  //!< The array which stores all types of all variables
		std::map<unsigned int,unsigned int> m_arraySizes; //!< The map which stores all array sizes of all array variables
		GLbyte* m_data = nullptr;						  //!< The pointer which is used for writeing to the buffer
		GLvoid* m_bufferMap = nullptr;					  //!< The pointer which is used for mapping
		GLsizei m_bufferSize = 0;						  //!< The size of the buffer in bytes
	};

	/*! \brief A class which represents a shader program
	 *
	 */
	class Shader
	{
	public:
		Shader();
		~Shader();

		/*! \brief Adds a fragment shader to the Shader
		 *  \param contents The source code of the fragment shader
		 */
		void addFragmentShader(const std::string& contents);
		/*! \brief Adds a vertex shader to the Shader
		 *  \param contents The source code of the vertex shader
		 */
		void addVertexShader(const std::string& contents);
		/*! \brief Adds a geometry shader to the Shader
		 *  \param contents The source code of the geometry shader
		 */
		void addGeometryShader(const std::string& contents);

		/*! \brief Links the Shader (should be called after the add**Shader calls)
		 *
		 */
		void link();
		/*! \brief Binds the shader program
		 *
		 */
		void bind();

		/*! \brief Attaches a uniform block to a specific binding point
		 *  \param name The name of the uniform block
		 *  \param bindingPoint The binding point to attach to
		 */
		void attachUniformBuffer(const std::string& name,GLuint bindingPoint);
		
		/*! \brief Stores the uniform location of the uniform with the given name
		 *  \param name The name of the ubiform to store the location
		 *  \param endifNotThere Defines if a error message should be printed of the uniform wasn't found
		 *  \return true if the uniform was found and false otherwhise
		 */
		bool addUniform(const std::string& name,bool endIfNOtThere = true);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, GLint value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, GLfloat value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const glm::vec2& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Vector2f& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Vector2i& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const glm::vec3& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Vector3f& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const glm::vec4& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Vector4f& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const TextureRegion& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const glm::mat4& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Matrix4f& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const glm::mat3& value);
		/*! \brief Sets the value of a uniform in the shader
		 *  \param name The name of the uniform
		 *  \param value The value of the uniform
		 */
		void setUniform(const std::string& name, const Matrix3f& value);

		/*! \brief Defines a vertex attribute
		 *  \param name The name of the vertex attribute
		 *  \param index The index of the vertex attribute
		 */
		void addAttribute(const std::string& name,GLint index);

		/*! \brief Defines if this Shader is a Shader used for rendering to a ShadowMap3D DEPRECATED
		 *  \param b The bool value
		 */
		void setShadowMap(bool b) { m_shadowMap = b; }

		/*! \return The name of the shader program
		 *
		 */
		GLuint getProgram() { return m_program; }
		/*! \return If the SHader is used for rendering to a ShadowMap3D DEPRECATED
		 *
		 */
		bool isShadowMap() const { return m_shadowMap; }
        
        /*! \brief Sets the ShaderUpdater of the Shader
         *  \param T the type of ShaderUpater
         */
        template<class T>
        void setShaderUpdater();
        /*! \return The ShaderUpdater of the Shader
         *
         */
        ShaderUpdater* getShaderUpdater() {return m_shaderUpdater;}

	private:
		/*! \brief Actually adds a shader source to the shader program
		 *  \param text The source code of a shader
		 *  \param type The type of shader
		 */
		void addProgram(const std::string& text,GLuint type);
		/*! \param name The name of the uniform
		 *  \return The location of the uniform or INT_MAX if the uniform wasn't found
		 */
		GLuint getUniformLocation(const std::string& name);
		/*! \return The index of a uniform block by name
		 *  \param name The name of The uniform block
		 */
		GLuint getUniformBlockIndex(const std::string& name);

		std::map<std::string, GLuint> m_uniforms; 		    //!< The map where all uniform locations are stored

		GLuint m_program = 0;					  	        //!< The name of the shader program
		GLuint m_vert = 0;						  	        //!< The name of the vertex shader
		GLuint m_frag = 0;						  	        //!< The name of the fragment shader
		GLuint m_geo = 0;						  	        //!< The name of the geometry shader

		bool m_shadowMap = false;				  	        //!< Defines if the Shader is used for rendering to ShadowMap3D DEPRECATED

		std::map<std::string,GLuint> m_uniformBlockIndices; //!< The map where every uniform block indices are stored
        
        ShaderUpdater* m_shaderUpdater = nullptr;			//!< The ShaderUpdater of the Shader
	};
    
    template<class T>
    inline void Shader::setShaderUpdater()
    {
        m_shaderUpdater = new T(this);
    }
}
