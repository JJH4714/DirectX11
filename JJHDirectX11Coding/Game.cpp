#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

std::unique_ptr<Game> G_Game = std::make_unique<Game>();
Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	m_hwnd = hwnd;

	m_graphics = std::make_shared<Graphics>(hwnd);

	m_sceneManager = std::make_shared<SceneManager>(m_graphics);
	m_sceneManager->Init();
	m_inputManager = std::make_shared<InputManager>();
	m_inputManager->Init(hwnd);
	m_timeManager = std::make_shared<TimeManager>();
	m_timeManager->Init();
	m_resourceManager = std::make_shared<ResourceManager>(m_graphics->GetDevice());
	m_resourceManager->Init();
	m_renderManager = std::make_shared<RenderManager>(m_graphics->GetDevice(), m_graphics->GetDeviceContext());
	m_renderManager->Init();

	m_sceneManager->LoadScene(L"Test");
}

void Game::Update()
{
	m_sceneManager->Update();
	m_inputManager->Update();
	m_timeManager->Update();
}

void Game::Render()
{
	m_renderManager->Update(m_graphics);
}