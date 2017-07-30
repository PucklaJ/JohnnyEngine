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
#include <map>
#include <vector>

namespace Johnny
{
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

	// I000 VVVV MMMM MMMM MMMM MMMM

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

	class UniformBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();

		void addVariable(UBOTypes);
		void addArray(UBOTypes,unsigned int);
		void map();
		void unmap();
		void setVariable(UBOTypes,unsigned int,GLvoid*);
		void createBuffer(GLuint);

		GLsizei getBufferSize() const {return m_bufferSize;}
	private:
		void m_setVariable(UBOTypes,GLsizei,GLvoid*,unsigned int);

		GLuint m_buffer = 0;
		std::vector<UBOTypes> m_types;
		std::map<unsigned int,unsigned int> m_arraySizes;
		GLvoid* m_data = nullptr;
		GLvoid* m_bufferMap = nullptr;
		GLsizei m_bufferSize = 0;
	};

	class Shader
	{
	public:
		Shader();
		~Shader();

		void addFragmentShader(const std::string&);
		void addVertexShader(const std::string&);
		void addGeometryShader(const std::string&);

		void link();
		void bind();

		void attachUniformBuffer(const std::string&,GLuint);
		void addUniform(const std::string&,bool endIfNOtThere = true);
		void setUniformi(const std::string&,GLint);
		void setUniformf(const std::string&,GLfloat);
		void setUniformVec2(const std::string&,const glm::vec2&);
		void setUniformVec2(const std::string&,const Vector2f&);
		void setUniformVec3(const std::string&,const glm::vec3&);
		void setUniformVec3(const std::string&,const Vector3f&);
		void setUniformVec4(const std::string&,const glm::vec4&);
		void setUniformVec4(const std::string&,const Vector4f&);
		void setUniformMat4(const std::string&,const glm::mat4&);
		void setUniformMat4(const std::string&, const Matrix4f&);
		void setUniformMat3(const std::string&, const glm::mat3&);
		void setUniformMat3(const std::string&, const Matrix3f&);

		void addAttribute(const std::string&,GLint);

		void setShadowMap(bool b) { m_shadowMap = b; }
		void setLoadDefaultUniforms(bool b) { m_loadDefaultUniforms = b; }

		GLuint getProgram() { return m_program; }
		bool isShadowMap() const { return m_shadowMap; }
		bool loadDefaultUniforms() { return m_loadDefaultUniforms; }

	private:
		void addProgram(const std::string&,GLuint);
		GLuint getUniformLocation(const std::string&);
		GLuint getUniformBlockIndex(const std::string&);

		std::map<std::string, GLuint> m_uniforms;

		GLuint m_program = 0;
		GLuint m_vert = 0;
		GLuint m_frag = 0;
		GLuint m_geo = 0;

		bool m_shadowMap = false;
		bool m_loadDefaultUniforms = true;

		std::map<std::string,GLuint> m_uniformBlockIndices;
	};
}
