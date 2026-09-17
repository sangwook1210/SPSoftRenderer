#pragma once

#include "Graphics/FrameBuffer.h"
#include "Math/Color.h"

class Rasterizer
{
public:

	void DrawLine(
		int x0, int y0,
		int x1, int y1,
		Color color,
		FrameBuffer& frameBuffer);
	void DrawTriangle(
		int x0, int y0, Color color0,
		int x1, int y1, Color color1,
		int x2, int y2, Color color2,
		FrameBuffer& frameBuffer);

};