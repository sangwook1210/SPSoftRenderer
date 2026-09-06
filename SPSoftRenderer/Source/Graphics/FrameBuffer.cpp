#include "Graphics/FrameBuffer.h"	

FrameBuffer::FrameBuffer(int width, int height)
	: width(width), height(height), pixels(width* height) {}

int FrameBuffer::GetWidth() const
{
	return width;
}
int FrameBuffer::GetHeight() const
{
	return height;
}
const uint32_t* FrameBuffer::GetPixels() const
{
	return pixels.data();
}

void FrameBuffer::SetPixel(int x, int y, uint32_t color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return;
	}

	pixels[x + height * y] = color;
}

void FrameBuffer::Clear(uint32_t color)
{
	for (uint32_t& pixel : pixels)
	{
		pixel = color;
	}
}