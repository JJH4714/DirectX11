#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"
class HeightMapDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
private:
	shared_ptr<Shader> _shader;

	// Object
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Matrix _world = Matrix::Identity;	// 월드 행렬

	//Camera
	shared_ptr<GameObject> _camera;

	// 터레인에 깔 텍스쳐
	shared_ptr<Texture> _texture;
	// HeightMap 높이 지정하기 위한 텍스쳐
	shared_ptr<Texture> _heightMap;
};

