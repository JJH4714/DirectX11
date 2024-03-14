#pragma once
#include "Engine/00. Engine/IExecute.h"

// IExecute : 하나의 실행 단위
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