#pragma once

#include "ResourceBase.h"

class Shader : public ResourceBase
{
public:
	Shader();
	virtual ~Shader();

public:
	std::shared_ptr<InputLayout> GetInputLayout() { return m_inputLayout; }
	std::shared_ptr<VertexShader> GetVertexShader() { return m_vertexShader; }
	std::shared_ptr<PixelShader> GetPixelShader() { return m_pixelShader; }

private:
	friend class ResourceManager;
	std::shared_ptr<InputLayout> m_inputLayout;
	std::shared_ptr<VertexShader> m_vertexShader;
	std::shared_ptr<PixelShader> m_pixelShader;
};

