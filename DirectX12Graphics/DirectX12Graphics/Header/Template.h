#pragma once

// 동적할당 해제
template <class T>
void safeDelete(T& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <class T>
void safeDeleteArray(T& ptr)
{
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

// 싱글톤 오브젝트
template <class T>
class SingletonObject
{
protected:
	explicit SingletonObject()
	{
	};
	virtual ~SingletonObject()
	{
	};

public:													
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
		return instance;
	}

	void destorySingleton()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	static T* instance;
};

#define IMPLEMENT_SINGLETON(T)	T* T::instance = nullptr;

// 객체 생성
template <class T>
T* createObject()
{
	T* instance = new T;

	if (E_FAIL == instance->init())
		return nullptr;

	return instance;
};