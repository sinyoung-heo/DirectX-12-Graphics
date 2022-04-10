#pragma once
#define NO_COPY(CLASSNAME)								\
	private:											\
	CLASSNAME(const CLASSNAME&);						\
	CLASSNAME& operator = (const CLASSNAME&);	

#define DECLARE_SINGLETON(CLASSNAME)					\
	NO_COPY(CLASSNAME)									\
	private:											\
		static CLASSNAME* instance;						\
	public:												\
		static CLASSNAME* getInstance(void);			\
		void destoryInstance(void);

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
	CLASSNAME* CLASSNAME::instance = nullptr;			\
	CLASSNAME* CLASSNAME::getInstance(void)				\
	{													\
		if(instance == nullptr)							\
		{												\
			instance = new CLASSNAME;					\
		}												\
		return instance;								\
	}													\
	void CLASSNAME::destoryInstance(void)				\
	{													\
		if (instance != nullptr)						\
		{												\
			delete instance;							\
			instance = nullptr;							\
		}												\
	}