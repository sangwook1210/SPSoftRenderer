#pragma once

#include <ostream>	

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	#pragma region ∫§≈Õ ø¨ªÍ

	Vector2 operator+(const Vector2& other)const;
	Vector2 operator-(const Vector2& other)const;
	Vector2 operator*(float scaler)const;
	Vector2 operator/(float scaler)const;

	void Scale(float scaler);

	float Length()const;
	float LengthSquared()const;

	void Normalize();
	Vector2 Normalized()const;

	float Distance(const Vector2& other)const;
	float DistanceSquared(const Vector2& other)const;

	Vector2 Dot(const Vector2& other)const;

	#pragma endregion

};

std::ostream& operator<<(std::ostream& os, const Vector2& vector);