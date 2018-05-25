#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "FileUtil.hpp"

class ShaderUtil
{
public:
	static GLuint CreateVertexShader(const std::string& fileName,GLenum ShaderType) {
		std::string fileContent = FileUtil::getFileContent(fileName);
		if (fileContent.length() == 0)
		{
			return 0;
		}
		auto Shader = glCreateShader(ShaderType);
		const char* source = fileContent.c_str();
		glShaderSource(Shader,1,&source,nullptr);
		glCompileShader(Shader);
		GLint bSuccess;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &bSuccess);
		if (!bSuccess)
		{
			char compileLog[1024] = {0};
			glGetShaderInfoLog(Shader, 1025, nullptr, compileLog);
			std::cout << "×ÅÉ«Æ÷±àÒë´íÎó:" <<fileName <<std::endl
				<< compileLog << std::endl;
			glDeleteShader(Shader);
			Shader = 0;
		}
		return Shader;
	}

	static GLuint CreateProgram(const std::string& vertFile, const std::string& fragFile) {
		GLuint VertShader = CreateVertexShader(vertFile, GL_VERTEX_SHADER);
		if (!VertShader)
		{
			return VertShader;
		}
		GLuint FragShader = CreateVertexShader(fragFile, GL_FRAGMENT_SHADER);
		if (!FragShader)
		{
			return FragShader;
		}

		GLuint program = glCreateProgram();
		glAttachShader(program,VertShader);
		glAttachShader(program,FragShader);
		glLinkProgram(program);
		GLint bSuccess;
		glGetProgramiv(program, GL_LINK_STATUS, &bSuccess);
		if(!bSuccess)
		{
			char LinkInfo[1024];
			glGetProgramInfoLog(program, 1024, nullptr, LinkInfo);
			std::cout << "³ÌÐòÁ¬½Ó´íÎó:" << LinkInfo << std::endl;
			glDetachShader(program, GL_VERTEX_SHADER);
			glDetachShader(program, GL_FRAGMENT_SHADER);
			glDeleteShader(VertShader);
			glDeleteShader(FragShader);
			glDeleteProgram(program);
			return 0;
		}

		glDeleteShader(VertShader);
		glDeleteShader(FragShader);

		return program;
	}
};

