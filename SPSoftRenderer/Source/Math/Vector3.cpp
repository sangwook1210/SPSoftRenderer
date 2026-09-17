#include "Math/Vector3.h"

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z) {
}

#pragma region 벡터 연산

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3 Vector3::operator- (const Vector3& other)const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3 Vector3::operator*(float scaler)const
{
	return Vector3(x * scaler, y * scaler, z * scaler);
}
Vector3 Vector3::operator/(float scaler)const
{
	return Vector3(x / scaler, y / scaler, z / scaler);
}

Vector3& Vector3::Scale(float scaler)
{
	x *= scaler;
	y *= scaler;
	z *= scaler;

	return *this;
}

float Vector3::Length()const
{
	return std::sqrt(this->LengthSquared());
}
float Vector3::LengthSquared()const
{
	return x * x + y * y + z * z;
}

Vector3& Vector3::Normalize()
{
	float length = this->Length();
	x /= length;
	y /= length;
	z /= length;

	return *this;
}
Vector3 Vector3::Normalized()const
{
	float length = this->Length();
	return Vector3(x / length, y / length, z / length);
}

float Vector3::Distance(const Vector3& other)const
{
	return std::sqrt(this->DistanceSquared(other));
}
float Vector3::DistanceSquared(const Vector3& other)const
{
	// 컴파일러가 최적화해줌
	float dx = other.x - x;
	float dy = other.y - y;
	float dz = other.z - z;
	return dx * dx + dy * dy + dz * dz;
}

Vector3 Vector3::Dot(const Vector3& other)const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

#pragma endregion

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "Vector3: " << vector.x << ", " << vector.y << ", " << vector.z;
	return os;
}