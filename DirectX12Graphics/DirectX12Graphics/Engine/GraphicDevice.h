#pragma once
#include "Include.h"
#include "SingletonMacro.h"

enum_begin(CmdList)
{
	Main,
	Resource,
	End
}
enum_end

enum_begin(SwapChain)
{
	Front,
	Back,
	End
}
enum_end

enum_begin(WindowType)
{
	FullScreen,
	WindowScreen,
	End
}
enum_end

class GraphicDevice
{
	DECLARE_SINGLETON(GraphicDevice)

private:
	explicit GraphicDevice();
	~GraphicDevice();

public:
	HRESULT init(const HWND hWnd, const HANDLE hHandle, const WindowType::T winType, const unsigned int width, const unsigned int height);
	void clear();

public:
	HRESULT renderReset();
	HRESULT renderExcuteCmdList();
	HRESULT renderEnd();
	HRESULT	waitForGpuComplete();

public:
	ID3D12Device* getDevice();
	const wstring& getDeviceName();

private:
	HRESULT createGraphicDevice(const unsigned int width, const unsigned int height);
	void findHardwareAdapter(IDXGIFactory2* factory, IDXGIAdapter1** out);
	HRESULT createCommandList();
	HRESULT createSwapChain(const HWND hWnd, const WindowType::T winType, const unsigned int width, const unsigned int height);
	HRESULT createRtvAndDsvDescriptorHeap();
	HRESULT createFenceObject();
	HRESULT createRenderTargetAndDepthStencilBuffer(const unsigned int width, const unsigned int height);

	void logAdapters();
	void logAdapterOutputs(IDXGIAdapter* adapter);
	void logOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

private:
	// DirectX 12 Graphic Device
	ID3D12Device* device_{ nullptr };
	wstring deviceName_;
	IDXGIFactory4* factory_{ nullptr };
	IDXGISwapChain1* swapChain_{ nullptr };

	// DirectX 12 CommandList
	ID3D12PipelineState* pipelineState_{ nullptr };
	ID3D12CommandQueue* commandQueue_{ nullptr };
	vector<ID3D12CommandAllocator*> commandAllocators_;
	vector<ID3D12GraphicsCommandList*> commandLists_;

	// Descriptor Heap
	ID3D12DescriptorHeap* rtvHeap_{ nullptr };
	ID3D12DescriptorHeap* dsvHeap_{ nullptr };
	unsigned int rtvDescriptorSize_{ 0 };
	unsigned int dsvDescriptorSize_{ 0 };
	unsigned int etcDescriptorSize_{ 0 };

	// Swap Chain Buffers
	vector< ID3D12Resource*> swapChainBuffers_;
	unsigned int curBackBuffer_{ SwapChain::Front };
	bool isMsaa4XEnable_{ false };
	unsigned int msaa4XQualityLevel_{ 0 };
	D3D12_VIEWPORT viewport_;
	D3D12_RECT scissorRect_;

	ID3D12Resource* depthStencilBuffer_{ nullptr };

	// Fence Object
	ID3D12Fence* fence_{ nullptr };
	UINT64 curFence_{ 0 };
};

