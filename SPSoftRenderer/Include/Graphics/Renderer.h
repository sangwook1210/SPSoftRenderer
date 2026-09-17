#pragma once

#include "windows.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Rasterizer.h"	

class Renderer
{
public:
	Renderer(int width, int height);

	void Render(HWND hWnd);

private:
	int width, height;

	FrameBuffer frameBuffer;
	Rasterizer rasterizer;

	void Present(HWND hWnd);
};