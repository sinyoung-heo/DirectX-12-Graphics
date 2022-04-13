#pragma once
#include "Include.h"
#include "SingletonMacro.h"
#include "IObject.h"

enum_begin(LayerTag)
{
	Camera,
	Environment,
	GameObject,
	UI,
	End
}
enum_end

typedef vector<IObject*> ObjectList;

class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager)

private:
	explicit ObjectManager();
	~ObjectManager();

public:
	HRESULT init();
	void clear();
	void update(const float timeDelta);		// 객체 상태 업데이트 (이동, 신축, 회전 등)
	void process(const float timeDelta);	// 객체 상태 업데이트 후, 각종 이벤트 처리 (충돌, 렌더링 등)

	void clearObjectList(const LayerTag::T layer, const ObjectTag::T id);
	void clearObjectList();

private:
	vector<ObjectList> objectList_[LayerTag::End];
};

