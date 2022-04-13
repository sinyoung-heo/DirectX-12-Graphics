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
	void update(const float timeDelta);		// ��ü ���� ������Ʈ (�̵�, ����, ȸ�� ��)
	void process(const float timeDelta);	// ��ü ���� ������Ʈ ��, ���� �̺�Ʈ ó�� (�浹, ������ ��)

	void clearObjectList(const LayerTag::T layer, const ObjectTag::T id);
	void clearObjectList();

private:
	vector<ObjectList> objectList_[LayerTag::End];
};

