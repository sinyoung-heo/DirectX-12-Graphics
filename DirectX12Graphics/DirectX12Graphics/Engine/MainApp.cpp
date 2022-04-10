#include "framework.h"
#include "MainApp.h"

IMPLEMENT_SINGLETON(MainApp);

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
	clear();
}

void MainApp::clear()
{
}

HRESULT MainApp::init()
{
	return S_OK;
}

HRESULT MainApp::update(const float& timeDelta)
{
	return S_OK;
}

void MainApp::render(const float& timeDelta)
{
}
