#pragma once
#include <glm/detail/type_vec.hpp>
#include "Rotator.hpp"

class Transform
{
public:
	Transform(const glm::vec3& InTranslation = glm::vec3(0,0,0),const Rotator& InRotator = Rotator(),const glm::vec3& InScale = glm::vec3(1.0f,1.0f,1.0f))
		:translation(InTranslation),
		scale(InScale),
		rotator(InRotator)
	{
	}

	void SetDirection(const glm::vec3& InDirection, EAxis::Type InAxis = EAxis::Z) {
		rotator.SetDirection(InDirection, InAxis);
		matrixDirty = true;
	}

	void Move(const glm::vec3& InTranslation) {
		translation += InTranslation;
		matrixDirty = true;
	}
	void SetTranslation(const glm::vec3& InTranslation) {
		translation = InTranslation;
		matrixDirty = true;
	}
	void SetScale(const glm::vec3& InScale) {
		scale = InScale;
		matrixDirty = true;
	}
	void SetRotator(const Rotator& InRotator) {
		rotator = InRotator;
		matrixDirty = true;
	}
	glm::vec3 GetUnitAxis(EAxis::Type InAxis) const {
		return rotator.GetDirection(InAxis);
	}

	glm::vec3 GetTranslation() const {
		return translation;
	}
	glm::vec3 GetScale() const {
		return scale;
	}
	Rotator GetRotator() const {
		return rotator;
	}
	glm::mat4 GetRotateMatrix() const {
		update();
		return rotator.GetMaxtrix4X4();
	}
	glm::mat4 GetTransformMatrix() const {
		update();
		return transformMatrix;
	}
	glm::mat4 GetTransformMatrixInverse() const {
		update();
		return glm::inverse(transformMatrix);
	}

	bool MatrixIsDirty() const { return matrixDirty; }
private:
	glm::vec3 translation;
	glm::vec3 scale;
	Rotator rotator;

	void update() const {
		if (matrixDirty)
		{
			transformMatrix = rotator.GetMaxtrix4X4()* glm::scale(scale);
			transformMatrix[3] = glm::vec4(translation,1.0f);
			matrixDirty = false;
		}
	}
	mutable glm::mat4 transformMatrix;
	mutable bool matrixDirty = true;
};