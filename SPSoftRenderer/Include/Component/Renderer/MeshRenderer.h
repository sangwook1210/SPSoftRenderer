#pragma once

#include <Component/Renderer/RendererComponent.h>
#include <Graphics/Mesh.h>

class MeshRenderer : public RendererComponent
{
public:
	MeshRenderer();
	MeshRenderer(Mesh* mesh);

	Mesh* mesh = nullptr;

	void Submit(RenderQueue& queue) override;
};