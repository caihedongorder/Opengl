#pragma once

#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"
#include "Camera.hpp"
#include "Transform.hpp"

struct Material
{
	glm::vec3 ambient = glm::vec3(1, 1, 1);
	glm::vec3 diffuse = glm::vec3(1, 1, 1);
	glm::vec3 specular = glm::vec3(1, 1, 1);
	float shininess = 32.0f;

	GLuint ambientLocation;
	GLuint diffuseLocation;
	GLuint specularLocation;
	GLuint shininessLocation;

	void Init(GLuint InProgram) {
		ambientLocation = glGetUniformLocation(InProgram, "material.ambient");
		diffuseLocation = glGetUniformLocation(InProgram, "material.diffuse");
		specularLocation = glGetUniformLocation(InProgram, "material.specular");
		shininessLocation = glGetUniformLocation(InProgram, "material.shininess");
	}

	void Update() {
		glUniform3fv(ambientLocation, 1, glm::value_ptr(ambient));
		glUniform3fv(diffuseLocation, 1, glm::value_ptr(diffuse));
		glUniform3fv(specularLocation, 1, glm::value_ptr(specular));
		glUniform1f(shininessLocation, shininess);
	}
};

struct Light {
	glm::vec3 position;

	glm::vec3 ambient = glm::vec3(1, 1, 1);
	glm::vec3 diffuse = glm::vec3(1, 1, 1);
	glm::vec3 specular = glm::vec3(1, 1, 1);

	GLuint ambientLocation;
	GLuint diffuseLocation;
	GLuint specularLocation;
	GLuint positionLocation;

	void Init(GLuint InProgram) {
		ambientLocation = glGetUniformLocation(InProgram, "light.ambient");
		diffuseLocation = glGetUniformLocation(InProgram, "light.diffuse");
		specularLocation = glGetUniformLocation(InProgram, "light.specular");
		positionLocation = glGetUniformLocation(InProgram, "light.position");
	}
	void Update() {
		glUniform3fv(ambientLocation, 1, glm::value_ptr(ambient));
		glUniform3fv(diffuseLocation, 1, glm::value_ptr(diffuse));
		glUniform3fv(specularLocation, 1, glm::value_ptr(specular));
		glUniform3fv(positionLocation, 1, glm::value_ptr(position));
	}
};


class ModelBase
{
public:
	virtual bool OnCreateGeometry() { return false; }
	virtual bool OnGPUProgram() { 
		glUseProgram(program);
		mvpLocation = glGetUniformLocation(program, "mvp");
		mLocation = glGetUniformLocation(program, "m");
		viewPositionLocation = glGetUniformLocation(program, "viewPosition");
		uvRepeatCountLocation = glGetUniformLocation(program, "uvRepeatCount");

		materia.Init(program);
		light.Init(program);
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
		glUniform3fv(viewPositionLocation, 1, glm::value_ptr(Camera::GetCamera()->GetCameraTransform().GetTranslation()));
		glUniform1f(uvRepeatCountLocation, uvRepeatCount);
		materia.Update();
		light.Update();
	}
	void UnUseProgram() { glUseProgram(0); }

	void SetLightPosition(const glm::vec3& lightPosition) {
		glUseProgram(program);
		light.position = lightPosition;
	}

	void SetMaterialAmbient(const glm::vec3& InAmbient) {
		materia.ambient = InAmbient;
	}
	void SetMaterialDiffuse(const glm::vec3& InDiffuse) {
		materia.diffuse = InDiffuse;
	}
	void SetMaterialSpecular(const glm::vec3& InSpecular) {
		materia.specular = InSpecular;
	}
	void SetMaterialShininess(float InShininess) {
		materia.shininess = InShininess;
	}
	void SetUVRepeatCount(float InUvRepeartCount) {
		uvRepeatCount = InUvRepeartCount;
	}
	void SetLightAmbient(const glm::vec3& InAmbient) {
		light.ambient = InAmbient;
	}
	void SetLightDiffuse(const glm::vec3& InDiffuse) {
		light.diffuse = InDiffuse;
	}
	void SetLightSpecular(const glm::vec3& InSpecular) {
		light.specular = InSpecular;
	}
protected:
	Transform transform;
	
	float uvRepeatCount = 1.0f;
	GLuint program;
	GLuint uvRepeatCountLocation;

	GLuint VAO = 0;
	GLuint mvpLocation;
	GLuint mLocation;
	GLuint viewPositionLocation;
	glm::vec4 lightColor = glm::vec4(1, 1, 1, 1);
	Material materia;
	Light light;
};