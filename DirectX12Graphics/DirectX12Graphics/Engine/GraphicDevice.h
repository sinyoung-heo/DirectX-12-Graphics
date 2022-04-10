#pragma once
#include "SingletonMacro.h"

enum class CmdList
{
	Main,
	Resource,
	End
};

enum class SwapChain
{
	Front,
	Back,
	End
};

enum class WindowType
{
	FullScreen,
	WindowScreen,
	End
};

class GraphicDevice
{
	DECLARE_SINGLETON(GraphicDevice)

private:
	explicit GraphicDevice();
	virtual ~GraphicDevice();

public:
	HRESULT init(const HWND hWnd, const HANDLE hHandle, const WindowType winType, const unsigned int width, const unsigned int height);
	void clear();

public:
	HRESULT	waitForGpuComplete();

private:
	HRESULT createGraphicDevice(const unsigned int width, const unsigned int height);
	void findHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppOutAdapter);
	HRESULT createCommandList();
	HRESULT createSwapChain(const HWND hWnd, const WindowType winType, const unsigned int width, const unsigned int height);
	HRESULT createRtvAndDsvDescriptorHeap();
	HRESULT createFenceObject();
	HRESULT createRenderTargetAndDepthStencilBuffer(const unsigned int width, const unsigned int height);

	void logAdapters();
	void logAdapterOutputs(IDXGIAdapter* adapter);
	void logOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

private:
	// DirectX 12 Graphic Device
	ID3D12Device* graphicDevice_{ nullptr };
	wstring graphicDeviceName_;
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
	unsigned int curBackBuffer_{ (unsigned int)SwapChain::Front };
	bool isMsaa4XEnable_{ false };
	unsigned int msaa4XQualityLevel_{ 0 };
	D3D12_VIEWPORT viewport_;
	D3D12_RECT scissorRect_;

	ID3D12Resource* depthStencilBuffer_{ nullptr };

	// Fence Object
	ID3D12Fence* fence_{ nullptr };
	UINT64 curFence_{ 0 };
};

