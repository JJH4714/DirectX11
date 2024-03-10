#include "pch.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Animator.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : m_device(device), m_deviceContext(deviceContext)
{
}

void RenderManager::Init()
{
	m_pipeline = std::make_shared<Pipeline>(m_deviceContext);

	m_cameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(m_device, m_deviceContext);
	m_cameraBuffer->Create();
	m_transformBuffer = std::make_shared<ConstantBuffer<TransformData>>(m_device, m_deviceContext);
	m_transformBuffer->Create();
	m_animationBuffer = std::make_shared<ConstantBuffer<AnimationData>>(m_device, m_deviceContext);
	m_animationBuffer->Create();

	m_rasterizerState = std::make_shared<RasterizerState>(m_device);
	m_rasterizerState->Create();
	m_blendState = std::make_shared<BlendState>(m_device);
	m_blendState->Create();
	m_samplerState = std::make_shared<SamplerState>(m_device);
	m_samplerState->Create();
}

void RenderManager::Update(std::shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();

	_PushCameraData();
	_GatherRenderableObjects();
	_RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::_PushCameraData()
{
	m_cameraData.matView = Camera::m_matView;
	m_cameraData.matProjection = Camera::m_matProjection;
	m_cameraBuffer->CopyData(m_cameraData);
}

void RenderManager::_PushTransformData()
{
	m_transformBuffer->CopyData(m_transformData);
}

void RenderManager::_PushAnimationData()
{
	m_animationBuffer->CopyData(m_animationData);
}

void RenderManager::_GatherRenderableObjects()
{
	m_vecRenderObject.clear();

	auto& gameObjects = G_Game->GetSceneManager()->GetActiveScene()->GetGameObjects();
	for (const auto& e : gameObjects)
	{
		if (e == nullptr)
			continue;

		// 게임오브젝트에 메쉬렌더러가 있다면 그린다
		if (std::shared_ptr<MeshRenderer> meshRenderer = e->GetMeshRenderer())
			m_vecRenderObject.push_back(e);
	}
}

void RenderManager::_RenderObjects()
{
	for (const auto& e : m_vecRenderObject)
	{
		if (e == nullptr)
			continue;

		std::shared_ptr<MeshRenderer> meshRenderer = e->GetMeshRenderer();
		if (meshRenderer == nullptr)
			continue;

		std::shared_ptr<Transform> transform = e->GetTransform();
		if (transform == nullptr)
			continue;

		// SRT
		m_transformData.matWorld = transform->GetWorldMatrix();
		_PushTransformData();

		// Animation
		std::shared_ptr<Animator> animator = e->GetAnimator();
		if (animator)
		{
			const KeyFrame& keyFrame = animator->GetCurKeyFrame();
			m_animationData.spriteOffset = keyFrame.offset;
			m_animationData.spriteSize = keyFrame.size;
			m_animationData.textureSize = animator->GetCurAnimation()->GetTextureSize();
			m_animationData.useAnimation = 1.f;
			_PushAnimationData();

			m_pipeline->SetConstantBuffer(2, SS_VertexShader, m_animationBuffer);
			m_pipeline->SetTexture(0, SS_PixelShader, animator->GetCurAnimation()->GetTexture());
		}
		else
		{
			m_animationData.spriteOffset = { 0.f,0.f };
			m_animationData.spriteSize = { 0.f,0.f };
			m_animationData.textureSize = { 0.f,0.f };
			m_animationData.useAnimation = 0.f;

			_PushAnimationData();

			m_pipeline->SetConstantBuffer(2, SS_VertexShader, m_animationBuffer);
			m_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		}

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = m_rasterizerState;
		info.blendState = m_blendState;

		m_pipeline->UpdatePipeline(info);

		m_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		m_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());

		m_pipeline->SetConstantBuffer(0, SS_VertexShader, m_cameraBuffer);
		m_pipeline->SetConstantBuffer(1, SS_VertexShader, m_transformBuffer);

		m_pipeline->SetSamplerState(0, SS_PixelShader, m_samplerState);

		m_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
