#include "../include/Shader.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../include/LogManager.h"
#include <cstdlib>


namespace Johnny
{
	Shader::Shader()
	{
		m_program = glCreateProgram();
		if (m_program == 0)
		{
			LogManager::error("Couldn't create ShaderProgram");
		}
	}


	Shader::~Shader()
	{
		if (m_program != 0)
			glDeleteProgram(m_program);
	}

	void Shader::addFragmentShader(const std::string & text)
	{
		addProgram(text, GL_FRAGMENT_SHADER);
	}

	void Shader::addVertexShader(const std::string & text)
	{
		addProgram(text, GL_VERTEX_SHADER);
	}

	void Shader::addGeometryShader(const std::string & text)
	{
		addProgram(text, GL_GEOMETRY_SHADER);
	}

	void Shader::link()
	{
		if (m_program == 0)
		{
			LogManager::error("Couldn't link Shader, because the program hasn't been initialized");
			return;
		}

		glLinkProgram(m_program);

		GLint isLinked = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_program, maxLength, &maxLength, &infoLog[0]);

			for (size_t i = 0; i < infoLog.size(); i++)
			{
				std::cout << infoLog[i];
			}

			glDeleteProgram(m_program);

			if (m_frag != 0)
				glDeleteShader(m_frag);
			if (m_vert != 0)
				glDeleteShader(m_vert);
			if (m_geo != 0)
				glDeleteShader(m_geo);

			LogManager::error("Shader failed to link");

			return;
		}

		glValidateProgram(m_program);
		GLint status;
		glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_program, maxLength, &maxLength, &infoLog[0]);

			for (size_t i = 0; i < infoLog.size(); i++)
			{
				std::cout << infoLog[i];
			}

			glDeleteProgram(m_program);

			if (m_frag != 0)
				glDeleteShader(m_frag);
			if (m_vert != 0)
				glDeleteShader(m_vert);
			if (m_geo != 0)
				glDeleteShader(m_geo);

			LogManager::error("Shader failed to validate");

			return;
		}

		if (m_frag != 0)
		{
			glDetachShader(m_program, m_frag);
			glDeleteShader(m_frag);
		}

		if (m_vert != 0)
		{
			glDetachShader(m_program, m_vert);
			glDeleteShader(m_vert);
		}

		if (m_geo != 0)
		{
			glDetachShader(m_program, m_geo);
			glDeleteShader(m_geo);
		}

	}

	void Shader::bind()
	{
		if (m_program != 0)
			glUseProgram(m_program);
	}

	void Shader::addUniform(const std::string & uniform, bool endIfNotThere)
	{
		GLuint uniLoc = glGetUniformLocation(m_program, uniform.c_str());

		if (uniLoc == -1)
		{
			if (endIfNotThere)
			{
				LogManager::error("Couldn't find uniform: " + uniform);
				shutdownProgram();
			}

		}
		else
		{
			m_uniforms.insert(std::pair<std::string, GLuint>(uniform, uniLoc));
		}
	}

	void Shader::setUniformi(const std::string & name, GLint i)
	{
		if (m_program != 0)
			glUniform1i(getUniformLocation(name), i);
	}

	void Shader::setUniformf(const std::string & name, GLfloat f)
	{
		if (m_program != 0)
			glUniform1f(getUniformLocation(name), f);
	}

	void Shader::setUniformVec2(const std::string& name, const glm::vec2& vec)
	{
		if (m_program != 0)
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
	}

	void Shader::setUniformVec3(const std::string & name, const glm::vec3 & vec)
	{
		if (m_program != 0)
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void Shader::setUniformVec4(const std::string & name, const glm::vec4 & vec)
	{
		if (m_program != 0)
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::setUniformMat4(const std::string & name, const glm::mat4 & mat)
	{
		if (m_program != 0)
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setUniformMat3(const std::string& name, const glm::mat3& mat)
	{
		if (m_program != 0)
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setUniformMat3(const std::string& name, const Matrix3f& mat)
	{
		if (m_program != 0)
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, mat.values);
	}

	void Shader::addProgram(const std::string & text, GLuint type)
	{
		if (m_program == 0)
		{
			LogManager::error("Couldn't add Shader to program, because the program hasn't been initialized");
			return;
		}

		GLuint shader = 0;

		switch (type)
		{
		case GL_VERTEX_SHADER:
			shader = m_vert = glCreateShader(GL_VERTEX_SHADER);
			if (m_vert == 0)
			{
				LogManager::error("Couldn't create VertexShader");
			}
			break;
		case GL_FRAGMENT_SHADER:
			shader = m_frag = glCreateShader(GL_FRAGMENT_SHADER);
			if (m_frag == 0)
			{
				LogManager::error("Couldn't create FragmentShader");
			}
			break;
		case GL_GEOMETRY_SHADER:
			shader = m_geo = glCreateShader(GL_GEOMETRY_SHADER);
			if (m_geo == 0)
			{
				LogManager::error("Couldn't create GeometryShader");
			}
			break;
		}

		if (shader == 0)
			return;

		const char* contentsPointer = text.c_str();

		glShaderSource(shader, 1, &contentsPointer, nullptr);

		glCompileShader(shader);
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			char* errorLog = new char[maxLength];
			glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);

			glDeleteShader(shader);

			LogManager::error(std::string("Shader failed to compile:\n") + errorLog);

			delete[] errorLog;

			return;
		}

		glAttachShader(m_program, shader);
	}

	GLuint Shader::getUniformLocation(const std::string& name)
	{
		if (m_program != 0)
		{
			std::map<std::string, GLuint>::iterator it = m_uniforms.find(name);
			if (it == m_uniforms.end())
			{
				addUniform(name, false);
				return m_uniforms[name];
			}
			else
			{
				return it->second;
			}
		}
		else
		{
			return 0;
		}
	}

	void Shader::addAttribute(const std::string& name, GLint index)
	{
		if (m_program != 0)
			glBindAttribLocation(m_program, index, name.c_str());
	}

}