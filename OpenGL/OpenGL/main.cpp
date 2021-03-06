// OpenGL.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderUtil.hpp"
#include "TriangleDemo.hpp"
#include "ColorfulTriangle.hpp"
#include "Texture.hpp"
#include "TransformDemo.hpp"
#include "DoubleTexture.hpp"
#include "CubeDemo.hpp"
#include "Billboard.hpp"
#include "CubeModelDemo.hpp"
#include "LightDemo.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
RenderDemoBase* GRenderDemo = nullptr;

void ProcessInput(GLFWwindow* InWindow)
{
	if (glfwGetKey(InWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(InWindow,true);
}


int main() {
	if (!glfwInit())
	{
		return -1;
	}
	//设置Opengl 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建一个glfw窗口
	auto Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello GLFW", nullptr, nullptr);
	if (!Window)
	{
		glfwTerminate();
		return -1;
	}

	//在使用glad加载 opengl API前必须调用glfwMakeContextCurrent
	glfwMakeContextCurrent(Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -1;
	}
	//设置Opengl视口
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetWindowSizeCallback(Window, [](auto window, auto width, auto height) {
		auto OldWindow = glfwGetCurrentContext();
		if (OldWindow != window)
		{
			glfwMakeContextCurrent(window);
		}
		glViewport(0, 0, width, height);
		if (OldWindow != window)
		{
			glfwMakeContextCurrent(OldWindow);
		}
	});

	//创建集合体
	GRenderDemo = new LightDemo();
	if (!GRenderDemo->OnInit()) {
		glfwTerminate();
		return -1;
	}

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//窗口消息循环
	while (!glfwWindowShouldClose(Window))
	{
		ProcessInput(Window);

		GRenderDemo->OnRender();

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
	GRenderDemo->OnUnInit();
	delete GRenderDemo;
	GRenderDemo = nullptr;

	glfwTerminate();
	return 0;

}