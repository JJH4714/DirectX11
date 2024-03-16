#include "pch.h"
#include "07. HeightMapDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"06. Terrain.fx");

	// Texture
	_texture = RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Grass.jpg");
	_heightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Textures\\Heightmap.png");

	const int width = _heightMap->GetSize().x;
	const int height = _heightMap->GetSize().y;

	//@@ JJHCHECK
	const auto& info = _heightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();

	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, width, height);

	// CPU
	{
		// 1. ������ �ͷ����� ������ �� ������
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());

		for (int32 z = 0; z < height; ++z)
		{
			for (int32 x = 0; x < width; ++x)
			{
				// �ͷ��ο� ���� �ؽ����� ��ǥ�� ã�ư� ( 0 ~ width , 0 ~ height )
				int32 idx = width * z + x;

				// �ؽ����� �ȼ����� �ͷ����� ���̰��̹Ƿ� �� ������ �̿��� �� ���� ���
				uint8 vHeight = pixelBuffer[idx] / 255.f * 25.f;
				
				// ������ ���̸� ����� �ɷ� ���� ����
				v[idx].position.y = vHeight;


			}
		}
	}

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	//Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	Vec3 pos = _camera->GetTransform()->GetPosition();
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.5f, 0.f));
	_camera->GetTransform()->SetRotation(Vec3(25.f, 0.f, 0.f));
}

void HeightMapDemo::Update()
{
	_camera->Update();
}

void HeightMapDemo::Render()
{
	// W - V - P
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);	// ���̴����� matrix World
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);	// ���̴����� matrix View
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);	// ���̴����� matrix Projection
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());	//Texture2D Texture0

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _indexBuffer->GetOffset());

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
