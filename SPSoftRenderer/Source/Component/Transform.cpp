#include "Component/Transform.h"
#include "Math/MathUtils.h"
#include <cmath>

void Transform::SetPosition(Vector3 position)
{
	_position = position;
	_isDirty = true;
}
void Transform::SetRotation(Vector3 rotation)
{
	_rotation = rotation;
	_isDirty = true;
}
void Transform::SetScale(Vector3 scale)
{
	_scale = scale;
	_isDirty = true;
}

void Transform::AddPosition(Vector3 offset)
{
	_position = _position + offset;
	_isDirty = true;
}
void Transform::AddRotation(Vector3 offset)
{
	_rotation = _rotation + offset;
	_isDirty = true;
}

const Vector3& Transform::GetPosition() const
{
	return _position;
}
const Vector3& Transform::GetRotation() const
{
	return _rotation;
}
const Vector3& Transform::GetScale() const
{
	return _scale;
}

const Matrix4x4& Transform::GetWorldMatrix()
{
	if (_isDirty)
	{
		// 행렬 계산
		Matrix4x4 transformMatrix({
			1,0,0,_position.x,
			0,1,0, _position.y,
			0,0,1,_position.z,
			0,0,0,1
			});

		float radianX = Math::ToRadian(_rotation.x);
		float radianY = Math::ToRadian(_rotation.y);
		float radianZ = Math::ToRadian(_rotation.z);

		Matrix4x4 rotateMatrixX({
			1, 0, 0, 0,
			0, cosf(radianX), -sinf(radianX), 0,
			0, sinf(radianX), cosf(radianX) ,0,
			0, 0, 0, 1
			});
		Matrix4x4 rotateMatrixY({
			cosf(radianY), 0, sinf(radianY), 0,
			0, 1, 0, 0,
			-sinf(radianY), 0, cosf(radianY), 0,
			0, 0, 0, 1
			});
		Matrix4x4 rotateMatrixZ({
			cosf(radianZ), -sinf(radianZ), 0, 0,
			sinf(radianZ), cosf(radianZ) ,0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			});

		Matrix4x4 scaleMatrix({
			_scale.x, 0,0, 0,
			0,_scale.y, 0, 0,
			0, 0, _scale.z, 0,
			0, 0, 0, 1
			});

		_worldMatrix = transformMatrix
			* rotateMatrixX * rotateMatrixY * rotateMatrixZ
			* scaleMatrix;

		_isDirty = false;
	}

	return _worldMatrix;
}