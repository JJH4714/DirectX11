#pragma once
#include "Engine/00. Engine/IExecute.h"

// IExecute : �ϳ��� ���� ����
class TriangleDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<Shader> _shader;
	vector<VertexData> _vertices;
	shared_ptr<VertexBuffer> _buffer;
};