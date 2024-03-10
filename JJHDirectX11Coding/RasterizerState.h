#pragma once
class RasterizerState
{
public:
	RasterizerState(ComPtr<ID3D11Device> device);
	~RasterizerState();

	ComPtr<ID3D11RasterizerState> GetComPtr() { return m_rasterizerState; }

	void Create();

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11RasterizerState> m_rasterizerState;
};