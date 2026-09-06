#pragma once

#include <ostream>	

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
};

std::ostream& operator<<(std::ostream& os, const Vector2& vector);