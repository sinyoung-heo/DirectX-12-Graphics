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
	void update(const float timeDelta);		// 객체 상태 업데이트 (이동, 신축, 회전 등)
	void process(const float timeDelta);	// 객체 상태 업데이트 후, 각종 이벤트 처리 (충돌, 렌더링 등)
	void render(const float timeDelta);
};

