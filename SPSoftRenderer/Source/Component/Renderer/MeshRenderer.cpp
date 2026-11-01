
#include "Component/Renderer/MeshRenderer.h"
#include "Core/GameObject.h"

MeshRenderer::MeshRenderer()
{

}


MeshRenderer::MeshRenderer(Mesh* mesh)
	:mesh(mesh)
{

}

void MeshRenderer::Submit(RenderQueue& queue)
{
	queue.Submit({
		mesh,
		this->gameObject->transform->GetWorldMatrix()
		});
}