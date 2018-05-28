#pragma once
#include "CubeModel.hpp"


class CubeModelDemo : public RenderDemoBase
{
public:
	virtual bool OnInit() override
	{
		model.OnCreateGeometry();
		model.OnGPUProgram();

		auto camLocation = glm::vec3(0, 0, 10);
		Camera::GetCamera()->GetCameraTransform().SetTranslation(camLocation);
		Camera::GetCamera()->GetCameraTransform().SetDirection(-camLocation);

		model.GetTransform().SetScale(glm::vec3(4, 4, 4));

		return true;
	}
	virtual void OnUnInit() override
	{

	}
	virtual void OnRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model.OnRender();
	}
private:
	CubeModel model;
};