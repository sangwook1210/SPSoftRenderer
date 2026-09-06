#pragma once

#include <cstdint>

struct Color
{
	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
		: r(r), g(g), b(b), a(a)
	{
	}

	// 0.0 ~ 1.0
	float r;
	float g;
	float b;
	float a;

	std::uint32_t ToUInt32() const;

	Color operator+ (const Color& other) const;
	Color operator- (const Color& other) const;
	Color operator* (float scaler) const;
	Color operator/ (float scaler) const;

	Color Dot(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) const;
	Color Dot(const Color& other) const;

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color White;
	static const Color Black;
};