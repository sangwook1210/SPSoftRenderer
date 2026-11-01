#pragma once

namespace Math
{
	constexpr float PI = 3.14159265358979323846f;

	constexpr float ToRadian(float degree)
	{
		return degree * Math::PI / 180.0f;
	}

	constexpr float ToDegree(float radian)
	{
		return radian * 180.0f / Math::PI;
	}
}