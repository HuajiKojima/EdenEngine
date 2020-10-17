#include "EdenShader.h"
#define COMPILE_VERTEX_SHADER 0
#define COMPILE_FRAGMENT_SHADER 1
#define COMPILE_GEOMETRY_SHADER 2
#define LINK_PROGRAM 3

EDEN::EdenShader::EdenShader(const char * vertCodePath, const char * fragCodePath, const char * geoCodePath = nullptr)
{
	std::string vertShaderCode;
	std::string fragShaderCode;
	std::string geoShaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	// Set the format of file stream exception
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertCodePath);
		fShaderFile.open(fragCodePath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragCode = fShaderStream.str();

		if (geoCodePath != nullptr) 
		{
			gShaderFile.open(geoCodePath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geoCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure & e)
	{
		std::cout << "EDEN::ERROR::SHADER::FILEREAD::" << e.what() << std::endl;
	}
	const char * vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragCode.c_str();
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, COMPILE_VERTEX_SHADER);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, COMPILE_FRAGMENT_SHADER);

	unsigned int geometryShader;
	if (geoCodePath != nullptr)
	{
		const char * gShaderCode = geoCode.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gShaderCode, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, COMPILE_GEOMETRY_SHADER);
	}
	this->shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	if (geoCodePath != nullptr) 
	{
		glAttachShader(shaderID, geometryShader);
	}
	glLinkProgram(shaderID);
	checkCompileErrors(shaderID, LINK_PROGRAM);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geoCodePath != nullptr)
	{
		glDeleteShader(geometryShader);
	}
}

void EDEN::EdenShader::ShaderRun()
{
	glUseProgram(shaderID);
}

unsigned int EDEN::EdenShader::getShaderID()
{
	return this->shaderID;
}

void EDEN::EdenShader::setUniformBool(const char * shaderVariable, bool uniVal)
{
	glUniform1i(glGetUniformLocation(shaderID, shaderVariable), int(uniVal));
}

void EDEN::EdenShader::setUniformFloat(const char * shaderVariable, float uniVal)
{
	glUniform1f(glGetUniformLocation(shaderID, shaderVariable), uniVal);
}

void EDEN::EdenShader::setUniformIntenger(const char * shaderVariable, int uniVal)
{
	glUniform1i(glGetUniformLocation(shaderID, shaderVariable), uniVal);
}

void EDEN::EdenShader::setUniformVec2(const char * shaderVariable, glm::vec2 & uniVal)
{
	glUniform2f(glGetUniformLocation(shaderID, shaderVariable), uniVal.x, uniVal.y);
}

void EDEN::EdenShader::setUniformVec3(const char * shaderVariable, glm::vec3 & uniVal)
{
	glUniform3f(glGetUniformLocation(shaderID, shaderVariable), uniVal.x, uniVal.y, uniVal.z);
}

void EDEN::EdenShader::setUniformVec4(const char * shaderVariable, glm::vec4 & uniVal)
{
	glUniform4f(glGetUniformLocation(shaderID, shaderVariable), uniVal.x, uniVal.y, uniVal.z, uniVal.w);
}

void EDEN::EdenShader::setUniformVec2(const char * shaderVariable, float x, float y)
{
	glUniform2f(glGetUniformLocation(shaderID, shaderVariable), x, y);
}

void EDEN::EdenShader::setUniformVec3(const char * shaderVariable, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderID, shaderVariable), x, y, z);
}

void EDEN::EdenShader::setUniformVec4(const char * shaderVariable, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderID, shaderVariable), x, y, z, w);
}

void EDEN::EdenShader::setUniformMat2(const char * shaderVariable, glm::mat2 & uniVal)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderID, shaderVariable), 1, GL_FALSE, &uniVal[0][0]);
}

void EDEN::EdenShader::setUniformMat3(const char * shaderVariable, glm::mat3 & uniVal)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, shaderVariable), 1, GL_FALSE, &uniVal[0][0]);
}

void EDEN::EdenShader::setUniformMat4(const char * shaderVariable, glm::mat4 & uniVal)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, shaderVariable), 1, GL_FALSE, &uniVal[0][0]);
}

void checkCompileErrors(GLuint shader, int type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != LINK_PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "EDEN::SHADER::ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "EDEN::SHADER::ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
