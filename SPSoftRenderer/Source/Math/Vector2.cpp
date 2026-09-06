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

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
	os << "Vector2: " << vector.x << ", " << vector.y;
	return os;
}