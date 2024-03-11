#pragma once

#include "Component.h"
#include "Material.h"
#include "Shader.h"

class Mesh;
class MeshRenderer : public Component
{
public:
	MeshRenderer(ComPtr<ID3D11Device> device);
	virtual ~MeshRenderer() = default;

	void SetMaterial(std::shared_ptr<Material> material) { m_material = material; }
	void SetShader(std::shared_ptr<Shader> shader) { m_material->SetShader(shader); }
	void SetMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
	void SetTexture(std::shared_ptr<Texture> texture) { m_material->SetTexture(texture); }

	auto GetMaterial() { return m_material; }
	auto GetVertexShader() { return m_material->GetShader()->GetVertexShader(); }
	auto GetInputLayout() { return m_material->GetShader()->GetInputLayout(); }
	auto GetPixelShader() { return m_material->GetShader()->GetPixelShader(); }

	auto GetMesh() { return m_mesh; }
	auto GetTexture() { return m_material->GetTexture(); }

private:
	ComPtr<ID3D11Device> m_device;

	friend class RenderManager;

	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_material;
};

