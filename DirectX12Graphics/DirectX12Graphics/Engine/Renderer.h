#pragma once
#include "SingletonMacro.h"
#include "IObject.h"

enum_begin(RenderGroup)
{
	Environment,
	NoneAlpha,
	Alpha,
	End
} 
enum_end

class Renderer
{
	DECLARE_SINGLETON(Renderer)

private:
	explicit Renderer();
	~Renderer();

public:
	HRESULT init();
	void clear();
	void render(const float timeDelta);

	void addRenderGroup(const RenderGroup::T id, IObject* object);
	void clearRenderGroup(const RenderGroup::T id);
	void clearRenderGroup();

private:
	void renderEnvironment(const float timeDelta);
	void renderNoneAlpha(const float timeDelta);
	void renderAlpha(const float timeDelta);

private:
	vector<IObject*> renderList_[RenderGroup::End];
};

