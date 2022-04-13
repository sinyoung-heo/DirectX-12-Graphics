#pragma once
#include "Include.h"
#include "SingletonMacro.h"

class MainApp
{
	DECLARE_SINGLETON(MainApp)

private:
	explicit MainApp();
	~MainApp();

public:
	HRESULT init();
	void clear();
	void update(const float timeDelta);		// ��ü ���� ������Ʈ (�̵�, ����, ȸ�� ��)
	void process(const float timeDelta);	// ��ü ���� ������Ʈ ��, ���� �̺�Ʈ ó�� (�浹, ������ ��)
	void render(const float timeDelta);
};

