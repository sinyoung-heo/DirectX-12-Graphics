#pragma once
// �����Ҵ� ����
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

template <class T>
void safeRelease(T& ptr)
{
	if (ptr != nullptr)
	{
		ptr->Release();
	}
}

// ��ü ����
template <class T>
T* createInstance()
{
	T* instance = new T;

	if (E_FAIL == instance->init())
	{
		safeDelete(instance);
		return nullptr;
	}

	return instance;
};

inline void FAILED_CHECK(const HRESULT hr, const char* msg)
{
	if (hr < 0)
	{
		assert(ERROR && msg);
	}
}
