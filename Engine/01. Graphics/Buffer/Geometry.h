#pragma once

template<typename T>
class Geometry
{
public:
	Geometry() {} 
	~Geometry() {}

	uint32 GetVertexCount() { return static_cast<uint32>(m_vecVertex.size()); }
	void* GetVertexData() { return m_vecVertex.data(); }
	const vector<T>& GetVertices() { return m_vecVertex; }

	uint32 GetIndexCount() { return static_cast<uint32>(m_vecIndex.size());  }
	void* GetIndexData() { return m_vecIndex.data(); }
	const vector<uint32>& GetIndices() { return m_vecIndex; }

	void AddVertex(const T& vertex) { m_vecVertex.push_back(vertex); }
	void AddVertices(const vector<T>& vertices) { m_vecVertex.insert(m_vecVertex.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const vector<T>& vertices) { m_vecVertex = vertices; }

	void AddIndex(uint32 index) { m_vecIndex.push_back(index); }
	void AddIndices(const vector<uint32>& indices) { m_vecIndex.insert(m_vecIndex.end(), indices.begin(), indices.end()); }
	void SetIndices(const vector<uint32>& indices) { m_vecIndex = indices; }

private:
	vector<T> m_vecVertex;
	vector<uint32> m_vecIndex;
};
