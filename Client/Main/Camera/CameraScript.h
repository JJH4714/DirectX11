#pragma once
#include "Engine/04. Component/Monobehaviour.h"

class CameraScript : public Monobehaviour
{
public:
	CameraScript();
	virtual ~CameraScript();

	virtual void Start() override;
	virtual void Update() override;

	float _speed = 10.f;
};