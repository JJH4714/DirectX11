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
	// OM : Output Merge , 렌더링 가장 마지막 단계, 렌더타겟 지정
	m_deviceContext->OMSetRenderTargets(1,/*후면 버퍼 개수*/m_renderTargetView.GetAddressOf(), nullptr);

	// 렌더타겟뷰를 원하는 색상으로 클리어시킴
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), m_clearColor);

	// 화면 크기 설정
	m_deviceContext->RSSetViewports(1, &m_viewPort);
}

void Graphics::RenderEnd()
{
	// 후면 버퍼에 다 그렸으면, 전면 버퍼에 복사해야 함(혹은 교체인데 이건 케바케(?))
	// 그린 걸 화면에 출력하도록 복사해주는 게 Present
	HRESULT hr = m_swapChain->Present(1, 0);
	CHECK_HR(hr);
}

void Graphics::_CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// 윈도우 800,600으로 해뒀는데, 버퍼도 그에 맞아야 하니까 똑같이 설정
	desc.BufferDesc.Width = m_width;	// 창 크기
	desc.BufferDesc.Height = m_height;	// 창 크기
	// 화면 주사율 관련
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;	// 계단 현상같은 문제 완화...멀티샘플링 안 쓸 거면 1
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 버퍼 사용처 : GPU 연산 후 최종 결과를 확보했을 때 그려주는 역할로 사용하겠다
	desc.BufferCount = 1;	// 버퍼 개수
	desc.OutputWindow = m_hwnd;	// 윈도우 핸들 번호
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// 

	// 삼총사 Device, DeviceContext, SwapChain 생성
	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,	// 드라이버 타입을 하드웨어로 -> 글카
		nullptr,
		0,
		nullptr,
		0,	// FeatureLevels 사이즈
		D3D11_SDK_VERSION,	//SDK Version
		&desc, // SWAP_CHAIN_DESC. 디바이스와 함께 스왑체인 정보도 요구
		m_swapChain.GetAddressOf(),// IDXGISwapChain** . 결과를 받음
		m_device.GetAddressOf(),
		nullptr,	// FeatureLevel에 해당하는 결과
		m_deviceContext.GetAddressOf()
	);

	CHECK_HR(hr);
}

void Graphics::_CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	// 백버퍼 텍스쳐를 만들어 스왑체인이 들고 있는 후면 버퍼 정보를 텍스쳐 타입으로 가져옴
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK_HR(hr);

	hr = m_device->CreateRenderTargetView(
		// 인자가 ID3D11Resource 인데, ID3D11Texture2D가 저걸 상속받음
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
