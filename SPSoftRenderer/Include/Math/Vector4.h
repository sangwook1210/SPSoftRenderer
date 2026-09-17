#pragma once

#include <ostream>	

struct Vector4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	Vector4() {}
	Vector4(float x, float y, float z, float w);

#pragma region ∫§≈Õ ø¨ªÍ

	Vector4 operator+(const Vector4& other)const;
	Vector4 operator-(const Vector4& other)const;
	Vector4 operator*(float scaler)const;
	Vector4 operator/(float scaler)const;

	Vector4& Scale(float scaler);

	float Length()const;
	float LengthSquared()const;

	Vector4& Normalize();
	Vector4 Normalized()const;

	float Distance(const Vector4& other)const;
	float DistanceSquared(const Vector4& other)const;

	Vector4 Dot(const Vector4& other)const;

#pragma endregion

};

std::ostream& operator<<(std::ostream& os, const Vector4& vector);