#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Image.hpp"
#include "ShaderUtil.hpp"
#include "RenderDemoBase.hpp"
#include "LightModel.hpp"


class LightDemo : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		if (!light.OnCreateGeometry()) return false;
		if (!light.OnGPUProgram()) return false;

		if (!cube.OnCreateGeometry()) return false;
		if (!cube.OnGPUProgram()) return false;

		//camera
		auto camLocation = glm::vec3(10, 10, 10);
		Camera::GetCamera()->GetCameraTransform().SetTranslation(camLocation);
		Camera::GetCamera()->GetCameraTransform().SetDirection(-camLocation);

		//light

		//cube

		cube.GetTransform().SetScale(glm::vec3(4, 4, 4));
		
		return true;
	}
	virtual void OnUnInit() override
	{
		
	}
	virtual void OnRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float angle = glfwGetTime();
		auto lightlocation = glm::vec3(radius*glm::sin(angle), 5 * glm::sin(angle) , radius*glm::cos(angle));
		light.GetTransform().SetTranslation(lightlocation);
		light.GetTransform().SetDirection(-lightlocation);
		light.OnRender();

		cube.SetLightPosition(lightlocation);

		cube.OnRender();
	}
private:
	LightModel light;
	CubeModel cube;
	float radius = 10;
};