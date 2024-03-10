#pragma once
#include "ResourceBase.h"

struct KeyFrame
{
	Vec2 offset = Vec2::Zero;	// 좌표
	Vec2 size = Vec2::Zero;	// 잘라낼 크기
	float time = 0.0f;	// 보여줄 시간
};

class Texture;

class Animation : public ResourceBase
{
public:
	Animation();
	virtual ~Animation();

	void SetLoop(bool b) { m_bLoop = b; }
	bool IsLoop() { return m_bLoop; }

	void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
	std::shared_ptr<Texture> GetTexture() { return m_texture; }
	Vec2 GetTextureSize() { return m_texture->GetSize(); }
	
	const KeyFrame& GetKeyFrame(int32 index);
	int32 GetKeyFrameCount();
	void AddKeyFrame(const KeyFrame& keyFrame);

protected:
	virtual void Load(const std::wstring& path) override;
	virtual void Save(const std::wstring& path) override;

private:
	bool m_bLoop = false;	// 애니메이션 반복재생
	std::shared_ptr<Texture> m_texture;	// 그릴 텍스쳐
	std::vector<KeyFrame> m_vecKeyFrame;	// 프레임 데이터 리스트
};

