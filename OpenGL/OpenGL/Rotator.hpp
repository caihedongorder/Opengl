#pragma once
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Quat.hpp"
#include "Axis.hpp"
#include <glm/gtc/epsilon.hpp>


class Rotator
{
public:
	Rotator(float InRoll = 0.0f, float InPitch = 0.0f, float InYaw = 0.0f)
		:roll(InRoll),
		pitch(InPitch),
		yaw(InYaw)
	{

	}

	float GetRoll() const {
		return roll;
	}
	float GetPitch() const {
		return pitch;
	}
	float GetYaw() const {
		return yaw;
	}

	void SetRoll(float InRoll) {
		matrixDirty = true;
		roll = InRoll;
	}
	void SetPitch(float InPitch) {
		matrixDirty = true;
		pitch = InPitch;
	}
	void SetYaw(float InYaw) {
		matrixDirty = true;
		yaw = InYaw;
	}

	/*
		假定 Z轴为向前方向
	*/
	void SetDirection(const glm::vec3& InDirection) {
		SetDirection(EAxis::Z, InDirection);
	}
	void SetDirection(EAxis::Type InAxis, const glm::vec3& InAxisDir, const glm::vec3& up = glm::vec3(0, 1, 0)) {
		glm::mat3 mat(1.0);
		auto Axis = glm::normalize(InAxisDir);
		
		auto rightDir = glm::vec3(1, 0, 0);
		auto upDir = glm::normalize(up);
		auto forwardDir = glm::vec3(0, 0, 1);

		if (InAxis == EAxis::X)
		{
			rightDir = Axis;
			forwardDir = glm::normalize(glm::cross(rightDir, upDir));
			upDir = glm::normalize(glm::cross(forwardDir, rightDir));
		}
		else if (InAxis == EAxis::Y)
		{
			rightDir = glm::normalize(glm::cross(upDir, Axis));
			upDir = Axis;
			forwardDir = glm::normalize(glm::cross(rightDir, upDir));
		}
		else if(InAxis == EAxis::Z)
		{
			forwardDir = Axis;
			rightDir = glm::normalize(glm::cross(upDir, forwardDir));
			upDir = glm::normalize(glm::cross(forwardDir, rightDir));
		}
		transformMatrix4X4 = glm::mat4(1.0f);

		transformMatrix4X4[0][0] = rightDir[0];
		transformMatrix4X4[1][0] = rightDir[1];
		transformMatrix4X4[2][0] = rightDir[2];

		transformMatrix4X4[0][1] = upDir[0];
		transformMatrix4X4[1][1] = upDir[1];
		transformMatrix4X4[2][1] = upDir[2];

		transformMatrix4X4[0][2] = forwardDir[0];
		transformMatrix4X4[1][2] = forwardDir[1];
		transformMatrix4X4[2][2] = forwardDir[2];

		transformMatrix3X3 = glm::mat3(transformMatrix4X4);

		glm::extractEulerAngleXYZ(transformMatrix4X4, pitch, yaw, roll);

		matrixDirty = false;
	}

	glm::vec3 GetDirection(EAxis::Type InAxis) const{
		update();
		if (InAxis == EAxis::X)
		{
			return glm::normalize(glm::vec3(1, 0, 0)*transformMatrix3X3);
		}
		else if (InAxis == EAxis::Y)
		{
			return glm::normalize(glm::vec3(0, 1, 0)*transformMatrix3X3);
		}
		else
		{
			return glm::normalize(glm::vec3(0, 0, 1)*transformMatrix3X3);
		}
	}

	glm::mat3 GetMaxtrix3X3() const {
		update();
		return transformMatrix3X3;
	}
	glm::mat4 GetMaxtrix4X4() const {
		update();
		return transformMatrix4X4;
	}
	Quat ToQuat() {
		update();
		return glm::toQuat(transformMatrix4X4);
	}
private:
	void update() const {
		if (matrixDirty)
		{
			transformMatrix4X4 = glm::eulerAngleXYZ(glm::radians(pitch), glm::radians(yaw),glm::radians(roll));
			transformMatrix3X3 = glm::mat3(transformMatrix4X4);
			matrixDirty = false;
		}
	}

	float roll, pitch, yaw;

	mutable glm::mat4 transformMatrix4X4;
	mutable glm::mat3 transformMatrix3X3;
	mutable bool matrixDirty;
};