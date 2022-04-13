#include "framework.h"
#include "MainApp.h"
#include "GraphicDevice.h"
#include "Renderer.h"
#include "ObjectManager.h"

IMPLEMENT_SINGLETON(MainApp)

MainApp::MainApp()
{
	clear();
}

MainApp::~MainApp()
{
	clear();
}

HRESULT MainApp::init()
{
	FAILED_CHECK(GraphicDevice::getInstance()->init(
		g_hWnd, 
		g_hWnd, 
		WindowType::WindowScreen,
		DEFAULT_WINCX, 
		DEFAULT_WINCY), 
		"GrpahicDevice init Failed");

	FAILED_CHECK(Renderer::getInstance()->init(), "Renderer init Failed");
	FAILED_CHECK(ObjectManager::getInstance()->init(), "ObjectManager init Failed");

	return NO_ERROR;
}

void MainApp::clear()
{
}

void MainApp::update(const float timeDelta)
{
	ObjectManager::getInstance()->update(timeDelta);
}

void MainApp::process(const float timeDelta)
{
	ObjectManager::getInstance()->process(timeDelta);
}

void MainApp::render(const float timeDelta)
{
	Renderer::getInstance()->render(timeDelta);
}

