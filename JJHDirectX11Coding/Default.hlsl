// ���̴� ������ �ֱ� ������ C++�� �ϳ� ���
struct VS_INPUT
{
    // float4 : �̰͵� ����ü��, float 4��
    // POSITION, COLOR : CreateInputLayout���� D3D11_INPUT_ELEMENT_DESC ���� ��
    // layout �̸�. ���߿� �� �� �𸣰ڴµ�... �ﰢ�� ���� �� "POSITION", "COLOR"�� �߾���
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;   //SV : System Value
    float2 uv : UV;
};

// �̰͵� �Լ��ε�, C++ó�� (��ȯŸ��) (�Լ��̸�)(����)�� ����
// �� ��ȯŸ���� ���� VS_OUTPUT , �Լ��̸� VS, �Լ� ���� ���� VS_INPUT �̴�
// ��� �����Լ� ���� ��

// ����� ������ ���������� �ٽ� 5�ܰ��
// IA - VS - RS - PS - OM

// Game.cpp - _CreateGeometry���� ���ؽ� ���� �����, ���ؽ� ���۱��� ����� GPU�� �����ߴ�
// �ٵ� �׷��� ������ �͸� �ָ�...���ӿ��� �����ӿ� ���� ����� �� �ȴ�.
// �׷��ٰ� �����ӿ� ���� ���� ������ �� �ٲ㼭 �ٽ� ���ؽ� ���۷� ����⿣ �δ��� ũ��,
// ������ �ʴ� ������ ������ �ΰ� ���ؽ� ���̴� �ʿ��� �����ӿ� ���� ����� �ٽ�����
cbuffer CameraData : register(b0)
{
    row_major matrix matView;
    row_major matrix matProjection;
}


cbuffer TransformData : register(b1)
{
    row_major matrix matWorld;
}

cbuffer AnimationData : register(b2)
{
    float2 spriteOffset;
    float2 spriteSize;
    float2 textureSize;
    float useAnimation;
}

// ���ؽ� ���̴�
// �����, ����Ʈ�� ������� �Լ� ���� �˰����� �̰͵� main�Լ��� ����
// �츮�� ���� ���ؽ����̴�.hlsl ���� �Ӽ� ���� ������ �̸� : main �ε�
// �츰 VS��� �̸����� ������ �̸��� �ٲ����� ( main �� �Ÿ� ����...)
VS_OUTPUT VS(VS_INPUT input)
{
    // input�� ������ ������ ������ �ʰ�, �߰�����(offset)�� ����
    // ���ؽ� ���̴��� ������ ���� ������ �����
    VS_OUTPUT output;

    // W - V - P
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.uv = input.uv;

    if(useAnimation == 1.f)
    {
        //@@ JJHCHECK
        output.uv *= spriteSize / textureSize;
        output.uv += spriteOffset / textureSize;
    }

    return output;
}


// RS (�����Ͷ�����) : ���ؽ� ���̴����� �������� ������ �ﰢ�� �����ͷ� �̾Ƴ���
// �ﰢ�� ����, ���� 3���� ������ �׳� ���̴ϱ�...�̰� �ﰢ������ ����


Texture2D texture0 : register(t0);  //t0 �������Ϳ� texture0�� ���
SamplerState sampler0 : register(s0);

// �ȼ� ���̴�. ���ؽ� ���̴����� ó���� �� RS(�����Ͷ�����)���� ó���ϰ�, �������� �Ѿ��
// ����� �ȼ� ���̴���...ȭ�鿡 ���� �� �ȼ����� �� ���
float4 PS(VS_OUTPUT input) : SV_Target  /*JJHCheck*/
{
    // �ؽ��� 0���� uv ��ǥ�� �ű⿡ �ش��ϴ� ������ ����
    float4 color = texture0.Sample(sampler0, input.uv);
    
    return color;
}