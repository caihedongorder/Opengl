#pragma once
#include "RenderDemoBase.hpp"
#include "ShaderUtil.hpp"

class $safeitemname$ : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		float verticals[] = {
			-0.5f,-0.5f,0.0f,
			0.5f,-0.5f,0.0f,
			0.0f,0.5f,0.0f
		};

		//´´½¨VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//glBindVertexArray(0);

		program = ShaderUtil::CreateProgram("shaders/test/test1.vert", "shaders/test/test1.frag");

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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
};