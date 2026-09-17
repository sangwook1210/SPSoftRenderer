#pragma once

#include <ostream>	

struct Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3() {}
	Vector3(float x, float y, float z);

#pragma region ∫§≈Õ ø¨ªÍ

	Vector3 operator+(const Vector3& other)const;
	Vector3 operator-(const Vector3& other)const;
	Vector3 operator*(float scaler)const;
	Vector3 operator/(float scaler)const;

	Vector3& Scale(float scaler);

	float Length()const;
	float LengthSquared()const;

	Vector3& Normalize();
	Vector3 Normalized()const;

	float Distance(const Vector3& other)const;
	float DistanceSquared(const Vector3& other)const;

	Vector3 Dot(const Vector3& other)const;

#pragma endregion

};

std::ostream& operator<<(std::ostream& os, const Vector3& vector);