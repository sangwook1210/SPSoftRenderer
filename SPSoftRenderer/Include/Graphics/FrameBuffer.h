#pragma once

#include "Math/Color.h"	
#include <vector>

class FrameBuffer
{
public:
	FrameBuffer(int width, int height);

	int GetWidth() const;
	int GetHeight() const;
	const Color* GetPixels() const;
	const uint32_t* GetPixelsByUInt32();


	void SetPixel(int x, int y, Color color);
	void Clear(Color color);

	void DrawLine(
		int x0, int y0,
		int x1, int y1,
		Color color);
	void DrawTriangle(
		int x0, int y0, Color color0,
		int x1, int y1, Color color1,
		int x2, int y2, Color color2);

private:
	int width, height;
	std::vector<Color> pixels;
	std::vector<uint32_t> uint32Pixels;
};