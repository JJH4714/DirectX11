#pragma once

#include "Component.h"

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer() = default;

	virtual void Update() override;

	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }

	auto getShder() { return _shader; }
	auto getMesh() { return _mesh; }
	auto getTexture() { return _texture; }

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Mesh> _mesh;
	shared_ptr<Texture> _texture;
};

