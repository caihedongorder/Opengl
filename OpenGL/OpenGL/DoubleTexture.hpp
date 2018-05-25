#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"



class DoubleTexture : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		float verticals[] = {
			-0.5f,-0.5f,0.0f,	0.0f,0.0f,
			0.5f,-0.5f,0.0f,	1.0f,0.0f,
			0.5f,0.5f,0.0f,		1.0f,1.0f,
			-0.5f,0.5f,0.0f,	0.0f,1.0f,
		};

		//创建VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		unsigned int indices[] = { 0,1,2,0,2,3 };
		GLuint IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		program = ShaderUtil::CreateProgram("shaders/demo/DoubleTexture.vert", "shaders/demo/DoubleTexture.frag");
		textureLocation0 = glGetUniformLocation(program, "layer0");
		textureLocation1 = glGetUniformLocation(program, "layer1");

		Image img = Image::LoadFromFile("asserts/images/block.jpg");
		if (!img.IsValid())
			return false;

		//创建纹理
		glGenTextures(1, &texture0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
		
		img = Image::LoadFromFile("asserts/images/monkey.png");
		//img = Image::LoadFromFile("asserts/images/tiger.jpg");
		if (!img.IsValid())
			return false;

		//创建纹理
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
		glGenerateMipmap(GL_TEXTURE_2D);




		return true;
	}
	virtual void OnUnInit() override
	{
		glDeleteProgram(program);
		program = 0;
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	virtual void OnRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glUseProgram(program);
		glUniform1i(textureLocation0, 0);
		glUniform1i(textureLocation0, 1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
	GLuint textureLocation0;
	GLuint textureLocation1;
	GLuint texture0 = 0;
	GLuint texture1 = 0;
};