#pragma once
class InputLayout
{
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();

	ComPtr<ID3D11InputLayout> GetComPtr() { return m_inputLayout; }

	void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& descs,
		ComPtr<ID3DBlob> blob);

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11InputLayout> m_inputLayout;	// 넘겨줄 버텍스에 대한 구조 정보
};

