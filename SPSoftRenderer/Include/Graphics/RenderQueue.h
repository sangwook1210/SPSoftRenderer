#pragma once

#include <vector>
#include "Mesh.h"
#include "Math/Matrix.h"

struct DrawCommand
{
	Mesh* mesh = nullptr;
	// _todo Material Ãß°¡
	Matrix4x4 worldMatrix;
};

class RenderQueue
{
private:
	std::vector<DrawCommand> _commands;

public:
	void Submit(const DrawCommand& command);
	const std::vector<DrawCommand>& GetCommands() const;
	void Clear();
};