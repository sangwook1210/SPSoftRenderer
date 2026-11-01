#include "Graphics/RenderQueue.h"

void RenderQueue::Submit(const DrawCommand& command)
{
    _commands.push_back(command);
}

const std::vector<DrawCommand>& RenderQueue::GetCommands() const
{
    return _commands;
}

void RenderQueue::Clear()
{
    _commands.clear();
}