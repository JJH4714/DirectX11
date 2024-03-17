#pragma once
#include "Engine/00. Engine/IExecute.h"
#include "Engine/01. Graphics/Buffer/Geometry.h"

// Ambient : ȯ�汤/�ֺ���
// ���� �� ���� �ݻ�Ǵ� �� �ƴ϶� �ݻ� �� �ٸ� ��ü��� ���� �� �ݻ�Ǵ� Ư¡�� �̿��� ���� ���
// ���ǿ��� �� ���� �´�� ���� ���̴� �� �ƴ϶�, �ֺ��� ��� ���̴� �� �̷��� Ư¡

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

