#include "../include/Shader.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../include/LogManager.h"
#include <cstdlib>
#include "../include/operators.h"


namespace Johnny
{
	UniformBuffer::UniformBuffer()
	{

	}

	UniformBuffer::~UniformBuffer()
	{
		if(m_buffer != 0)
			glDeleteBuffers(1,&m_buffer);

		if(m_data)
			delete[] ((GLbyte*)m_data);
	}

	void UniformBuffer::createBuffer(GLuint bindingPoint)
	{
		glCreateBuffers(1,&m_buffer);
		if(m_buffer == 0)
		{
			LogManager::error("UniformBuffer couldn't be created");
			return;
		}

		GLsizei size = 0;
		GLsizei curSize = 0;
		GLsizei curChunkSpace = 16;
		unsigned int arraySize = 0;

		for(unsigned int i = 0;i<m_types.size();i++)
		{
			if(m_arraySizes.find(i) != m_arraySizes.end())
				arraySize = m_arraySizes[i];

			curSize = getSize(m_types[i],arraySize);
			if(curSize > curChunkSpace)
			{
				if(curChunkSpace == 16)
					size += curSize;
				else
					size += curChunkSpace + curSize;

				curChunkSpace = 16;
			}
			else
			{
				curChunkSpace -= curSize;
				size += curSize;
			}

			if(curChunkSpace == 0)
				curChunkSpace = 16;
		}

		if(curChunkSpace < 16)
			size += curChunkSpace;

		m_bufferSize = size;

		GLvoid* newData = new GLbyte[size];

		memset(newData,0,size);

		glGetError();
		glNamedBufferStorage(m_buffer,size,newData,GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_DYNAMIC_STORAGE_BIT);

		std::string errorStr = "Failed to allocate the buffer: ";
		GLenum error = glGetError();

		switch(error)
		{
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			LogManager::error(errorStr + "Invalid Enum");
			break;
		case GL_INVALID_VALUE:
			LogManager::error(errorStr + "Size is negative");
			break;
		case GL_INVALID_OPERATION:
			LogManager::error(errorStr + "Buffer isn't valid");
			break;
		case GL_OUT_OF_MEMORY:
			LogManager::error(errorStr + "Out of Memory");
			break;
		default:
			LogManager::error(errorStr + std::to_string(error));
			break;
		}

		glBindBufferBase(GL_UNIFORM_BUFFER,bindingPoint,m_buffer);

		error = glGetError();
		errorStr = std::string("Failed to bind UniformBuffer to BindingPoint ") + std::to_string(bindingPoint) + ": ";

		GLint maxBindings = 0;

		switch(error)
		{
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			LogManager::error(errorStr + "Invalid Enum");
			break;
		case GL_INVALID_VALUE:
			glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,&maxBindings);
			LogManager::error(errorStr + "BindingPoint is too big (MAX: " + std::to_string(maxBindings-1) + ")");
			break;
		default:
			LogManager::error(errorStr + std::to_string(error));
			break;
		}

		delete[] (GLbyte*)newData;

	}

	void UniformBuffer::addVariable(UBOTypes type)
	{
		m_types.push_back(type);
	}

	void UniformBuffer::addArray(UBOTypes type,unsigned int arraySize)
	{
		m_types.push_back(type);
		m_arraySizes[m_types.size()-1] = arraySize;
	}

	void UniformBuffer::map()
	{
		if(m_buffer == 0)
			return;
		glGetError();
		m_bufferMap = glMapNamedBuffer(m_buffer,GL_READ_WRITE);
		if(m_bufferMap == nullptr)
		{
			GLenum error = glGetError();
			std::string errorStr = "Failed to map UniformBuffer: ";

			switch(error)
			{
			case GL_INVALID_OPERATION:
				LogManager::error(errorStr + "Buffer is already mapped");
				break;
			case GL_OUT_OF_MEMORY:
				LogManager::error(errorStr + "Out of Memory");
				break;
			case GL_INVALID_ENUM:
				LogManager::error(errorStr + "Invalid Enum");
				break;
			case GL_NO_ERROR:
				LogManager::error(errorStr + "Couldn't identify error");
				break;
			default:
				LogManager::error(errorStr + std::to_string(error));
				break;
			}
			return;
		}
		m_data = new GLbyte[m_bufferSize];
		memcpy(m_data,m_bufferMap,m_bufferSize);
	}

	void UniformBuffer::unmap()
	{
		if(m_buffer == 0)
			return;

		memcpy(m_bufferMap,m_data,m_bufferSize);

		glUnmapNamedBuffer(m_buffer);
		delete[] ((GLbyte*)m_data);
		m_data = nullptr;
	}

	void UniformBuffer::setVariable(UBOTypes type,unsigned int index,GLvoid* data)
	{
		if(m_buffer == 0)
			return;

		GLsizei offset = 0;
		GLsizei curSize = 0;
		GLsizei curChunkSpace = 16;
		GLuint numTypes = 0;
		unsigned int arraySize = 0;
		unsigned int ArraySize = 0;

		for(unsigned int i = 0;i<m_types.size();i++)
		{
			if(m_types[i] == type)
			{
				if(index == numTypes)
				{
					if(m_arraySizes.find(i) != m_arraySizes.end())
						ArraySize = m_arraySizes[i];
					break;
				}
				else
				{
					numTypes++;
				}

			}

			if(m_arraySizes.find(i) != m_arraySizes.end())
				arraySize = m_arraySizes[i];

			curSize = getSize(m_types[i],arraySize);
			if(curSize > curChunkSpace)
			{
				if(curChunkSpace == 16)
					offset += curSize;
				else
					offset += curChunkSpace + curSize;

				curChunkSpace = 16;
			}
			else
			{
				curChunkSpace -= curSize;
				offset += curSize;
			}

			if(curChunkSpace == 0)
				curChunkSpace = 16;
		}

		if(curChunkSpace < 16 && getSize(type,ArraySize) > curChunkSpace)
			offset += curChunkSpace;

		m_setVariable(type,offset,data,ArraySize);
	}

	void UniformBuffer::m_setVariable(UBOTypes type,GLsizei offset,GLvoid* data,unsigned int arraySize)
	{
		GLsizei addOffset = offset;

		switch(type)
		{
		case FLOAT:
			*((GLfloat*)(m_data+offset)) = *((GLfloat*)data);
			break;
		case INT:
			*((GLint*)(m_data+offset)) = *((GLint*)data);
			break;
		case VEC2:
			((GLfloat*)(m_data+offset))[0] = ((GLfloat*)data)[0];
			((GLfloat*)(m_data+offset))[1] = ((GLfloat*)data)[1];
			break;
		case VEC3:
			((GLfloat*)(m_data+offset))[0] = ((GLfloat*)data)[0];
			((GLfloat*)(m_data+offset))[1] = ((GLfloat*)data)[1];
			((GLfloat*)(m_data+offset))[2] = ((GLfloat*)data)[2];
			break;
		case VEC4:
			((GLfloat*)(m_data+offset))[0] = ((GLfloat*)data)[0];
			((GLfloat*)(m_data+offset))[1] = ((GLfloat*)data)[1];
			((GLfloat*)(m_data+offset))[2] = ((GLfloat*)data)[2];
			((GLfloat*)(m_data+offset))[3] = ((GLfloat*)data)[3];
			break;
		case MAT2:
			((GLfloat*)(m_data+offset))[0] = ((GLfloat*)data)[0];
			((GLfloat*)(m_data+offset))[1] = ((GLfloat*)data)[1];
			((GLfloat*)(m_data+offset+16))[0] = ((GLfloat*)data)[2];
			((GLfloat*)(m_data+offset+16))[1] = ((GLfloat*)data)[3];
			break;
		case MAT3:
			for(unsigned int i = 0;i<3;i++)
			{
				for(unsigned int j =0;j<3;j++)
				{
					*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*3+j];
					addOffset += sizeof(GLfloat);
				}
				addOffset += sizeof(GLfloat);
			}
			break;
		case MAT4:
			for(unsigned int i = 0;i<4;i++)
			{
				for(unsigned int j = 0;j<4;j++)
				{
					*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*4+j];
					addOffset += sizeof(GLfloat);
				}
			}
			break;
		case ARRAY_FLOAT:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i];
				addOffset += 16;
			}
			break;
		case ARRAY_INT:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				*((GLint*)(m_data+addOffset)) = ((GLint*)data)[i];
				addOffset += 16;
			}
			break;
		case ARRAY_VEC2:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				for(unsigned int j = 0;j<2;j++)
				{
					*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*2+j];
					addOffset += sizeof(GLfloat);
				}

				addOffset += 2*sizeof(GLfloat);
			}
			break;
		case ARRAY_VEC3:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				for(unsigned int j = 0;j<3;j++)
				{
					*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*3+j];
					addOffset += sizeof(GLfloat);
				}

				addOffset += sizeof(GLfloat);
			}
			break;
		case ARRAY_VEC4:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				for(unsigned int j = 0;j<4;j++)
				{
					*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*4+j];
					addOffset += sizeof(GLfloat);
				}
			}
			break;
		case ARRAY_MAT2:
			for(unsigned int i = 0;i<arraySize;i++)
			{
				((GLfloat*)(m_data+offset+i*2*16))[0] = ((GLfloat*)data)[0+i*4];
				((GLfloat*)(m_data+offset+i*2*16))[1] = ((GLfloat*)data)[1+i*4];
				((GLfloat*)(m_data+offset+16+i*2*16))[0] = ((GLfloat*)data)[2+i*4];
				((GLfloat*)(m_data+offset+16+i*2*16))[1] = ((GLfloat*)data)[3+i*4];
			}
			break;
		case ARRAY_MAT3:
			for(unsigned int a = 0;a<arraySize;a++)
			{
				for(unsigned int i = 0;i<3;i++)
				{
					for(unsigned int j =0;j<3;j++)
					{
						*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*3+j+a*3*3];
						addOffset += sizeof(GLfloat);
					}
					addOffset += sizeof(GLfloat);
				}
			}
			break;
		case ARRAY_MAT4:
			for(unsigned int a = 0;a<arraySize;a++)
			{
				for(unsigned int i = 0;i<4;i++)
				{
					for(unsigned int j = 0;j<4;j++)
					{
						*((GLfloat*)(m_data+addOffset)) = ((GLfloat*)data)[i*4+j+a*4*4];
						addOffset += sizeof(GLfloat);
					}
				}
			}
			break;
		default:
			break;
		}

	}

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

	void Shader::attachUniformBuffer(const std::string& blockName,GLuint bindingPoint)
	{
		if(m_program == 0)
			return;

		GLuint index = getUniformBlockIndex(blockName);
		if(index == GL_INVALID_INDEX)
			LogManager::error(std::string("Couldn't find UniformBlock: " + blockName));

		glGetError();
		glUniformBlockBinding(m_program,index,bindingPoint);

		GLenum error = glGetError();
		std::string errorStr = "Couldn't bind UniformBlock to BindingPoint " + std::to_string(bindingPoint) + ": ";
		GLint maxBinding = 0;

		switch(error)
		{
		case GL_NO_ERROR:
			break;
		case GL_INVALID_VALUE:
			glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,&maxBinding);
			LogManager::error(errorStr + (index == 0 ? "UniformBlock is invalid" : ("BindingPoint is too big (MAX: " + std::to_string(maxBinding-1) + ")")));
			break;
		default:
			LogManager::error(errorStr + std::to_string(error));
			break;
		}
	}

	bool Shader::addUniform(const std::string & uniform, bool endIfNotThere)
	{
		GLuint uniLoc = glGetUniformLocation(m_program, uniform.c_str());

        m_uniforms.insert(std::pair<std::string, GLuint>(uniform, uniLoc));

		if (uniLoc == (GLuint)-1)
		{
			if (endIfNotThere)
			{
				LogManager::error("Couldn't find uniform: " + uniform);
			}
			return false;
		}
		else
		{
            
            return true;
		}
	}

	void Shader::setUniform(const std::string & name, GLint i)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform1i(loc, i);
        }
	}

	void Shader::setUniform(const std::string & name, GLfloat f)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform1f(loc, f);
        }
	}

	void Shader::setUniform(const std::string& name, const glm::vec2& vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform2f(loc, vec.x,vec.y);
        }
	}

	void Shader::setUniform(const std::string& name, const Vector2f& vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform2f(loc, vec.x,vec.y);
        }
	}

	void Shader::setUniform(const std::string& name, const Vector2i& vec)
	{
		if (m_program != 0)
		{
			GLuint loc = getUniformLocation(name);

			if (loc != 4294967295)
				glUniform2i(loc, vec.x, vec.y);
		}
	}

	void Shader::setUniform(const std::string & name, const glm::vec3 & vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform3f(loc, vec.x,vec.y,vec.z);
        }
	}

	void Shader::setUniform(const std::string & name, const Vector3f& vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform3f(loc, vec.x,vec.y,vec.z);
        }
	}

	void Shader::setUniform(const std::string & name, const glm::vec4 & vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform4f(loc, vec.x,vec.y,vec.z,vec.w);
        }
	}

	void Shader::setUniform(const std::string & name, const Vector4f& vec)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniform4f(loc, vec.x,vec.y,vec.z,vec.w);
        }
	}

	void Shader::setUniform(const std::string& name, const TextureRegion& vec)
	{
		if (m_program != 0)
		{
			GLuint loc = getUniformLocation(name);

			if (loc != 4294967295)
				glUniform4f(loc, (GLfloat)vec.x, (GLfloat)vec.y, (GLfloat)vec.width, (GLfloat)vec.height);
				
		}
	}

	void Shader::setUniform(const std::string & name, const glm::mat4 & mat)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniformMatrix4fv(loc,1,GL_FALSE, &mat[0][0]);
        }
	}

	void Shader::setUniform(const std::string& name, const Matrix4f& mat)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniformMatrix4fv(loc,1,GL_FALSE, &mat.values[0]);
        }
	}

	void Shader::setUniform(const std::string& name, const glm::mat3& mat)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniformMatrix3fv(loc,1,GL_FALSE, &mat[0][0]);
        }
	}

	void Shader::setUniform(const std::string& name, const Matrix3f& mat)
	{
		if (m_program != 0)
        {
            GLuint loc = getUniformLocation(name);
            
            if(loc != 4294967295)
                glUniformMatrix3fv(loc,1,GL_FALSE, &mat.values[0]);
        }
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
				if(addUniform(name, false))
                    return m_uniforms[name];
                else
                {
                    return 4294967295;
                }
                    
			}
			else
			{
				return it->second;
			}
		}
		else
		{
			return 4294967295;
		}
	}

	GLuint Shader::getUniformBlockIndex(const std::string& blockName)
	{
		if(m_program == 0)
			return 0;

		if(m_uniformBlockIndices.find(blockName) != m_uniformBlockIndices.end())
			return m_uniformBlockIndices[blockName];
		else
		{
			GLuint index = glGetUniformBlockIndex(m_program,blockName.c_str());
			if(index != GL_INVALID_INDEX)
				m_uniformBlockIndices[blockName] = index;

			return index;
		}
	}

	void Shader::addAttribute(const std::string& name, GLint index)
	{
		if (m_program != 0)
			glBindAttribLocation(m_program, index, name.c_str());
	}

}
