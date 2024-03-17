#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"
class MeshDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
private:

	// Geometry, Vertex-Index Buffer 등을 MeshRenderer로 통합시킴

	// Object
	shared_ptr<GameObject> _obj;
	//Camera
	shared_ptr<GameObject> _camera;
};

