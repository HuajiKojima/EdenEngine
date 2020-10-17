#pragma once
#ifndef EDEN_SHADER
#define EDEN_SHADER

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace EDEN
{
	class EdenShader
	{
	private:
		unsigned int shaderID;
		std::string vertexCode;
		std::string fragCode;
		std::string geoCode;
		void checkCompileErrors(GLuint shader, int type);

	public:
		EdenShader(const char * vertCodePath, const char * fragCodePath, const char * geoCodePath = nullptr);
		void ShaderRun();
		unsigned int getShaderID();
		void setUniformBool(const char * shaderVariable, bool uniVal);
		void setUniformFloat(const char * shaderVariable, float uniVal);
		void setUniformIntenger(const char * shaderVariable, int uniVal);

		// Set uniform vector
		//--------------------------------------------------------------------------
		void setUniformVec2(const char * shaderVariable, glm::vec2 & uniVal);
		void setUniformVec3(const char * shaderVariable, glm::vec3 & uniVal);
		void setUniformVec4(const char * shaderVariable, glm::vec4 & uniVal);
		void setUniformVec2(const char * shaderVariable, float x, float y);
		void setUniformVec3(const char * shaderVariable, float x, float y, float z);
		void setUniformVec4(const char * shaderVariable, float x, float y, float z, float w);
		//--------------------------------------------------------------------------

		// Set uniform matrix
		//--------------------------------------------------------------------------
		void setUniformMat2(const char * shaderVariable, glm::mat2 & uniVal);
		void setUniformMat3(const char * shaderVariable, glm::mat3 & uniVal);
		void setUniformMat4(const char * shaderVariable, glm::mat4 & uniVal);
		//--------------------------------------------------------------------------
	};
}
#endif // !EDEN_SHADER



