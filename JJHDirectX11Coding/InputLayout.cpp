#include "pch.h"
#include "InputLayout.h"

InputLayout::InputLayout(ComPtr<ID3D11Device> device) : m_device(device)
{
}

InputLayout::~InputLayout()
{
}

void InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob)
{
	const int32 count = static_cast<int32>(descs.size());
	HRESULT hr = m_device->CreateInputLayout(
		descs.data(),
		count/*InputLayout�� ���� ������ ��*/,
		blob->GetBufferPointer(),	// ���ؽ� ���̴��� ��� ����
		blob->GetBufferSize(),		// ���ؽ� ���̴��� ��� ������
		m_inputLayout.GetAddressOf()	// ID3D11InputLayout �� �����
	);
	ASSERT(hr);
}
