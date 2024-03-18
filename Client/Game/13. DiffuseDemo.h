#pragma once
#include "Engine/00. Engine/IExecute.h"

// Diffuse : 분산광, 난반사광
// 표면으로 들어온 빛이 반사될 때, 표면의 각도에 따라 빛이 퍼지는 특징을 이용한 기법
// 광원벡터랑 표면의 노멀벡터 이용하던 그거...

class DiffuseDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
private:
	// Object
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;
	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Shader> _shader;
};

