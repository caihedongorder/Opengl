#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"


class $safeitemname$ : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float verticals[] = {
			-0.5f,-0.5f,	-0.5f,
			0.5f,-0.5f,		-0.5f,
			0.5f,0.5f,		-0.5f,
			-0.5f,0.5f,		-0.5f,

			-0.5f,-0.5f,	 0.5f,
			0.5f,-0.5f,		 0.5f,
			0.5f,0.5f,		 0.5f,
			-0.5f,0.5f,		 0.5f,
		};

		//创建VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0));
		glEnableVertexAttribArray(0);

		int indices[] = {
			//前后
			0,2,1,0,3,2,
			4,5,6,4,6,7,
			//左右
			4,3,0,4,7,3,
			5,1,2,5,2,6,
			//上下
			7,6,2,7,2,3,
			4,1,5,4,0,1,
		};
		//创建IBO
		GLuint IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		//glBindVertexArray(0);

		program = ShaderUtil::CreateProgram("shaders/demo/CubeDemo.vert", "shaders/demo/CubeDemo.frag");
		mvpLocation = glGetUniformLocation(program, "mvp");
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glm::mat4 mvp(1.0f);
		mvp = glm::translate(mvp, glm::vec3(0, 0, -5));
		mvp = glm::rotate(mvp, (float)glfwGetTime(), glm::vec3(1, 1, 1));
		auto projectMat = glm::perspective<float>(glm::radians(90.0f),800.0f/600,1.0f,1000.0f);
		mvp = projectMat * mvp;
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
	GLuint mvpLocation;
};