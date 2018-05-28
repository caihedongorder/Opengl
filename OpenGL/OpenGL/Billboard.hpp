#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include <glm/gtx/matrix_query.inl>
#include <glm/gtc/constants.hpp>

class Billboard : public RenderDemoBase
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

		//����VBO
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0));
		glEnableVertexAttribArray(0);

		int indices[] = {
			//ǰ��
			0,2,1,0,3,2,
			4,5,6,4,6,7,
			//����
			4,3,0,4,7,3,
			5,1,2,5,2,6,
			//����
			7,6,2,7,2,3,
			4,1,5,4,0,1,
		};
		//����IBO
		GLuint IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		//glBindVertexArray(0);

		program = ShaderUtil::CreateProgram("shaders/demo/CubeDemo.vert", "shaders/demo/CubeDemo.frag");
		mvpLocation = glGetUniformLocation(program, "mvp");
		modelTransform.SetTranslation(glm::vec3(0, 0, 0));
		modelTransform1.SetTranslation(glm::vec3(0, 5, 0));
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

		//�������λ��
		float Angle = glfwGetTime();
		float CamX = Radus * cos(Angle);
		float CamY = Radus * sin(Angle);
		float CamZ = Radus * sin(Angle);
		Transform& CamTransform = Camera::GetDefaultCamera()->GetCameraTransform();
		glm::vec3 CamLocation = glm::vec3(CamX, CamY , CamZ);
		static glm::vec3 InitCamLocation = CamLocation;
		CamTransform.SetTranslation(CamLocation);
		CamTransform.SetDirection(-CamLocation);

		//modelTransform.SetScale(glm::vec3(4, 4, 4) * (sin(float(glfwGetTime())/2.0f *2 * glm::pi<float>())+2.0f)/3.0f);
		modelTransform.SetScale(glm::vec3(4, 4, 4));
		modelTransform.SetDirection(CamLocation);
		//auto viewMat = glm::lookAt(CamLocation, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//glm::mat4 mvp = Camera::GetDefaultCamera()->getProjectionMatrix() * viewMat * modelTransform.GetTransformMatrix();

		//modelTransform.SetRotator(Rotator(Angle *0,0,glm::degrees(Angle)));
		glm::mat4 mvp = Camera::GetDefaultCamera()->getViewProjectionMatrix()* modelTransform.GetTransformMatrixWithScale();
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glUseProgram(0);

		//���Ƶڶ��������
		glUseProgram(program);
		modelTransform1.SetScale(glm::vec3(2, 2, 2));
		mvp = Camera::GetDefaultCamera()->getViewProjectionMatrix()* modelTransform1.GetTransformMatrixWithScale();
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glUseProgram(0);

	}
private:
	GLuint program = 0;
	GLuint VAO = 0;
	GLuint mvpLocation;
	Transform modelTransform;
	Transform modelTransform1;
	float Radus = 10.0f;
};