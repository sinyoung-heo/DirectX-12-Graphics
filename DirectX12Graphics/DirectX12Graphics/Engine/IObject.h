#pragma once
#include "Include.h"

class IObject
{
protected:
	explicit IObject() = default;
	virtual ~IObject() = default;

public:
	virtual void init() PURE;
	virtual void clear() PURE;
	virtual void update(const float timeDelta) PURE;	// ��ü ���� ������Ʈ (�̵�, ����, ȸ�� ��)
	virtual void process(const float timeDelta) PURE;	// ��ü ���� ������Ʈ ��, ���� �̺�Ʈ ó�� (�浹, ������ ��)
	virtual void render(const float timeDelta) PURE;	// ��ü ������
};

