#pragma once

#include <vector>

class FrameBuffer
{
public:
	FrameBuffer(int width, int height);

	int GetWidth() const;
	int GetHeight() const;
	const uint32_t* GetPixels() const;


	void SetPixel(int x, int y, uint32_t color);
	void Clear(uint32_t color);

private:
	int width, height;
	std::vector<uint32_t> pixels;
};