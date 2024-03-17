#include "pch.h"
#include "Graphics.h"

void Graphics::Init(HWND hwnd)
{
	_hwnd = hwnd;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	CreateDepthStencilView();
	SetViewport();
}

void Graphics::RenderBegin()
{
	// 여태껏 OMSetRenderTargets의 마지막 인자를 nullptr로 했는데 저게 DSV 였음.
	// 최종 깊이값을 저장해줌
	//_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), (float*)(&GAME->GetGameDesc().clearColor));
	// 깊이 1, 스텐실 0 : 카메라 Near Far 를 0~1 로 둬서 그에 맞춤
	// 이전 프레임에서 DSV에 채운 값을 비워주지 않으면, 다음 프레임에도 그 정보가 저장되어 렌더링할 때 해당 깊이에 물체가 있다고 판단하여 그림을 그리지 않아버림
	// 따라서 매 프레임 DSV를 비워줘야 함
	// Depth 는 물체가 보여지는 깊이 정보
	// Stencil은 보이지 않는 부분에 대한 정보(가려지는 부분)
	_deviceContext->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}
void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = GAME->GetGameDesc().width;
		desc.BufferDesc.Height = GAME->GetGameDesc().height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Graphics::CreateDepthStencilView()
{
	{
		D3D11_TEXTURE2D_DESC desc = {};
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = static_cast<uint32>(GAME->GetGameDesc().width);
		desc.Height = static_cast<uint32>(GAME->GetGameDesc().height);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT hr = DEVICE->CreateTexture2D(&desc, nullptr, _depthStencilTexture.GetAddressOf());
		CHECK(hr);
	}

	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		HRESULT hr = DEVICE->CreateDepthStencilView(_depthStencilTexture.Get(), &desc, _depthStencilView.GetAddressOf());
		CHECK(hr);
	}
}

void Graphics::SetViewport()
{
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;
	_viewport.Width = static_cast<float>(GAME->GetGameDesc().width);
	_viewport.Height = static_cast<float>(GAME->GetGameDesc().height);
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
}