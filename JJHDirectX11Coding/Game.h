#pragma once
//#include "GameObject.h"

class SceneManager;
class InputManager;
class TimeManager;
class ResourceManager;
class RenderManager;

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

	std::shared_ptr<SceneManager> GetSceneManager() { return m_sceneManager; }
	std::shared_ptr<InputManager> GetInputManager() { return m_inputManager; }
	std::shared_ptr<TimeManager> GetTimeManager() { return m_timeManager; }
	std::shared_ptr<ResourceManager> GetResourceManager() { return m_resourceManager; }
	std::shared_ptr<RenderManager> GetRenderManager() { return m_renderManager; }

private:
	HWND m_hwnd = 0;

	std::shared_ptr<Graphics> m_graphics;

	std::shared_ptr<SceneManager> m_sceneManager;
	std::shared_ptr<InputManager> m_inputManager;
	std::shared_ptr<TimeManager> m_timeManager;
	std::shared_ptr<ResourceManager> m_resourceManager;
	std::shared_ptr<RenderManager> m_renderManager;
};

extern std::unique_ptr<Game> G_Game;	//Global