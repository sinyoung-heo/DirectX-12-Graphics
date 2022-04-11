#include "framework.h"
#include "MainApp.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(MainApp)

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
	clear();
}

HRESULT MainApp::init()
{
	if (FAILED(GraphicDevice::getInstance()->init(g_hWnd, g_hWnd, WindowType::WindowScreen, DEFAULT_WINCX, DEFAULT_WINCY)))
	{
		assert("GrpahicDevice init Failed");
		return E_FAIL;
	}


	return NO_ERROR;
}

void MainApp::clear()
{
}

void MainApp::update(const float timeDelta)
{
}

void MainApp::process(const float timeDelta)
{
}

void MainApp::render(const float timeDelta)
{
	if (FAILED(GraphicDevice::getInstance()->renderReset()))
	{
		assert(ERROR && "GraphicDevice renderReset Failed");
		return;
	}

	if (FAILED(GraphicDevice::getInstance()->renderExcuteCmdList()))
	{
		assert(ERROR && "GraphicDevice renderExcuteCmdList Failed");
		return;
	}

	if (FAILED(GraphicDevice::getInstance()->renderEnd()))
	{
		assert(ERROR && "GraphicDevice renderEnd Failed");
		return;
	}

	if (FAILED(GraphicDevice::getInstance()->waitForGpuComplete()))
	{
		assert(ERROR && "GraphicDevice waitForGpuComplete Failed");
		return;
	}
}

