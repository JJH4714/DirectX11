#pragma once

enum class ResourceType : uint8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<uint8>(ResourceType::End)
};

class ResourceBase : public std::enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type) : m_type(type) {};
	virtual ~ResourceBase() = default;

	ResourceType GetType() { return m_type; }

	void SetName(const std::wstring& name) { m_name = name; }
	const std::wstring& GetName() const { return m_name; }
	const uint32 GetID() const { return m_id; }

protected:
	virtual void Load(const std::wstring& path) {}
	virtual void Save(const std::wstring& path) {}

protected:
	ResourceType m_type = ResourceType::None;
	std::wstring m_name;

	std::wstring m_path;
	uint32 m_id = 0;
};

