#pragma once

template <typename T>
class Geometry
{
public:
	Geometry() = default;
	~Geometry() = default;

	uint32 GetVertexCount() { return static_cast<uint32>(m_vecVertices.size()); }
	void* GetVertexData() { return m_vecVertices.data(); }
	const std::vector<T>& GetVertices() { return m_vecVertices; }

	uint32 GetIndexCount() { return static_cast<uint32>(m_vecIndices.size()); }
	void* GetIndexData() { return m_vecIndices.data(); }
	const std::vector<uint32>& GetIndices() { return m_vecIndices; }

	void AddVertex(const T& vertex) { m_vecVertices.push_back(vertex); }
	void AddVertices(const std::vector<T>& vecVertices) { 
		m_vecVertices.insert(m_vecVertices.end(), vecVertices.begin(), vecVertices.end()); 
	}
	void SetVertices(const std::vector<T>& vecVertices) { m_vecVertices = vecVertices; }

	void AddIndex(uint32 index) { m_vecIndices.push_back(index); }
	void AddIndicies(const std::vector<uint32>& vecIndices) {
		m_vecIndices.insert(m_vecIndices.end(), vecIndices.begin(), vecIndices.end());
	}
	void SetIndicies(const std::vector<uint32>& vecIndices) { m_vecIndices = vecIndices; }

private:
	std::vector<T> m_vecVertices;	// 정점 정보
	std::vector<uint32> m_vecIndices;	// 버텍스의 인덱스
};