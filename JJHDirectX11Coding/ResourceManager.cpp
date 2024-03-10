#include "pch.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Animation.h"

void ResourceManager::Init()
{
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = std::make_shared<Texture>(m_device);
		texture->SetName(L"Test1");
		texture->Create(L"Test1.png");
		Add(texture->GetName(), texture);
	}
	{
		auto texture = std::make_shared<Texture>(m_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMesh()
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(m_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	auto vertexShader = std::make_shared<VertexShader>(m_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	auto inputLayout = std::make_shared<InputLayout>(m_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

	auto pixelShader = std::make_shared<PixelShader>(m_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	// Shader
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->SetName(L"Default");
	shader->m_vertexShader = vertexShader;
	shader->m_inputLayout = inputLayout;
	shader->m_pixelShader = pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	auto material = std::make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"Test1"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	auto animation = std::make_shared<Animation>();
	animation->SetName(L"SnakeAnim");
	animation->SetTexture(Get<Texture>(L"Snake"));
	animation->SetLoop(true);

	// 이미지 좌표마다 잘라주고 있음
	animation->AddKeyFrame(KeyFrame(Vec2(0.f, 0.f), Vec2(100.f, 100.f), 0.1f));
	animation->AddKeyFrame(KeyFrame(Vec2(100.f, 0.f), Vec2(100.f, 100.f), 0.1f));
	animation->AddKeyFrame(KeyFrame(Vec2(200.f, 0.f), Vec2(100.f, 100.f), 0.1f));
	animation->AddKeyFrame(KeyFrame(Vec2(300.f, 0.f), Vec2(100.f, 100.f), 0.1f));

	Add(animation->GetName(), animation);
}
