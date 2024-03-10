#pragma once

class Scene;
class SceneManager
{
public:
	SceneManager(std::shared_ptr<Graphics> graphics);

	void Init();
	void Update();

	void LoadScene(std::wstring sceneName);

	//void Render();

	std::shared_ptr<Scene> GetActiveScene() { return m_activeScene; }

private:
	std::shared_ptr<Scene> _LoadTestScene(); 

private:
	std::shared_ptr<Graphics> m_graphics;
	std::shared_ptr<Scene> m_activeScene;

};

