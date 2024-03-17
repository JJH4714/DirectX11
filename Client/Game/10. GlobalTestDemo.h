#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"
class GlobalTestDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
private:
	// Object
	shared_ptr<GameObject> _obj;
	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Shader> _shader;
};
