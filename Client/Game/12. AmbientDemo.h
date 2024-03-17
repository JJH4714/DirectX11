#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"

// Ambient : 환경광/주변광
// 빛은 한 번만 반사되는 게 아니라 반사 후 다른 물체들과 여러 번 반사되는 특징을 이용한 조명 기법
// 현실에서 꼭 빛에 맞닿는 곳만 보이는 게 아니라, 주변도 밝게 보이는 게 이러한 특징

class AmbientDemo : public IExecute
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

