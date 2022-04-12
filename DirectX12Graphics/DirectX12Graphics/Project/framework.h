// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <string>

using namespace std;
#include <assert.h>

// DirectX 12
#include <wrl.h>
#include <shellapi.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <d3d12shader.h>
#include <dxgi1_4.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3dx12.h>
#include "DDSTextureLoader.h"

// DirectX 11
#include <d3d11on12.h>
#include <d2d1_3.h>
#include <dwrite_2.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#define _XM_NO_INTRINSICS_
typedef XMMATRIX matrix;
typedef XMFLOAT4X4 float4x4;
