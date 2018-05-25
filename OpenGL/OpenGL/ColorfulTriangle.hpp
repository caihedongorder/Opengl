#pragma once
#include "RenderDemoBase.hpp"
#include "ShaderUtil.hpp"

class ColorfulTriangle : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		float verticals[] = {
			-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,1.0f,
			0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,1.0f,
			0.0f,0.5f,0.0f,		0.0f,0.0f,1.0f,1.0f
		};

		//创建VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
		int stride = 7 * sizeof(float);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		unsigned int indices[] = { 0,1,2 };

		//创建IBO
		GLuint IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//glBindVertexArray(0);

		program = ShaderUtil::CreateProgram("shaders/demo/colorful.vert", "shaders/demo/colorful.frag");

		return true;
	}
	virtual void OnUnInit() override
	{
		glDeleteProgram(program);
		program = 0;
		glDeleteVertexArrays(1,&VAO);
		VAO = 0;
	}
	virtual void OnRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
};