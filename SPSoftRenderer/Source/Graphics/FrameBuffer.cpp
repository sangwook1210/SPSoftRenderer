#include <cmath>	
#include <algorithm>
#include <vector>

#include "Graphics/FrameBuffer.h"	

FrameBuffer::FrameBuffer(int width, int height)
	: width(width), height(height), pixels(width* height), uint32Pixels(width * height) {}

int FrameBuffer::GetWidth() const
{
	return width;
}
int FrameBuffer::GetHeight() const
{
	return height;
}
const Color* FrameBuffer::GetPixels() const
{
	return pixels.data();
}
const uint32_t* FrameBuffer::GetPixelsByUInt32()
{
	for (int i = 0; i < uint32Pixels.size(); i++)
	{
		uint32Pixels[i] = pixels[i].ToUInt32();
	}

	return uint32Pixels.data();
}

void FrameBuffer::SetPixel(int x, int y, Color color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	pixels[x + height * y] = color;
}

void FrameBuffer::Clear(Color color)
{
	for (Color& pixel : pixels)
	{
		pixel = color;
	}
}

void FrameBuffer::DrawLine(
	int x0, int y0,
	int x1, int y1,
	Color color)
{
	// DDA 알고리즘
	int dx = x1 - x0;
	int dy = y1 - y0;

	int loopCnt;
	float x = x0;
	float y = y0;

	if (std::abs(dy) > std::abs(dx))
	{
		loopCnt = std::abs(dy);
	}
	else
	{
		loopCnt = std::abs(dx);
	}

	float x_increase = static_cast<float>(dx) / loopCnt;
	float y_increase = static_cast<float>(dy) / loopCnt;

	SetPixel(x, y, color);

	for (int i = 0; i < loopCnt; i++)
	{
		x += x_increase;
		y += y_increase;

		SetPixel(std::round(x), std::round(y), color);
	}

	/*
	float slope = static_cast<float>(dy) / dx;
	float x_intercept = y0 - slope * x0;

	int x = x0;
	int y = y0;
	int loopCnt = 0;
	bool isXIncrease = true;

	// 기울기가 1 이하라면 x에 대해 증가
	if (std::abs(slope) <= 1)
	{
		loopCnt = std::abs(x1 - x0);
		isXIncrease = true;
	}
	// 기울기가 1 초과라면 y에 대해 증가
	else
	{
		loopCnt = std::abs(y1 - y0);
		isXIncrease = false;
	}


	SetPixel(x, y, color);

	for (int i = 0; i < loopCnt; i++)
	{
		if (isXIncrease)
		{
			x += x0 < x1 ? 1 : -1;
			y = std::round(slope * x + x_intercept);
		}
		else
		{
			y += y0 < y1 ? 1 : -1;
			x = std::round((y - x_intercept) / slope);
		}

		SetPixel(x, y, color);
	}
	*/

	// _todo Bresenham 알고리즘 이용하여 구현해보기

}

void FrameBuffer::DrawTriangle(
	int x0, int y0, Color color0,
	int x1, int y1, Color color1,
	int x2, int y2, Color color2)
{
	// Barycentric Coordinates

	int x_min = std::min({ x0, x1, x2 });
	int x_max = std::max({ x0, x1, x2 });
	int y_min = std::min({ y0, y1, y2 });
	int y_max = std::max({ y0, y1, y2 });

	for (int y = y_min; y <= y_max; y++)
	{
		for (int x = x_min; x <= x_max; x++)
		{
			float areaSize = static_cast<float>(x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
			float alpha = (static_cast<float>(x1 - x) * (y2 - y) - (y1 - y) * (x2 - x)) / areaSize;
			float beta = (static_cast<float>(x2 - x) * (y0 - y) - (y2 - y) * (x0 - x)) / areaSize;
			float gamma = 1.0f - alpha - beta;

			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				Color color = color0 * alpha + color1 * beta + color2 * gamma;
				SetPixel(x, y, color);
			}
		}
	}
	

	/* Scan line Algorithm
	// Scan line

	DrawLine(x0, y0, x1, y1, color);
	DrawLine(x0, y0, x2, y2, color);
	DrawLine(x1, y1, x2, y2, color);

	int y_min = std::min({ y0, y1, y2 });
	int y_max = std::max({ y0, y1, y2 });

	for (int y = y_max; y >= y_min; y--)
	{
		std::vector<float> intersection;
		
		if (std::min(y0, y1) <= y && std::max(y0, y1) > y && y0 != y1)
		{
			intersection.push_back((y - y0) * static_cast<float>(x1 - x0) / (y1 - y0) + x0);
		}

		if (std::min(y0, y2) <= y && std::max(y0, y2) > y && y0 != y2)
		{
			intersection.push_back((y - y0) * static_cast<float>(x2 - x0) / (y2 - y0) + x0);
		}

		if (std::min(y1, y2) <= y && std::max(y1, y2) > y && y1 != y2)
		{
			intersection.push_back((y - y1) * static_cast<float>(x2 - x1) / (y2 - y1) + x1);
		}

		if (intersection.size() == 2)
		{
			for (int x = std::round(std::min({ intersection[0], intersection[1] })); x < std::round(std::max({ intersection[0], intersection[1] })); x++)
			{
				SetPixel(x, y, color);
			}
		}
	}
	*/
}