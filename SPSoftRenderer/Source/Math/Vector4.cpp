#include "Math/Vector4.h"
#include "Math/Matrix.h"

Vector4::Vector4(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w) {
}
Vector4::Vector4(Matrix4x1 vectorMatrix)
	:x(vectorMatrix.values[0][0]), y(vectorMatrix.values[1][0]),
	z(vectorMatrix.values[2][0]), w(vectorMatrix.values[3][0]) {
}

#pragma region 벡터 연산

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}
Vector4 Vector4::operator- (const Vector4& other)const
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}
Vector4 Vector4::operator*(float scaler)const
{
	return Vector4(x * scaler, y * scaler, z * scaler, w * scaler);
}
Vector4 Vector4::operator/(float scaler)const
{
	return Vector4(x / scaler, y / scaler, z / scaler, w / scaler);
}

Vector4& Vector4::Scale(float scaler)
{
	x *= scaler;
	y *= scaler;
	z *= scaler;
	w *= scaler;

	return *this;
}

float Vector4::Length()const
{
	return std::sqrt(this->LengthSquared());
}
float Vector4::LengthSquared()const
{
	return x * x + y * y + z * z + w * w;
}

Vector4& Vector4::Normalize()
{
	float length = this->Length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;

	return *this;
}
Vector4 Vector4::Normalized()const
{
	float length = this->Length();
	return Vector4(x / length, y / length, z / length, w / length);
}

float Vector4::Distance(const Vector4& other)const
{
	return std::sqrt(this->DistanceSquared(other));
}
float Vector4::DistanceSquared(const Vector4& other)const
{
	// 컴파일러가 최적화해줌
	float dx = other.x - x;
	float dy = other.y - y;
	float dz = other.z - z;
	float dw = other.w - w;
	return dx * dx + dy * dy + dz * dz + dw * dw;
}

Vector4 Vector4::Dot(const Vector4& other)const
{
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

#pragma endregion

std::ostream& operator<<(std::ostream& os, const Vector4& vector)
{
	os << "Vector4: " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w;
	return os;
}