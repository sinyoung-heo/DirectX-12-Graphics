#include "framework.h"
#include "ObjectManager.h"

IMPLEMENT_SINGLETON(ObjectManager)

ObjectManager::ObjectManager()
{
	clear();
}

ObjectManager::~ObjectManager()
{
	clear();
}

HRESULT ObjectManager::init()
{

	return S_OK;
}

void ObjectManager::clear()
{
	clearObjectList();
}

void ObjectManager::update(const float timeDelta)
{
	for (auto& objectLayer : objectList_)
	{
		if (objectLayer.empty())
			continue;

		for (auto& objects : objectLayer)
		{
			if (objects.empty())
				continue;

			auto iterBegin = objects.begin();
			auto iterEnd = objects.end();

			for (; iterBegin != iterEnd; )
			{
				int objectEvent = (*iterBegin)->update(timeDelta);

				switch (objectEvent)
				{
				case  ObjectEvent::Delete:
					{
						safeDelete(*iterBegin);
						iterBegin = objects.erase(iterBegin);
					}
					break;
				case ObjectEvent::Return:
					{
						iterBegin = objects.erase(iterBegin);
					}
					break;
				case ObjectEvent::NoEvent:
					{
						++iterBegin;
					}
					break;
				}
			}
		}
	}
}

void ObjectManager::process(const float timeDelta)
{
	for (auto& objectLayer : objectList_)
	{
		if (objectLayer.empty())
			continue;

		for (auto& objects : objectLayer)
		{
			if (objects.empty())
				continue;

			for (auto& object : objects)
			{
				object->process(timeDelta);
			}
		}
	}
}

void ObjectManager::clearObjectList(const LayerTag::T layer, const ObjectTag::T id)
{
	if (layer == LayerTag::End || id == ObjectTag::End)
		return;

	objectList_[layer][id].clear();
}

void ObjectManager::clearObjectList()
{
	for (auto& objects : objectList_)
		objects.clear();
}
