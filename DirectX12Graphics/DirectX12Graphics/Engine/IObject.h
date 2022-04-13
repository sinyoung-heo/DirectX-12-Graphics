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
	virtual int update(const float timeDelta) PURE;	// 객체 상태 업데이트 (이동, 신축, 회전 등)
	virtual void process(const float timeDelta) PURE;	// 객체 상태 업데이트 후, 각종 이벤트 처리 (충돌, 렌더링 등)
	virtual void render(const float timeDelta) PURE;	// 객체 렌더링
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