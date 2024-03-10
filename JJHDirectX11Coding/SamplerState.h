#pragma once
class SamplerState
{
public:
	SamplerState(ComPtr<ID3D11Device> device);
	~SamplerState();

	ComPtr<ID3D11SamplerState> GetComPtr() { return m_samplerState; }

	void Create();

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11SamplerState> m_samplerState;
};