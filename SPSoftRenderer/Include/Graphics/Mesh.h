#pragma once

#include <vector>
#include <Graphics/Vertex.h>

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

public:
	Mesh() = default;
	Mesh(const std::vector<Vertex>& newVertices, const std::vector<uint32_t>& newIndices);
	Mesh(std::vector<Vertex>&& newVertices, std::vector<uint32_t>&& newIndices);	// 이동 생성자

	const std::vector<Vertex>& GetVertices() const;
	const std::vector<uint32_t>& GetIndices() const;

	Vertex& GetVertex(size_t index);
	const Vertex& GetVertex(size_t index) const;

	void SetVertices(const std::vector<Vertex>& newVertices);
	void SetIndices(const std::vector<uint32_t>& newIndices);
};