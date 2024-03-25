#ifndef _LIHGT_FX_
#define _LIHGT_FX_

//#include "00. Global.fx"
#include "Common/00. Global.fx"

// 이전에 개별적으로 나눈 조명들 합침
struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction; // 방향
    float fadding; // 16바이트 맞추기
};


struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};


cbuffer LightBuffer
{
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};

Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;



// 조명 연산으로 쓸 함수
float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor;
    float4 diffuseColor;
    float4 specularColor;
    float4 emissiveColor;
    
    // Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    // Diffuse
    {
        float4 color = DiffuseMap.Sample(LinearSampler, uv);
        float4 value = dot(normalize(-GlobalLight.direction), normalize(normal));
        diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
    }
    // Specular
    {
        float3 R = reflect(GlobalLight.direction, normal);
    
        R = normalize(R);
        
        float3 cameraPosition = CameraPosition();
        float3 E = cameraPosition - worldPosition;
        E = normalize(E);
    
        float value = dot(R, E);
        value = saturate(value); // saturate : clamp( 0 ~ 1 )
        float specular = pow(value, 10);
    
        specularColor = GlobalLight.specular * Material.specular * specular;
    }
    // Emissive
    {
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(E, normal));
        float emissive = 1.f - value;
    
        emissive = smoothstep(0.f, 1.f, emissive);
        emissive = pow(emissive, 5);
        emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
}

#endif

