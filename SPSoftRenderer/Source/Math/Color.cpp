#include <algorithm>

#include "Math/Color.h"

uint32_t Color::ToUInt32() const
{
    uint32_t R = static_cast<uint32_t>(std::clamp(r, 0.0f, 1.0f) * 255.0f);
    uint32_t G = static_cast<uint32_t>(std::clamp(g, 0.0f, 1.0f) * 255.0f);
    uint32_t B = static_cast<uint32_t>(std::clamp(b, 0.0f, 1.0f) * 255.0f);
    uint32_t A = static_cast<uint32_t>(std::clamp(a, 0.0f, 1.0f) * 255.0f);

    return (A << 24) | (R << 16) | (G << 8) | B;    // 0xAARRGGBB
}

Color Color::operator+(const Color& other) const
{
    return Color(
        std::clamp(r + other.r, 0.0f, 1.0f),
        std::clamp(g + other.g, 0.0f, 1.0f),
        std::clamp(b + other.b, 0.0f, 1.0f),
        std::clamp(a + other.a, 0.0f, 1.0f)
    );
}

Color Color::operator-(const Color& other) const
{
    return Color(
        std::clamp(r - other.r, 0.0f, 1.0f),
        std::clamp(g - other.g, 0.0f, 1.0f),
        std::clamp(b - other.b, 0.0f, 1.0f),
        std::clamp(a - other.a, 0.0f, 1.0f)
    );
}

Color Color::operator*(float scaler) const
{
    return Color(
        std::clamp(r * scaler, 0.0f, 1.0f),
        std::clamp(g * scaler, 0.0f, 1.0f),
        std::clamp(b * scaler, 0.0f, 1.0f),
        std::clamp(a * scaler, 0.0f, 1.0f)
    );
}

Color Color::operator/(float scaler) const
{
    return Color(
        std::clamp(r / scaler, 0.0f, 1.0f),
        std::clamp(g / scaler, 0.0f, 1.0f),
        std::clamp(b / scaler, 0.0f, 1.0f),
        std::clamp(a / scaler, 0.0f, 1.0f)
    );
}

Color Color::Dot(float r, float g, float b, float a) const
{
    return Color(
        std::clamp(this->r * r, 0.0f, 1.0f),
        std::clamp(this->g * g, 0.0f, 1.0f),
        std::clamp(this->b * b, 0.0f, 1.0f),
        std::clamp(this->a * a, 0.0f, 1.0f)
    );
}
Color Color::Dot(const Color& color) const 
{
    return Color(
        std::clamp(r * color.r, 0.0f, 1.0f),
        std::clamp(g * color.g, 0.0f, 1.0f),
        std::clamp(b * color.b, 0.0f, 1.0f),
        std::clamp(a * color.a, 0.0f, 1.0f)
    );
}

const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f);