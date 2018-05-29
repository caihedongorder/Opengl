#pragma once
#include "ModelBase.hpp"
#include <vector>

class LightModel : public ModelBase
{
public:
	virtual bool OnCreateGeometry() override
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float l = -0.5f;
		float t = 0.5f;
		float w = 1.0f;
		float h = 1.0f;

		glm::vec3 pts[] = {
			//front
			glm::vec3(l,t,w*0.5f),
			glm::vec3(l + w,t - h ,w*0.5f),
			glm::vec3(l + w,t,w*0.5f),

			glm::vec3(l,t,w*0.5f),
			glm::vec3(l,t - h,w*0.5f),
			glm::vec3(l + w ,t - h ,w*0.5f),

			//back
			glm::vec3(l,t,-w * 0.5f),
			glm::vec3(l + w,t,-w * 0.5f),
			glm::vec3(l + w,t - h ,-w * 0.5f),

			glm::vec3(l,t,-w * 0.5f),
			glm::vec3(l + w ,t - h ,-w * 0.5f),
			glm::vec3(l,t - h,-w * 0.5f),

			//right
			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),
			glm::vec3(l + w,t,-w * 0.5f),

			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t - h,w*0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),

			//left
			glm::vec3(l ,t,w*0.5f),
			glm::vec3(l ,t,-w * 0.5f),
			glm::vec3(l ,t - h,-w * 0.5f),

			glm::vec3(l ,t,w*0.5f),
			glm::vec3(l ,t - h,-w * 0.5f),
			glm::vec3(l ,t - h,w*0.5f),

			//top
			glm::vec3(l,t,w*0.5f),
			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l,t,-w * 0.5f),

			glm::vec3(l + w,t,w*0.5f),
			glm::vec3(l + w,t,-w * 0.5f),
			glm::vec3(l,t,-w * 0.5f),

			//bottom
			glm::vec3(l,t - h,w*0.5f),
			glm::vec3(l,t - h,-w * 0.5f),
			glm::vec3(l + w,t - h,w*0.5f),

			glm::vec3(l + w,t - h,w*0.5f),
			glm::vec3(l,t - h,-w * 0.5f),
			glm::vec3(l + w,t - h,-w * 0.5f),
		};		
		//´´½¨VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*36.0f, &pts[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	virtual bool OnGPUProgram() override
	{
		program = ShaderUtil::CreateProgram("shaders/demo/LightModel.vert", "shaders/demo/LightModel.frag");
		mvpLocation = glGetUniformLocation(program, "mvp");
		return true;
	}
	virtual void OnRender() override
	{
		glUseProgram(program);
		glm::mat4 mvp = Camera::GetCamera()->getViewProjectionMatrix()* transform.GetTransformMatrixWithScale();
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUseProgram(0);
	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
	GLuint mvpLocation;
	GLuint texture;
	GLuint textureLocation;
};