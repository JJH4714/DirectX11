#pragma once

#include "ResourceBase.h"

class Mesh;
class Shader;
class Texture;
class Material;
class Animation;

class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device) : m_device(device) {}
	~ResourceManager() = default;

	void Init();

	template <typename T>
	std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
	{
		auto objectType = GetResourceType<T>();
		KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(objectType)];

		const auto& it = keyObjMap.find(key);
		if (it != keyObjMap.end())
			return std::static_pointer_cast<T>(it->second);

		std::shared_ptr<T> object = std::make_shared<T>();
		object->Load(path);
		keyObjMap[key] = object;

		return object;
	}

	template <typename T>
	bool Add(const std::wstring& key, std::shared_ptr<T> object)
	{
		ResourceType resourceType = GetResourceType<T>();
		KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(resourceType)];

		const auto& it = keyObjMap.find(key);
		if (it != keyObjMap.end())
			return false;

		keyObjMap.insert({ key, object });
		return true;
	}

	template <typename T>
	std::shared_ptr<T> Get(const std::wstring& key)
	{
		ResourceType resourceType = GetResourceType<T>();
		KeyObjMap& keyObjMap = m_resources[static_cast<uint8>(resourceType)];

		const auto& it = keyObjMap.find(key);
		if (it != keyObjMap.end())
			return std::static_pointer_cast<T>(it->second);

		return nullptr;
	}

	template <typename T>
	ResourceType GetResourceType()
	{
		if (std::is_same_v<T, Mesh>)
			return ResourceType::Mesh;

		if (std::is_same_v<T, Shader>)
			return ResourceType::Shader;

		if (std::is_same_v<T, Texture>)
			return ResourceType::Texture;

		if (std::is_same_v<T, Material>)
			return ResourceType::Material;

		if (std::is_same_v<T, Animation>)
			return ResourceType::Animation;

		assert(false);
		return ResourceType::None;
	}

private:
	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();

private:
	ComPtr<ID3D11Device> m_device;

	using KeyObjMap = map<std::wstring, std::shared_ptr<ResourceBase>>;

	std::array<KeyObjMap, RESOURCE_TYPE_COUNT> m_resources;
};

