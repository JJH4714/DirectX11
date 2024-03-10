#pragma once
#include "RenderHelper.h"

class RenderManager
{
public:
	RenderManager(ComPtr<ID3D11Device> device,ComPtr<ID3D11DeviceContext> deviceContext);
	
	void Init();
	void Update(std::shared_ptr<Graphics> graphics);

private:
	void _PushCameraData();
	void _PushTransformData();
	void _PushAnimationData();

	void _GatherRenderableObjects();
	void _RenderObjects();

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	std::shared_ptr<Pipeline> m_pipeline;

	// Camera
	CameraData m_cameraData;
	std::shared_ptr<ConstantBuffer<CameraData>> m_cameraBuffer;
	// SRT
	TransformData m_transformData;
	std::shared_ptr<ConstantBuffer<TransformData>> m_transformBuffer;
	// Animation
	AnimationData m_animationData;
	std::shared_ptr<ConstantBuffer<AnimationData>> m_animationBuffer;

	std::shared_ptr<RasterizerState> m_rasterizerState;
	std::shared_ptr<SamplerState> m_samplerState;
	std::shared_ptr<BlendState> m_blendState;

	// 그려야 할 물체들
	std::vector<std::shared_ptr<GameObject>> m_vecRenderObject;
};