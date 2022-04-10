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
T* createObject()
{
	T* instance = new T;

	if (E_FAIL == instance->init())
	{
		safeDelete(instance);
		return nullptr;
	}

	return instance;
};
