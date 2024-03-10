#pragma once
class BlendState
{
public:
	BlendState(ComPtr<ID3D11Device> device);
	~BlendState();
	
	const float* GetBlendFactor() { return &m_fBlendFactor; }
	uint32 GetSampleMask() { return m_sampleMask; }
	ComPtr<ID3D11BlendState> GetComPtr() { return m_blendState; }

	void Create(D3D11_RENDER_TARGET_BLEND_DESC blendDesc =
		{
			true,
			D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP_ADD,
			D3D11_BLEND_ONE,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_OP_ADD,
			D3D11_COLOR_WRITE_ENABLE_ALL
		},
		float fFactor = 0.0f);

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11BlendState> m_blendState;
	float m_fBlendFactor = 0.0f;
	uint32 m_sampleMask = 0xFFFFFFFF;
};