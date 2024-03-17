#include "pch.h"
#include "Main.h"
#include "Engine/02. Manager/Game.h"
#include "Game/01. TriangleDemo.h"
#include "Game/02. QuadDemo.h"
#include "Game/03. ConstBufferDemo.h"
#include "Game/04. CameraDemo.h"
#include "Game/05. TextureDemo.h"
#include "Game/06. SamplerDemo.h"
#include "Game/07. HeightMapDemo.h"
#include "Game/08. NormalDemo.h"
#include "Game/09. MeshDemo.h"
#include "Game/10. GlobalTestDemo.h"
#include "Game/11. DepthStencilDemo.h"
#include "Game/12. AmbientDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.f, 0.f, 0.f);
	//desc.app = make_shared<TriangleDemo>();	// 내가 실행할 앱 ( 실행 단위 )
	//desc.app = make_shared<QuadDemo>();
	//desc.app = make_shared<ConstBufferDemo>();
	//desc.app = make_shared<CameraDemo>();
	//desc.app = make_shared<TextureDemo>();
	//desc.app = make_shared<SamplerDemo>();
	//desc.app = make_shared<HeightMapDemo>();
	//desc.app = make_shared<NormalDemo>();
	//desc.app = make_shared<MeshDemo>();
	//desc.app = make_shared<GlobalTestDemo>();
	//desc.app = make_shared<DepthStencilDemo>();
	desc.app = make_shared<AmbientDemo>();

	GAME->Run(desc);

	return 0;
}