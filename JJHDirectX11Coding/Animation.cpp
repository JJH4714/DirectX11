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

	return KeyFrame();
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
	tinyxml2::XMLDocument doc;

	// node를 Element라 함
	XMLElement* pRoot = doc.NewElement("Animation");
	if (pRoot == nullptr)
		return;

	// 부모노드
	doc.LinkEndChild(pRoot);	// 문서에 추가

	std::string strName;
	strName.assign(m_name.begin(), m_name.end());
	pRoot->SetAttribute("Name", strName.c_str());
	pRoot->SetAttribute("Loop", m_bLoop);
	pRoot->SetAttribute("TexturePath", "TODO");

	for (const auto& keyFrame : m_vecKeyFrame)
	{
		XMLElement* pEle = doc.NewElement("Keyframe");
		if (pEle == nullptr)
			continue;

		// 하부 노드 추가
		pRoot->LinkEndChild(pEle);

		pEle->SetAttribute("OffsetX", keyFrame.offset.x);
		pEle->SetAttribute("OffsetY", keyFrame.offset.y);
		pEle->SetAttribute("SizeX", keyFrame.size.x);
		pEle->SetAttribute("SizeY", keyFrame.size.y);
		pEle->SetAttribute("Time", keyFrame.time);
	}

	std::string strPath;
	strPath.assign(path.begin(), path.end());
	const XMLError result = doc.SaveFile(strPath.c_str());
	assert(result == XMLError::XML_SUCCESS);
}
