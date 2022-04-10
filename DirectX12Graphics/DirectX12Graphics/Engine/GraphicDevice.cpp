#include "framework.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(GraphicDevice)

GraphicDevice::GraphicDevice()
{
	clear();
}

GraphicDevice::~GraphicDevice()
{
	clear();
}

HRESULT GraphicDevice::init(
	const HWND hWnd, 
	const HANDLE hHandle,
	const WindowType winType,
	const unsigned int width, 
	const unsigned int height)
{
	createGraphicDevice(width, height);
	createCommandList();
	createSwapChain(hWnd, winType, width, height);
	createRtvAndDsvDescriptorHeap();
	createFenceObject();
	createRenderTargetAndDepthStencilBuffer(width, height);

	return NO_ERROR;
}

void GraphicDevice::clear()
{
	ZeroMemory(&viewport_, sizeof(D3D12_VIEWPORT));
	ZeroMemory(&scissorRect_, sizeof(D3D12_RECT));

	graphicDeviceName_.clear();
	commandAllocators_.clear();
	commandLists_.clear();
	swapChainBuffers_.clear();
}

HRESULT GraphicDevice::waitForGpuComplete()
{
	curFence_++;

	if (FAILED(commandQueue_->Signal(fence_, curFence_)))
	{
		assert("CommandQueue Signal Failed");
		return E_FAIL;
	}

	/*__________________________________________________________________________________________________________
	[ Wait until the GPU has completed commands up to this fence point ]
	- GPU가 이 Fence 지점까지의 명령들을 완료할 때 까지 기다린다.
	____________________________________________________________________________________________________________*/
	if (fence_->GetCompletedValue() < curFence_)
	{
		HANDLE eventHandle = CreateEventEx(NULL,
			FALSE, // Event Name
			FALSE, // Flags 
			EVENT_ALL_ACCESS);

		// GPU가 현재 Fence 지점에 도달했으면 이벤트를 발동한다.
		if (FAILED(fence_->SetEventOnCompletion(curFence_, eventHandle)))
		{
			assert("Fence SetEventOnCompletion Failed");
			return E_FAIL;
		}

		// GPU가 현재 울타리 지점에 도달했음을 뜻하는 이벤트를 기다린다.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}

	return S_OK;

	return S_OK;
}

HRESULT GraphicDevice::createGraphicDevice(const unsigned int width, const unsigned int height)
{
#ifdef _DEBUG
	ID3D12Debug* debugController { nullptr };
	D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void**)&debugController);
	debugController->EnableDebugLayer();
#endif
	// 팩토리
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory_))))
	{
		assert("Create Factory failed!");
		return E_FAIL;
	}

	// 그래픽 디바이스
	IDXGIAdapter1* hardwareAdapter;
	findHardwareAdapter(factory_, &hardwareAdapter);

	if (FAILED(D3D12CreateDevice(hardwareAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&graphicDevice_))))
	{
		IDXGIAdapter* warpAdapter;
		factory_->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
		D3D12CreateDevice(warpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&graphicDevice_));
	}

	graphicDevice_->SetName(L"GraphicDevice");

	rtvDescriptorSize_ = graphicDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	dsvDescriptorSize_ = graphicDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	etcDescriptorSize_ = graphicDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

#ifdef _DEBUG
	logAdapters();
	safeRelease(debugController);
#endif

	return NO_ERROR;
}

void GraphicDevice::findHardwareAdapter(IDXGIFactory2* factory, IDXGIAdapter1** out)
{
	// 가장 큰 비디오카드 메모리를 찾는다.
	UINT64	maxVideoMemory = 0;
	int	idx = 0;

	IDXGIAdapter1* adapter;
	for (int i = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(i, &adapter); ++i)
	{
		DXGI_ADAPTER_DESC1 adapterDesc;
		adapter->GetDesc1(&adapterDesc);

		if (maxVideoMemory <= adapterDesc.DedicatedVideoMemory)
		{
			maxVideoMemory = adapterDesc.DedicatedVideoMemory;
			graphicDeviceName_ = adapterDesc.Description;
			idx = i;
		}
	}

	// 2. Adapter 반환.
	factory->EnumAdapters1(idx, &adapter);
	*out = nullptr;
	*out = adapter;
}

HRESULT GraphicDevice::createCommandList()
{
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
	commandQueueDesc.Type	= D3D12_COMMAND_LIST_TYPE_DIRECT;
	commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	if (FAILED(graphicDevice_->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue_))))
	{
		assert("Create CommandQueue Failed");
		return E_FAIL;
	}
	commandQueue_->SetName(L"CommandQueue");

	/*__________________________________________________________________________________________________________
	[ CommandList ]
	____________________________________________________________________________________________________________*/
	for (int i = 0; i < (int)CmdList::End; ++i)
	{
		ID3D12CommandAllocator* commandAllocator{ nullptr };
		ID3D12GraphicsCommandList* commandList{ nullptr };

		if (FAILED(graphicDevice_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator))))
		{
			assert("Create CommandAllocator Failed");
			return E_FAIL;
		}

		if (FAILED(graphicDevice_->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			commandAllocator,	// Associated command allocator
			nullptr,			// Initial PipelineStateObject
			IID_PPV_ARGS(&commandList))))
		{
			assert("Create CommandList Failed");
			return E_FAIL;
		}

		commandList->Close();

		commandAllocators_.emplace_back(commandAllocator);
		commandLists_.emplace_back(commandList);
	}

	commandAllocators_[(size_t)CmdList::Main]->SetName(L"CommandAllocator Main");
	commandAllocators_[(size_t)CmdList::Resource]->SetName(L"CommandAllocator Resource");

	commandLists_[(size_t)CmdList::Main]->SetName(L"CommandList Main");
	commandLists_[(size_t)CmdList::Resource]->SetName(L"CommandList Resource");

	return NO_ERROR;
}

HRESULT GraphicDevice::createSwapChain(
	const HWND hWnd, 
	const WindowType winType, 
	const unsigned int width, 
	const unsigned int height)
{
	// 4X MSAA 품질 수준 지원 점검
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels;
	ZeroMemory(&msaaQualityLevels, sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS));
	msaaQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	msaaQualityLevels.SampleCount = 4;
	msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msaaQualityLevels.NumQualityLevels = 0;

	// 디바이스가 지원하는 다중 샘플의 품질 수준을 확인.
	if FAILED(graphicDevice_->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,	// 다중 표본화 기능.
		&msaaQualityLevels,							// 기능 지원 정보가 설정될 구조체 포인터.
		sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS)))
	{
		assert("Check Feature Support Failed");
		return E_FAIL;
	}

	//다중 샘플의 품질 수준이 1보다 크면 다중 샘플링을 활성화.
	msaa4XQualityLevel_ = msaaQualityLevels.NumQualityLevels;
	isMsaa4XEnable_ = (msaa4XQualityLevel_ > 1) ? true : false;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc1;
	ZeroMemory(&swapChainDesc1, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swapChainDesc1.Width = width;
	swapChainDesc1.Height = height;
	swapChainDesc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc1.SampleDesc.Count = isMsaa4XEnable_ ? 4 : 1;
	swapChainDesc1.SampleDesc.Quality = isMsaa4XEnable_ ? (msaa4XQualityLevel_ - 1) : 0;
	swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc1.BufferCount = (int)SwapChain::End;
	swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenDesc;
	ZeroMemory(&swapChainFullScreenDesc, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	swapChainFullScreenDesc.RefreshRate.Numerator = 60;
	swapChainFullScreenDesc.RefreshRate.Denominator = 1;
	swapChainFullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainFullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainFullScreenDesc.Windowed = bool(winType);

	if (FAILED(factory_->CreateSwapChainForHwnd(
		graphicDevice_,
		hWnd,
		&swapChainDesc1,
		&swapChainFullScreenDesc,
		nullptr,
		&swapChain_)))
	{
		assert("Create SwapChainForHwnd Failed");
		return E_FAIL;
	}

	return NO_ERROR;
}

HRESULT GraphicDevice::createRtvAndDsvDescriptorHeap()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = (int)SwapChain::End;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	if (FAILED(graphicDevice_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_))))
	{
		assert("Create RTV DescriptHeap Failed");
		return E_FAIL;
	}

	rtvHeap_->SetName(L"RTV DescriptorHeap");

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	if (FAILED(graphicDevice_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_))))
	{
		assert("Create DSV DescriptHeap Failed");
		return E_FAIL;
	}

	dsvHeap_->SetName(L"DSV DescriptorHeap");

	return NO_ERROR;
}

HRESULT GraphicDevice::createFenceObject()
{
	if (FAILED(graphicDevice_->CreateFence(
		0,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&fence_))))
	{
		assert("Create Fence Failed");
		return E_FAIL;
	}

	fence_->SetName(L"Fence");

	return NO_ERROR;
}

HRESULT GraphicDevice::createRenderTargetAndDepthStencilBuffer(const unsigned int width, const unsigned int height)
{
	// Flush before changing any resources
	waitForGpuComplete();

	if (FAILED((commandLists_[(int)CmdList::Main]->Reset(commandAllocators_[(int)CmdList::Main], nullptr))))
	{
		assert("Reset CommandLists Reset Failed");
		return E_FAIL;
	}

	// Resize the swap chain
	if (FAILED(swapChain_->ResizeBuffers(
		(unsigned int)SwapChain::End,
		width,
		height,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)))
	{
		assert("SwapChain ResizeBuffers Failed");
		return E_FAIL;
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(rtvHeap_->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < (int)SwapChain::End; i++)
	{
		ID3D12Resource* swapChainBuffer{ nullptr };
		if (FAILED(swapChain_->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer))))
		{
			assert("SwapChain GetBuffer Failed");
			return E_FAIL;
		}

		graphicDevice_->CreateRenderTargetView(swapChainBuffer,	nullptr, rtvHeapHandle);

		rtvHeapHandle.Offset(1, rtvDescriptorSize_);
		swapChainBuffers_.emplace_back(swapChainBuffer);
	}

	// Create the depth/stencil buffer and view
	D3D12_HEAP_PROPERTIES defaultHeapProperties;
	defaultHeapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	defaultHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	defaultHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	defaultHeapProperties.CreationNodeMask = 1;
	defaultHeapProperties.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = isMsaa4XEnable_ ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = isMsaa4XEnable_ ? (msaa4XQualityLevel_ - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	if (FAILED(graphicDevice_->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(&depthStencilBuffer_))))
	{
		assert("Create Depth Stencil Buffer Failed");
		return E_FAIL;
	}

	// Create descriptor to mip level 0 of entire resource using the format of the resource
	graphicDevice_->CreateDepthStencilView(depthStencilBuffer_, nullptr, dsvHeap_->GetCPUDescriptorHandleForHeapStart());

	// Transition the resource from its initial state to be used as a depth buffer
	commandLists_[(int)CmdList::Main]->ResourceBarrier(
		1, 
		&CD3DX12_RESOURCE_BARRIER::Transition(
			depthStencilBuffer_,
			D3D12_RESOURCE_STATE_COMMON,
			D3D12_RESOURCE_STATE_DEPTH_WRITE));

	// Execute the resize commands
	if (FAILED(commandLists_[(int)CmdList::Main]->Close()))
	{
		assert("CommandList Closd Failed");
		return E_FAIL;
	}

	ID3D12CommandList* cmdsLists[] = { *commandLists_.data() };
	commandQueue_->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete
	waitForGpuComplete();

	// Update the viewport transform to cover the client area
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.Width = (float)width;
	viewport_.Height = (float)height;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;

	scissorRect_ = { 0, 0, (LONG)width, (LONG)height };

	return NO_ERROR;
}

void GraphicDevice::logAdapters()
{
	unsigned int i = 0;
	IDXGIAdapter* adapter = nullptr;
	vector<IDXGIAdapter*> adapterList;

	while (DXGI_ERROR_NOT_FOUND != factory_->EnumAdapters(i, &adapter))
	{
		DXGI_ADAPTER_DESC adapterDesc;
		adapter->GetDesc(&adapterDesc);

		wstring text = L"***Adapter: ";
		text += adapterDesc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.emplace_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		logAdapterOutputs(adapterList[i]);
		safeRelease(adapterList[i]);
	}
}

void GraphicDevice::logAdapterOutputs(IDXGIAdapter* adapter)
{
	unsigned int i = 0;
	IDXGIOutput* output = nullptr;

	while (DXGI_ERROR_NOT_FOUND != adapter->EnumOutputs(i, &output))
	{
		DXGI_OUTPUT_DESC OutputDesc;
		output->GetDesc(&OutputDesc);

		wstring text = L"***Output: ";
		text += OutputDesc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		logOutputDisplayModes(output, DXGI_FORMAT_R8G8B8A8_UNORM);
		safeRelease(output);

		++i;
	}
}

void GraphicDevice::logOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	unsigned int count = 0;
	unsigned int flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		unsigned int n = x.RefreshRate.Numerator;
		unsigned int d = x.RefreshRate.Denominator;
		wstring text =
			L"Width   = " + to_wstring(x.Width) + L" " +
			L"Height  = " + to_wstring(x.Height) + L" " +
			L"Refresh = " + to_wstring(n) + L"/" + to_wstring(d) +
			L"\n";

		OutputDebugString(text.c_str());
	}
}
