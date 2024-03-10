#pragma once

struct PipelineInfo
{
	std::shared_ptr<InputLayout> inputLayout;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;
	std::shared_ptr<RasterizerState> rasterizerState;
	std::shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	// ��ü���� ��� ������ �۾��� ���� ����������
	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer);

	template <typename T>
	void SetConstantBuffer(uint32 slot, uint32 scope, std::shared_ptr<ConstantBuffer<T>> buffer)
	{
		if(scope &  SS_VertexShader)
			m_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
		if(scope & SS_PixelShader)
			// ������۰� �� VS �ܰ迡���� �ϴ� �� �ƴϴ�. �Ʒ�ó�� PS�ܰ迡�� �ִ�
			m_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
	}

	void SetTexture(uint32 slot, uint32 scope, std::shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, std::shared_ptr<SamplerState> samplerState);

	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startVertexLocation, uint32 baseVertexLocation);

private:
	ComPtr<ID3D11DeviceContext> m_deviceContext;

};

