#include "framework.h"
#include "MainApp.h"

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
}

