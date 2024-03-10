struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;   //SV : System Value
    float4 color : COLOR;
};

cbuffer TransformData : register(b0)
{
    //@@JJHCHECK row_major : 
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProjection;
    
    //float4 offset;
}

// ���ؽ� ���̴�
// �����, ����Ʈ�� ������� �Լ� ���� �˰����� �̰͵� main�Լ��� ����
// �츮�� ���� ���ؽ����̴�.hlsl ���� �Ӽ� ���� ������ �̸� : main �ε�
// �츰 VS��� �̸����� ������ �̸��� �ٲ����� ( main �� �Ÿ� ����...)
VS_OUTPUT VS(VS_INPUT input)
{
    // ���ؽ� ���̴��� ������ ���� ������ �����
    VS_OUTPUT output;

    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.color = input.color;
    
    // input�� ������ ������ ������ �ʰ�, �߰�����(offset)�� ����
    //output.position = input.position + offset;
    ////output.color = input.color;
    //output.uv = input.uv;

    return output;
}


// RS (�����Ͷ�����) : ���ؽ� ���̴����� �������� ������ �ﰢ�� �����ͷ� �̾Ƴ���
// �ﰢ�� ����, ���� 3���� ������ �׳� ���̴ϱ�...�̰� �ﰢ������ ����


Texture2D texture0 : register(t0);  //t0 �������Ϳ� texture0�� ���
SamplerState sampler0 : register(s0);

// �ȼ� ���̴�. ���ؽ� ���̴����� ó���� �� RS(�����Ͷ�����)���� ó���ϰ�, �������� �Ѿ��
// ����� �ȼ� ���̴���...ȭ�鿡 ���� �� �ȼ����� �� ���
float4 PS(VS_OUTPUT input) : SV_Target
{
    //return input.color;

    // �ؽ��� 0���� uv ��ǥ�� �ű⿡ �ش��ϴ� ������ ����
    //float4 color = texture0.Sample(sampler0, input.uv);
    float4 color = input.color;
    
    return color;
}


// ����Ʈ�� �ִ� �Լ�
//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}