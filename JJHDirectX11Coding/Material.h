#pragma once
#include "ResourceBase.h"

class Shader;
class Texture;

class Material : public ResourceBase
{
public:
	Material();
	virtual ~Material();

	auto GetShader() { return m_shader; }
	auto GetTexture() { return m_texture; }

	void SetShader(std::shared_ptr<Shader> shader) { m_shader = shader; }
	void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }

private:
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;
};

