#pragma once
#include <glm/fwd.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Rotator.hpp"

class Quat
{
public:
	Quat() {
		
	}
	Quat(const glm::quat& Inq) {
		q = Inq;
	}

	glm::vec3 GetRotateAxis() const {
		//glm::pi
		return glm::normalize(glm::vec3(q.x,q.y,q.z));
	}
	float GetRotateAngle() const {
		return glm::angle(q);
	}
private:
	glm::quat q = glm::quat_identity<float,glm::qualifier::highp>();
};