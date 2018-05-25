#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderDemoBase
{
public:
	RenderDemoBase() {
	}
	virtual ~RenderDemoBase() {
	}
	virtual bool OnInit() { return false; }
	virtual void OnUnInit() {}
	virtual void OnRender(){}
};