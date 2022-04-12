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
	FAILED_CHECK(GraphicDevice::getInstance()->renderReset(), "GraphicDevice renderReset Failed");
	FAILED_CHECK(GraphicDevice::getInstance()->renderExcuteCmdList(), "GraphicDevice renderExcuteCmdList Failed");
	FAILED_CHECK(GraphicDevice::getInstance()->renderEnd(), "GraphicDevice renderEnd Failed");
	FAILED_CHECK(GraphicDevice::getInstance()->waitForGpuComplete(), "GraphicDevice waitForGpuComplete Failed");
}

