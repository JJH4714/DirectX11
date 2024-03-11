#pragma once
class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return m_device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_deviceContext; }


private:
	void _CreateDeviceAndSwapChain();
	void _CreateRenderTargetView();
	void _SetViewPort();

private:
	HWND m_hwnd;
	uint32 m_width = 0;
	uint32 m_height = 0;

	const float m_clearColor[4] = { 0.0f , 0.0f, 0.0f , 1.0f };

	// Device , Context, SwapChain
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<IDXGISwapChain> m_swapChain;

	// RenderTargetView
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// ViewPort
	D3D11_VIEWPORT m_viewPort;
};

