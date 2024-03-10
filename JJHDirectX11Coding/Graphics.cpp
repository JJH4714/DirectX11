#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND hwnd)
{
	m_hwnd = hwnd;
	m_width = GWinSizeX;
	m_height = GWinSizeY;

	_CreateDeviceAndSwapChain();
	_CreateRenderTargetView();
	_SetViewPort();
}

Graphics::~Graphics()
{
}

void Graphics::RenderBegin()
{
	// OM : Output Merge , ������ ���� ������ �ܰ�, ����Ÿ�� ����
	m_deviceContext->OMSetRenderTargets(1,/*�ĸ� ���� ����*/m_renderTargetView.GetAddressOf(), nullptr);

	// ����Ÿ�ٺ並 ���ϴ� �������� Ŭ�����Ŵ
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), m_clearColor);

	// ȭ�� ũ�� ����
	m_deviceContext->RSSetViewports(1, &m_viewPort);
}

void Graphics::RenderEnd()
{
	// �ĸ� ���ۿ� �� �׷�����, ���� ���ۿ� �����ؾ� ��(Ȥ�� ��ü�ε� �̰� �ɹ���(?))
	// �׸� �� ȭ�鿡 ����ϵ��� �������ִ� �� Present
	HRESULT hr = m_swapChain->Present(1, 0);
	CHECK_HR(hr);
}

void Graphics::_CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// ������ 800,600���� �ص״µ�, ���۵� �׿� �¾ƾ� �ϴϱ� �Ȱ��� ����
	desc.BufferDesc.Width = m_width;	// â ũ��
	desc.BufferDesc.Height = m_height;	// â ũ��
	// ȭ�� �ֻ��� ����
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;	// ��� ������ ���� ��ȭ...��Ƽ���ø� �� �� �Ÿ� 1
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// ���� ���ó : GPU ���� �� ���� ����� Ȯ������ �� �׷��ִ� ���ҷ� ����ϰڴ�
	desc.BufferCount = 1;	// ���� ����
	desc.OutputWindow = m_hwnd;	// ������ �ڵ� ��ȣ
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// 

	// ���ѻ� Device, DeviceContext, SwapChain ����
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,	// ����̹� Ÿ���� �ϵ����� -> ��ī
		nullptr,
		0,
		nullptr,
		0,	// FeatureLevels ������
		D3D11_SDK_VERSION,	//SDK Version
		&desc, // SWAP_CHAIN_DESC. ����̽��� �Բ� ����ü�� ������ �䱸
		m_swapChain.GetAddressOf(),// IDXGISwapChain** . ����� ����
		m_device.GetAddressOf(),
		nullptr,	// FeatureLevel�� �ش��ϴ� ���
		m_deviceContext.GetAddressOf()
	);

	CHECK_HR(hr);
}

void Graphics::_CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	// ����� �ؽ��ĸ� ����� ����ü���� ��� �ִ� �ĸ� ���� ������ �ؽ��� Ÿ������ ������
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK_HR(hr);

	hr = m_device->CreateRenderTargetView(
		// ���ڰ� ID3D11Resource �ε�, ID3D11Texture2D�� ���� ��ӹ���
		backBuffer.Get(),
		nullptr,
		m_renderTargetView.GetAddressOf()
	);
	CHECK_HR(hr);
}

void Graphics::_SetViewPort()
{
	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;
	//m_viewPort.Width = STATIC_CAST(float, m_width);
	m_viewPort.Width = static_cast<float>(m_width);
	//m_viewPort.Height = STATIC_CAST(float, m_height);
	m_viewPort.Height = static_cast<float>(m_height);
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;
}
