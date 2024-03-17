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
	Matrix _world = Matrix::Identity;	// ���� ���

	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Texture> _texture;

	// ���� ���������� ���� �Ѵٸ� ���ʺκи� �Ͼ�� ���̰�(�� �޾Ƽ�)
	// �� ���̴� ���� ��İ� ��
	Vec3 _lightDir = Vec3::Backward;
};

