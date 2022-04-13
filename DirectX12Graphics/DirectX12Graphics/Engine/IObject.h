#pragma once
#include "Include.h"

class IObject
{
public:
	explicit IObject() = default;
	virtual ~IObject() = default;

public:
	virtual void init() PURE;
	virtual void clear() PURE;
	virtual int update(const float timeDelta) PURE;	// ��ü ���� ������Ʈ (�̵�, ����, ȸ�� ��)
	virtual void process(const float timeDelta) PURE;	// ��ü ���� ������Ʈ ��, ���� �̺�Ʈ ó�� (�浹, ������ ��)
	virtual void render(const float timeDelta) PURE;	// ��ü ������
};

enum_begin(ObjectEvent)
{
	Delete,
	Return,
	NoEvent
}
enum_end

enum_begin(ObjectTag)
{
	Test,
	End
}
enum_end