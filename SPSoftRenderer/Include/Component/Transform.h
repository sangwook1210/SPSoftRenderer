#pragma once

#include "Component/Component.h"
#include "Math/Vector3.h"
#include "Math/Matrix.h"

class Transform : public Component
{
private:
	Vector3 _position = { 0.0f, 0.0f, 0.0f };
	Vector3 _rotation = { 0.0f, 0.0f, 0.0f };	// _todo Quaternion으로 변경 필요
	Vector3 _scale = { 1.0f, 1.0f, 1.0f };

	// _todo 부모, 자식 게임오브젝트 추가

	Matrix4x4 _worldMatrix;

	bool _isDirty = true;

public:
	void SetPosition(Vector3 position);
	void SetRotation(Vector3 rotation);
	void SetScale(Vector3 scale);

	void AddPosition(Vector3 offset);
	void AddRotation(Vector3 offset);

	const Vector3& GetPosition() const;
	const Vector3& GetRotation() const;
	const Vector3& GetScale() const;

	const Matrix4x4& GetWorldMatrix();
};