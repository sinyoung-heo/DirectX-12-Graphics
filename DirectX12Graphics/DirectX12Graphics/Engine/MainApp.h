#pragma once

class MainApp : public SingletonObject<MainApp>
{
public:
	explicit MainApp();
	virtual ~MainApp();

public:
	HRESULT init();
	void clear();
	HRESULT update(const float& timeDelta);
	void render(const float& timeDelta);
};

