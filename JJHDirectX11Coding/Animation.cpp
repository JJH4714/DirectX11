#include "pch.h"
#include "Animation.h"

Animation::Animation() : ResourceBase(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

const KeyFrame& Animation::GetKeyFrame(int32 index)
{
	if (0 <= index && index < m_vecKeyFrame.size())
		return m_vecKeyFrame[index];
}

int32 Animation::GetKeyFrameCount()
{
	return static_cast<int32>(m_vecKeyFrame.size());
}

void Animation::AddKeyFrame(const KeyFrame& keyFrame)
{
	m_vecKeyFrame.push_back(keyFrame);
}

void Animation::Load(const std::wstring& path)
{
}

void Animation::Save(const std::wstring& path)
{
}
