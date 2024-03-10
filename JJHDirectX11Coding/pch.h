#pragma once

// 공용 기능들. 미리 컴파일할 헤더(PreCompileHeader)

#include "Types.h"
#include "Values.h"
#include "Struct.h"
#include "Macro.h"	// 내가 추가한 매크로 모음...

#include "corecrt_math_defines.h"

// STL
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <array>
#include <algorithm>
using namespace std;

// WinAPI
#include <windows.h>
#include <assert.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>

// 외부 라이브러리를 사용하려면 lib 파일과 그에 대한 헤더 파일 필요. 추가했다면 헤더 파일 경로 추가
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

// 또한 라이브러라 사용하겠다고 설정해야 함
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment (lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment (lib, "DirectXTex\\DirectXTex.lib")
#endif

#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexData.h"
#include "ShaderBase.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Pipeline.h"
#include "Transform.h"