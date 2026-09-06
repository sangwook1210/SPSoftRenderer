#include "Math/Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

#pragma region 벡터 연산

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator- (const Vector2 & other)const
{
	return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator*(float scaler)const
{
	return Vector2(x * scaler, y * scaler);
}
Vector2 Vector2::operator/(float scaler)const
{
	return Vector2(x / scaler, y / scaler);
}

void Vector2::Scale(float scaler)
{
	x *= scaler;
	y *= scaler;
}

float Vector2::Length()const
{
	return std::sqrt(this->LengthSquared());
}
float Vector2::LengthSquared()const
{
	return x * x + y * y;
}

void Vector2::Normalize()
{
	float length = this->Length();
	x /= length;
	y /= length;
}
Vector2 Vector2::Normalized()const
{
	float length = this->Length();
	return Vector2(x / length, y / length);
}

float Vector2::Distance(const Vector2& other)const
{
	return std::sqrt(this->DistanceSquared(other));
}
float Vector2::DistanceSquared(const Vector2& other)const
{
	// 컴파일러가 최적화해줌
	float width = other.x - x;
	float height = other.y - y;
	return width * width + height * height;
}

Vector2 Vector2::Dot(const Vector2& other)const
{
	return Vector2(x * other.x, y * other.y);
}

#pragma endregion

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
	os << "Vector2: " << vector.x << ", " << vector.y;
	return os;
}