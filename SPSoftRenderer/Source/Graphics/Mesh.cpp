
#include <Graphics/Mesh.h>

Mesh::Mesh(const std::vector<Vertex>& newVertices, const std::vector<uint32_t>& newIndices)
	: vertices(newVertices), indices(newIndices)
{
}

Mesh::Mesh(std::vector<Vertex>&& newVertices, std::vector<uint32_t>&& newIndices)
	: vertices(std::move(newVertices)), indices(std::move(newIndices))
{
}

const std::vector<Vertex>& Mesh::GetVertices() const
{
	return vertices;
}

const std::vector<uint32_t>& Mesh::GetIndices() const
{
	return indices;
}

Vertex& Mesh::GetVertex(size_t index)
{
	return vertices[index];
}

const Vertex& Mesh::GetVertex(size_t index) const
{
	return vertices[index];
}

void Mesh::SetVertices(const std::vector<Vertex>& newVertices)
{
	vertices = newVertices;
}

void Mesh::SetIndices(const std::vector<uint32_t>& newIndices)
{
	indices = newIndices;
}