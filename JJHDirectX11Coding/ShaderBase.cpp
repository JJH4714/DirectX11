#include "pch.h"
#include "ShaderBase.h"

ShaderBase::ShaderBase(ComPtr<ID3D11Device> device) : m_device(device)
{
}

ShaderBase::~ShaderBase()
{
}


void ShaderBase::LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version)
{
	m_path = path;
	m_name = name;

	// ������ �÷���
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;	// ����� ���, ����ȭ �ǳʶ�

	// DX11 �⺻ ���� �Լ� �ƴϰ�, �ܺ� ���̺귯���� d3dcompiler.lib �� �ִ�
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str()/*�ٸ� ���ڵ�� �ٸ��� ��� LPCWSTR (WCHAR ������)�� ����*/,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		m_blob.GetAddressOf(),	// blob�� ������ ä���� ����
		nullptr
	);

	CHECK_HR(hr);
}

VertexShader::VertexShader(ComPtr<ID3D11Device> device)
	: ShaderBase::ShaderBase(device)
{
}

VertexShader::~VertexShader()
{

}

void VertexShader::Create(const std::wstring& path, const std::string& name, const std::string& version)
{
	LoadShaderFromFile(path, name, version);
	
	HRESULT hr = m_device->CreateVertexShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf()	// ���ؽ����̴��� ���⿡ �����
	);
	CHECK_HR(hr);
}

PixelShader::PixelShader(ComPtr <ID3D11Device> device)
	: ShaderBase::ShaderBase(device)
{
}

PixelShader::~PixelShader()
{
}

void PixelShader::Create(const std::wstring& path, const std::string& name, const std::string& version)
{
	LoadShaderFromFile(path, name, version);

	HRESULT hr = m_device->CreatePixelShader(
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize(),
		nullptr,
		m_pixelShader.GetAddressOf()
	);
	CHECK_HR(hr);
}
