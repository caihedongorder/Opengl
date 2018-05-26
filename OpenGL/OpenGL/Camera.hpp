#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Transform.hpp"

class Camera
{
public:
	Camera() {
		ViewMatrixDirty = true;
		ProjectionMatrixDirty = true;

		fov = 90;
		ar = 800.0f / 600;
		nearPlane = 1.0f;
		farPlane = 1000.0f;
	}
	~Camera() {}

	void setProjection(float InFov, float InAr, float InNearPlane, float InFarPlane) {
		setFOV(InFov);
		setAr(InAr);
		setNearPlane(InNearPlane);
		setFarPlane(InFarPlane);
	}
	void setFOV(float InFov) { ProjectionMatrixDirty = true; fov = InFov; }
	float getFOV(float InFov) const { return fov; }
	void setAr(float InAr) { ProjectionMatrixDirty = true; ar = InAr; }
	float getAr() const { return ar; }
	void setNearPlane(float InNearPlane) { ProjectionMatrixDirty = true; nearPlane = InNearPlane; }
	float getNearPlane() const { return nearPlane; }
	void setFarPlane(float InFarPlane) { ProjectionMatrixDirty = true; farPlane = InFarPlane; }
	float getFarPlane() const { return farPlane; }

	void setView(const glm::vec3& InEyeAt, const glm::vec3& InTargetPosition, const glm::vec3& InUpDir) {
		camTransform.SetTranslation(InEyeAt);
		camTransform.SetDirection(InTargetPosition - InEyeAt);
	}
	Transform& GetCameraTransform() {
		return camTransform;
	}
	
	const glm::mat4& getViewMatrix() const { Update(); return ViewMatrix; }
	const glm::mat4& getProjectionMatrix() const { Update(); return ProjectionMatrix; };
	const glm::mat4& getViewProjectionMatrix() const { Update(); return ViewProjectionMatrix; };

	static Camera* GetDefaultCamera() { static Camera _sCam; return &_sCam; }
private:
	void Update() const {
		bool ViewProjectionMatrixDirty = false;

		if (camTransform.MatrixIsDirty())
		{
#if 0
/* 
				每个模型在渲染之前，都有一个默认相机朝向 也就是永远指向该模型的中心点向里的朝向，也就是和模型的朝向Z轴相反的朝向就是默认相机朝向(0，0，-1)

				相机变换的基本原理是 对默认相机朝向 做逆运算
					

			*/
			//构建默认相机朝向
			Rotator DefualtCamRotator(0, 0, 180);
			static glm::mat3 DefaultCamMatrix = DefualtCamRotator.GetMaxtrix3X3();
			auto rotateMatrix = DefaultCamMatrix * glm::transpose( camTransform.GetRotator().GetMaxtrix3X3() );
#endif
			
			auto rotateMatrix = camTransform.GetRotator().GetMaxtrix3X3();
			rotateMatrix[0][2] = -rotateMatrix[0][2];
			rotateMatrix[1][2] = -rotateMatrix[1][2];
			rotateMatrix[2][2] = -rotateMatrix[2][2];

			ViewMatrix[3][0] = glm::dot(glm::vec3(rotateMatrix[0][0], rotateMatrix[1][0], rotateMatrix[2][0]), -camTransform.GetTranslation());
			ViewMatrix[3][1] = glm::dot(glm::vec3(rotateMatrix[0][1], rotateMatrix[1][1], rotateMatrix[2][1]), -camTransform.GetTranslation());
			ViewMatrix[3][2] = glm::dot(glm::vec3(rotateMatrix[0][2], rotateMatrix[1][2], rotateMatrix[2][2]), -camTransform.GetTranslation());

			auto translateInvs = glm::translate(glm::mat4(1.0f),-camTransform.GetTranslation());
			ViewMatrix = glm::mat4(rotateMatrix)*translateInvs;

			ViewProjectionMatrixDirty = true;
		}

		if (ProjectionMatrixDirty)
		{
			ProjectionMatrix = glm::perspective(glm::radians(fov), ar, nearPlane, farPlane);
			ProjectionMatrixDirty = false;
			ViewProjectionMatrixDirty = true;
		}

		if (ViewProjectionMatrixDirty)
		{
			ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
			ViewProjectionMatrixDirty = false;
		}
	}
private:
	float fov;
	float ar;
	float nearPlane;
	float farPlane;

	Transform camTransform;

	mutable glm::mat4 ViewMatrix;
	mutable glm::mat4 ProjectionMatrix;
	mutable glm::mat4 ViewProjectionMatrix;

	mutable bool ViewMatrixDirty;
	mutable bool ProjectionMatrixDirty;
};
