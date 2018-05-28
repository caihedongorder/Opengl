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

	void SetDirection(const glm::vec3& InAxisDir, EAxis::Type InAxis = EAxis::Z) {
		glm::mat3 mat(1.0);
		auto Axis = glm::normalize(InAxisDir);
		
		auto rightDir = glm::vec3(1, 0, 0);
		auto upDir = glm::normalize(glm::vec3(0, 1, 0));
		auto forwardDir = glm::vec3(0, 0, 1);

		if (InAxis == EAxis::X)
		{
			rightDir = Axis;
			// rightDir.x >= 0.0f
			if (rightDir.x > 0 || glm::epsilonEqual<float>(rightDir.x, 0.0f, 0.0001f))
			{
				upDir = glm::vec3(0, 1, 0);

				//如果朝前的方向 和Y轴平行，则选择原先X轴 作为向上的方向
				if (glm::epsilonEqual<float>(rightDir.y, 1.0f, 0.0001f))
				{
					upDir = glm::vec3(-rightDir.y, 0, 0);
				}
			}
			else
			{
				upDir = glm::vec3(0, -1, 0);
			}
			//先将右手坐标系转化成左手坐标系
			forwardDir = glm::normalize(glm::cross(rightDir,upDir));
			upDir = glm::normalize(glm::cross(forwardDir, rightDir));
		}
		else if (InAxis == EAxis::Y)
		{
			//当 Axis.x > 0.0f,说明 Axis 可以作为X轴的参考轴，从而 计算出forwardDir
			rightDir = Axis;
			auto ReferenceXAxis = Axis.x > 0.0f ? Axis : -Axis;
			forwardDir = glm::normalize(glm::cross(ReferenceXAxis , glm::vec3(0, 1, 0)));
			upDir = glm::normalize(glm::cross(forwardDir, rightDir));
		}
		else if(InAxis == EAxis::Z)
		{
			forwardDir = Axis;
			//先将右手坐标系转化成左手坐标系
			forwardDir = -forwardDir;
			//根据左手定律，计算每条轴新方向

			//如果朝前的方向 和Y轴平行，则选择原先Z轴 作为向上的方向
			if (glm::epsilonEqual<float>( glm::abs(forwardDir.y), 1.0f, 0.0001f))
			{
				upDir = glm::vec3(0, 0, forwardDir.y);
			}
			rightDir = glm::normalize(glm::cross(upDir,forwardDir));
			upDir = glm::normalize(glm::cross(forwardDir,rightDir));
		}
		transformMatrix3X3 = glm::mat4(1.0f);

		transformMatrix3X3[0] = rightDir;
		transformMatrix3X3[1] = upDir;
		transformMatrix3X3[2] = forwardDir;

		transformMatrix4X4 = glm::mat4(transformMatrix3X3);

		transformMatrix3X3Inverse = glm::transpose(transformMatrix3X3);
		transformMatrix4X4Inverse = glm::mat4(transformMatrix3X3Inverse);

		glm::extractEulerAngleXYZ(transformMatrix4X4, pitch, yaw, roll);
		pitch = glm::degrees(pitch);
		yaw = glm::degrees(yaw);
		roll = glm::degrees(roll);


		matrixDirty = false;
	}

	glm::vec3 GetDirection(EAxis::Type InAxis) const{
		update();
		if (InAxis == EAxis::X)
		{
			return glm::normalize(glm::vec3(1, 0, 0)*transformMatrix3X3Inverse);
		}
		else if (InAxis == EAxis::Y)
		{
			return glm::normalize(glm::vec3(0, 1, 0)*transformMatrix3X3Inverse);
		}
		else
		{
			return glm::normalize(glm::vec3(0, 0, 1)*transformMatrix3X3Inverse);
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
	glm::mat3 GetMaxtrix3X3Inverse() const {
		update();
		return transformMatrix3X3Inverse;
	}
	glm::mat4 GetMaxtrix4X4Inverse() const {
		update();
		return transformMatrix4X4Inverse;
	}
	Quat ToQuat() {
		update();
		return glm::toQuat(transformMatrix4X4Inverse);
	}
private:
	void update() const {
		if (matrixDirty)
		{
			transformMatrix4X4 = glm::eulerAngleXYZ(glm::radians(pitch), glm::radians(yaw),glm::radians(roll));
			transformMatrix3X3 = glm::mat3(transformMatrix4X4);

			transformMatrix3X3Inverse = glm::transpose(transformMatrix3X3);
			transformMatrix4X4Inverse = glm::mat4(transformMatrix3X3Inverse);

			matrixDirty = false;
		}
	}

	float roll, pitch, yaw;

	mutable glm::mat3 transformMatrix3X3Inverse;
	mutable glm::mat4 transformMatrix4X4Inverse;
	mutable glm::mat3 transformMatrix3X3;
	mutable glm::mat4 transformMatrix4X4;
	mutable bool matrixDirty = true;
};