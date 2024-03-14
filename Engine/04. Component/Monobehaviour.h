#pragma once
#include "Component.h"
class Monobehaviour : public Component
{
public:
	Monobehaviour();
	~Monobehaviour();

	virtual void Awake() override;
	virtual void Update() override;

};

