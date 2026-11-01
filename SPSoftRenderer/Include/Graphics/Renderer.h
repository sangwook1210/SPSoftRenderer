#pragma once

#include "windows.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Rasterizer.h"
#include "Core/GameObject.h"
#include "Component/Renderer/RendererComponent.h"
#include <Graphics/Mesh.h>
#include "RenderQueue.h"



class Renderer
{
private:
	int width, height;

	BITMAPINFO bitmapInfo = {};

	FrameBuffer frameBuffer;
	Rasterizer rasterizer;

	RenderQueue renderQueue;

	void Present(HWND hWnd);

public:
	Renderer(int width, int height);

	void Render(HWND hWnd, std::vector<GameObject*>& gameObjects);

};
