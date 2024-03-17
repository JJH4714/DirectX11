#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"
class NormalDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
private:
	shared_ptr<Shader> _shader;

	// Object
	shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Matrix _world = Matrix::Identity;	// 월드 행렬

	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Texture> _texture;

	// 빛을 오른쪽으로 가게 한다면 왼쪽부분만 하얗게 보이고(빛 받아서)
	// 안 보이는 쪽은 까맣게 됨
	Vec3 _lightDir = Vec3::Backward;
};

