#include "pch.h"
#include "Pipeline.h"

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext) : m_deviceContext(deviceContext)
{
}

Pipeline::~Pipeline()
{

}

void Pipeline::UpdatePipeline(PipelineInfo info)
{
	// IA - VS - RS - PS - OM

	m_deviceContext->IASetInputLayout(info.inputLayout->GetComPtr().Get());
	m_deviceContext->IASetPrimitiveTopology(info.topology);

	// VS
	if(info.vertexShader)
		m_deviceContext->VSSetShader(info.vertexShader->GetComPtr().Get(), nullptr, 0);

	// RS
	if(info.rasterizerState)
		m_deviceContext->RSSetState(info.rasterizerState->GetComPtr().Get());

	// PS
	if(info.pixelShader)
		m_deviceContext->PSSetShader(info.pixelShader->GetComPtr().Get(), nullptr, 0);

	// OM
	if(info.blendState)
		m_deviceContext->OMSetBlendState(info.blendState->GetComPtr().Get(), info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());
}

void Pipeline::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	uint32 stride = buffer->GetStride();
	uint32 offset = buffer->GetOffset();

	m_deviceContext->IASetVertexBuffers(0, 1/*버퍼 하나*/,buffer->GetComPtr().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
{
	m_deviceContext->IASetIndexBuffer(buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetTexture(uint32 slot, uint32 scope, std::shared_ptr<Texture> texture)
{
	if(scope & SS_VertexShader)
		m_deviceContext->VSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		m_deviceContext->PSSetShaderResources(slot, 1, texture->GetComPtr().GetAddressOf());
}

void Pipeline::SetSamplerState(uint32 slot, uint32 scope, std::shared_ptr<SamplerState> samplerState)
{
	if (scope & SS_VertexShader)
		m_deviceContext->VSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());

	if (scope & SS_PixelShader)
		m_deviceContext->PSSetSamplers(slot, 1, samplerState->GetComPtr().GetAddressOf());
}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	m_deviceContext->Draw(vertexCount, startVertexLocation);	// 정점만으로 드로우
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startVertexLocation, uint32 baseVertexLocation)
{
	m_deviceContext->DrawIndexed(indexCount, startVertexLocation, baseVertexLocation);	// 인덱스 버퍼까지 적용해 드로우
}
