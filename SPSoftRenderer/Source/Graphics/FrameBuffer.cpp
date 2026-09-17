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
