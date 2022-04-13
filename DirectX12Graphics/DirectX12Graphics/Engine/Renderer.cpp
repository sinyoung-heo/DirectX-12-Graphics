#include "framework.h"
#include "Renderer.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(Renderer)

Renderer::Renderer()
{
	clear();
}

Renderer::~Renderer()
{
	clear();
}

HRESULT Renderer::init()
{
	return S_OK;
}

void Renderer::clear()
{
	clearRenderGroup();
}

void Renderer::render(const float timeDelta)
{
	FAILED_CHECK(GraphicDevice::getInstance()->renderReset(), "GraphicDevice renderReset Failed");

	renderEnvironment(timeDelta);
	renderNoneAlpha(timeDelta);
	renderAlpha(timeDelta);

	FAILED_CHECK(GraphicDevice::getInstance()->renderExcuteCmdList(), "GraphicDevice renderExcuteCmdList Failed");
	FAILED_CHECK(GraphicDevice::getInstance()->renderEnd(), "GraphicDevice renderEnd Failed");
	FAILED_CHECK(GraphicDevice::getInstance()->waitForGpuComplete(), "GraphicDevice waitForGpuComplete Failed");
	clearRenderGroup();
}

void Renderer::addRenderGroup(const RenderGroup::T id, IObject* object)
{
	if (id == RenderGroup::End || object == nullptr)
		return;

	renderList_[id].emplace_back(object);
}

void Renderer::clearRenderGroup(const RenderGroup::T id)
{
	if (id == RenderGroup::End)
		return;

	renderList_[id].clear();
}

void Renderer::clearRenderGroup()
{
	for (auto& group : renderList_)
		group.clear();
}

void Renderer::renderEnvironment(const float timeDelta)
{
	for (auto& object : renderList_[RenderGroup::Environment])
	{
		if (object != nullptr)
		{
			object->render(timeDelta);
		}
	}
}

void Renderer::renderNoneAlpha(const float timeDelta)
{
	for (auto& object : renderList_[RenderGroup::NoneAlpha])
	{
		if (object != nullptr)
		{
			object->render(timeDelta);
		}
	}
}

void Renderer::renderAlpha(const float timeDelta)
{
	for (auto& object : renderList_[RenderGroup::Alpha])
	{
		if (object != nullptr)
		{
			object->render(timeDelta);
		}
	}
}
