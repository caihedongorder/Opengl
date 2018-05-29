#pragma once

#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"
#include "Camera.hpp"
#include "Transform.hpp"


class ModelBase
{
public:
	virtual bool OnCreateGeometry() { return false; }
	virtual bool OnGPUProgram() { 
		glUseProgram(program);
		mvpLocation = glGetUniformLocation(program, "mvp");
		mLocation = glGetUniformLocation(program, "m");
		lightColorLocation = glGetUniformLocation(program, "lightColor");
		lightPositionLocation = glGetUniformLocation(program, "lightPosition");
		return true;
	}
	virtual void OnRender(){}
	Transform& GetTransform() { return transform; }
	GLuint GetGpuProgram() const { return program; }

	void UseProgram() { 
		glUseProgram(program); 
		glm::mat4 mvp = Camera::GetCamera()->getViewProjectionMatrix()* transform.GetTransformMatrixWithScale();
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrixWithScale()));
		glUniform4fv(lightColorLocation, 1, glm::value_ptr(lightColor));
	}
	void UnUseProgram() { glUseProgram(0); }

	void SetLightPosition(const glm::vec3& lightPosition) {
		glUseProgram(program);
		glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));
	}
protected:
	Transform transform;
	GLuint program;

	GLuint VAO = 0;
	GLuint mvpLocation;
	GLuint mLocation;
	GLuint lightColorLocation;
	GLuint lightPositionLocation;
	glm::vec4 lightColor = glm::vec4(1, 1, 1, 1);

};