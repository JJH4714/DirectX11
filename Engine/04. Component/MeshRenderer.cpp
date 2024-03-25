#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{
}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());
//
//	// 뷰, 프로젝션 : 물체마다 가지기보단 공용이므로 렌더매니저에서 처리...
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc(world));
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _mesh->GetIndexBuffer()->GetOffset());
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("DiffuseMap")->SetResource(_texture->GetComPtr().Get());
//
//	// 뷰, 프로젝션 : 물체마다 가지기보단 공용이므로 렌더매니저에서 처리...
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc(world));
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _mesh->GetIndexBuffer()->GetOffset());
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	_material->Update();

	auto shader = _material->GetShader();
	if (shader == nullptr)
		return;

	// 뷰, 프로젝션 : 물체마다 가지기보단 공용이므로 렌더매니저에서 처리...

	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc(world));

	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();

	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _mesh->GetIndexBuffer()->GetOffset());

	shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}