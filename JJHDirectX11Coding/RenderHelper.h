#pragma once

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
};


// CameraData, TransformData는 16바이트로 맞춰져 있어서 몰랐겠지만
// GPU 쪽으로 넘길 때 16으로 맞춰줘야 함
struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;

	float useAnimation;	// 애니메이션 사용할지. 쉐이더에 넘겨줄 때 boolean 이 없음;
	float fadding;	// 16 맞출 더미..
};