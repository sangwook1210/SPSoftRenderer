#pragma once

#include <Component/Component.h>
#include <Graphics/RenderQueue.h>

class RendererComponent : public Component
{
public:
	RendererComponent() = default;

	//_todo Material


	virtual void Submit(RenderQueue& queue) = 0;
};