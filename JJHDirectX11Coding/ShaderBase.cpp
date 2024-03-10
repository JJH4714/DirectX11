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

	// 컴파일 플래그
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;	// 디버그 모드, 최적화 건너뜀

	// DX11 기본 제공 함수 아니고, 외부 라이브러리인 d3dcompiler.lib 에 있다
	HRESULT hr = ::D3DCompileFromFile(
		path.c_str()/*다른 인자들과 다르게 얘는 LPCWSTR (WCHAR 포인터)로 받음*/,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		m_blob.GetAddressOf(),	// blob에 정보를 채워줄 거임
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
		m_vertexShader.GetAddressOf()	// 버텍스셰이더가 여기에 저장됨
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
