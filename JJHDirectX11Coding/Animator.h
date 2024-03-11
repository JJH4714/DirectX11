#pragma once
#include "Component.h"
#include "Animation.h"


class Animator : public Component
{
public:
	Animator();
	virtual ~Animator();

	void Init();
	void Update();

	std::shared_ptr<Animation> GetCurAnimation();
	const KeyFrame& GetCurKeyFrame() const;

	void SetAnimation(std::shared_ptr<Animation> animation) { m_curAnim = animation;  }

private:
	float m_fSumTime = 0.f;
	int32 m_curKeyFrameIdx = 0;
	std::shared_ptr<Animation> m_curAnim;
};

