#pragma once
#include <GL/glew.h>
#include <string>
#include <map>
#include <glm\glm.hpp>
#include "Matrix3.h"

namespace Johnny
{
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

		void addUniform(const std::string&,bool endIfNOtThere = true);
		void setUniformi(const std::string&,GLint);
		void setUniformf(const std::string&,GLfloat);
		void setUniformVec2(const std::string&,const glm::vec2&);
		void setUniformVec3(const std::string&,const glm::vec3&);
		void setUniformVec4(const std::string&, const glm::vec4&);
		void setUniformMat4(const std::string&,const glm::mat4&);
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

		std::map<std::string, GLuint> m_uniforms;

		GLuint m_program = 0;
		GLuint m_vert = 0;
		GLuint m_frag = 0;
		GLuint m_geo = 0;

		bool m_shadowMap = false;
		bool m_loadDefaultUniforms = true;
	};
}
