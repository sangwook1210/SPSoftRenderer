#pragma once

#include "windows.h"
#include "FrameBuffer.h"

class Renderer
{
public:
	Renderer(int width, int height);

	void Render(HWND hWnd);

private:
	int width, height;

	FrameBuffer frameBuffer;

	void Present(HWND hWnd);
};