#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device) : m_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// ä��� ���
	// FILL_SOLID :
	// FILL_WIREFRAME : ���̾�������(��������)��. ���� �� ä��
	desc.FillMode = D3D11_FILL_SOLID;
	//desc.FillMode = D3D11_FILL_WIREFRAME;
	// �ø�. ���� ��ŵ�ϴ� �ǵ�, ��Ŭ���� �ø� ���� �װ� ����
	//CULL_FRONT : �ո��� �׸��� �ʰڴ�
	//CULL_BACK : �ĸ��� �׸��� �ʰڴ�
	desc.CullMode = D3D11_CULL_BACK;
	// ��/�� �� ��� �Ǻ��ұ�? desc.FrontCounterClockwise

	// ���� �ݽð��ΰ�? �´�/�ƴϴ� 
	// Clockwise : �ð���� , CounterClockwise : �ݽð����
	// false(�ð����) ���� : ī�޶� �� �� ���� ������ �ð�����̸�, �װ� ���̴�.
	// �ʱ⿡ �ε������۸� �ð�������� ������ ������ �̰�...
	desc.FrontCounterClockwise = false;
	HRESULT hr = m_device->CreateRasterizerState(&desc, m_rasterizerState.GetAddressOf());
	CHECK_HR(hr);
}