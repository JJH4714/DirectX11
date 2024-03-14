#include "pch.h"
#include "Main.h"
#include "Engine/02. Manager/Game.h"
#include "Game/01. TriangleDemo.h"
#include "Game/02. QuadDemo.h"
#include "Game/03. ConstBufferDemo.h"
#include "Game/04. CameraDemo.h"
#include "Game/05. TextureDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	//desc.app = make_shared<TriangleDemo>();	// 내가 실행할 앱 ( 실행 단위 )
	//desc.app = make_shared<QuadDemo>();
	//desc.app = make_shared<ConstBufferDemo>();
	//desc.app = make_shared<CameraDemo>();
	desc.app = make_shared<TextureDemo>();

	GAME->Run(desc);

	return 0;
}