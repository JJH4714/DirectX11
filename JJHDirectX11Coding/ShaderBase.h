#pragma once

// 셰이더 사용처 지정
enum ShaderScope
{
	SS_NONE = 1 << 0,
	SS_VertexShader = 1 << 1,
	SS_PixelShader = 1 << 2,
	SS_Both = SS_VertexShader | SS_PixelShader,
};

class ShaderBase
{
public:
	ShaderBase(ComPtr<ID3D11Device> device);
	virtual ~ShaderBase();	// 상속 받을 거 대비

	ComPtr<ID3DBlob> GetBlob() { return m_blob; }

	virtual void Create(const std::wstring& path, const std::string& name, const std::string& version) abstract;

protected:
	void LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version);

protected:
	std::wstring m_path;
	string m_name;
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3DBlob> m_blob;
};

class VertexShader : public ShaderBase
{
public:
	VertexShader(ComPtr <ID3D11Device> device);
	~VertexShader();

	ComPtr<ID3D11VertexShader> GetComPtr() { return m_vertexShader; }

	virtual void Create(const std::wstring& path, const std::string& name, const std::string& version) override;

protected:
	ComPtr<ID3D11VertexShader> m_vertexShader;
};

class PixelShader : public ShaderBase
{
public:
	PixelShader(ComPtr <ID3D11Device> device);
	~PixelShader();

	ComPtr<ID3D11PixelShader> GetComPtr() { return m_pixelShader; }

	virtual void Create(const std::wstring& path, const std::string& name, const std::string& version) override;

protected:
	ComPtr<ID3D11PixelShader> m_pixelShader;
};