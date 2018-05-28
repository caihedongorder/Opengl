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
	glm::mat4 GetTransformMatrixWithScale() const {
		update();
		return transformMatrixWithScale;
	}
	glm::mat4 GetTransformMatrixWithScaleInverse() const {
		update();
		return transformMatrixWithScaleInvserse;
	}
	glm::mat4 GetTransformMatrixWithoutScale() const {
		update();
		return transformMatrixWithoutScale;
	}
	glm::mat4 GetTransformMatrixWithoutScaleInverse() const {
		update();
		return transformMatrixWithoutScaleInvserse;
	}
	bool MatrixIsDirty() const { return matrixDirty; }
private:
	glm::vec3 translation;
	glm::vec3 scale;
	Rotator rotator;

	void update() const {
		if (matrixDirty)
		{
			auto rotateMat3 = rotator.GetMaxtrix3X3();
			auto rotateMat3Inv = rotator.GetMaxtrix3X3Inverse();

			transformMatrixWithScale = glm::mat4(rotateMat3)* glm::scale(scale);
			transformMatrixWithScale[3] = glm::vec4(translation, 1.0f);

			transformMatrixWithoutScale = glm::mat4(rotateMat3);
			transformMatrixWithoutScale[3] = glm::vec4(translation, 1.0f);

			transformMatrixWithScaleInvserse = glm::mat4(rotateMat3Inv)* glm::scale(glm::vec3(1, 1, 1) / scale);
			transformMatrixWithScaleInvserse[3] = glm::vec4( glm::mat3(transformMatrixWithScaleInvserse) * (-translation) ,1.0f );

			transformMatrixWithoutScaleInvserse = glm::mat4(rotateMat3Inv);
			transformMatrixWithoutScaleInvserse[3] = glm::vec4(glm::mat3(transformMatrixWithoutScaleInvserse) * (-translation), 1.0f);

			matrixDirty = false;
		}
	}
	mutable glm::mat4 transformMatrixWithScale;
	mutable glm::mat4 transformMatrixWithoutScale;
	mutable glm::mat4 transformMatrixWithScaleInvserse;
	mutable glm::mat4 transformMatrixWithoutScaleInvserse;
	mutable bool matrixDirty = true;
};