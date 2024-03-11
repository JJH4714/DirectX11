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
	tinyxml2::XMLDocument doc;

	std::string strPath;
	strPath.assign(path.begin(), path.end());
	XMLError error = doc.LoadFile(strPath.c_str());
	assert(error == XMLError::XML_SUCCESS);

	XmlElement* pRoot = doc.FirstChildElement();
	if (pRoot == nullptr)
		return;

	std::wstring wstrName;
	std::string strName = pRoot->Attribute("Name");
	wstrName.assign(strName.begin(), strName.end());
	m_name = wstrName;

	m_bLoop = pRoot->BoolAttribute("Loop");
	m_path = path;

	for (XmlElement* pNode = pRoot->FirstChildElement(); pNode != nullptr; pNode = pNode->NextSiblingElement())
	{
		KeyFrame keyFrame;

		keyFrame.offset.x = pNode->FloatAttribute("OffsetX");
		keyFrame.offset.y = pNode->FloatAttribute("OffsetY");
		keyFrame.size.x = pNode->FloatAttribute("SizeX");
		keyFrame.size.x = pNode->FloatAttribute("SizeY");
		keyFrame.time = pNode->FloatAttribute("Time");

		AddKeyFrame(keyFrame);
	}
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
