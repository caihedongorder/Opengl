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
	virtual bool OnGPUProgram() { return false; }
	virtual void OnRender(){}
	Transform& GetTransform() { return transform; }
protected:
	Transform transform;
};