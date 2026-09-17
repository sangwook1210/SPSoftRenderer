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

private:
	int width, height;
	std::vector<Color> pixels;
	std::vector<uint32_t> uint32Pixels;
};