#include "pch.h"
#include "Animator.h"
#include "Game.h"
#include "TimeManager.h"

Animator::Animator() : Component(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{

}

void Animator::Update()
{
	std::shared_ptr<Animation> animation = GetCurAnimation();
	if (animation == nullptr)
		return;

	const KeyFrame& keyFrame = animation->GetKeyFrame(m_curKeyFrameIdx);
	
	float deltaTime = G_Game->GetTimeManager()->GetDeltaTime();
	m_fSumTime += deltaTime;
	if (m_fSumTime > keyFrame.time)
	{
		++m_curKeyFrameIdx;
		int32 iTotalCount = m_curAnim->GetKeyFrameCount();
		if (m_curKeyFrameIdx >= iTotalCount)
		{
			// 현재 애니메이션 인덱스 끝까지 도달
			if (animation->IsLoop())
				m_curKeyFrameIdx = 0;
			else
				m_curKeyFrameIdx = iTotalCount - 1;
		}

		m_fSumTime = 0.f;
	}
}

std::shared_ptr<Animation> Animator::GetCurAnimation()
{
	return m_curAnim;
}

const KeyFrame& Animator::GetCurKeyFrame() const
{
	return m_curAnim->GetKeyFrame(m_curKeyFrameIdx);
}
