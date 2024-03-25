#pragma once

#include "Component.h"

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer() = default;

	virtual void Update() override;

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }

	// Legacy
	void SetShader(shared_ptr<Shader> shader) { }
	void SetTexture(shared_ptr<Texture> texture) { }

private:
	shared_ptr<Mesh> _mesh;
	// Shader, Texture 는 Material로 통합
	shared_ptr<Material> _material;
	//shared_ptr<Shader> _shader;
	//shared_ptr<Texture> _texture;
};

