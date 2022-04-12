#pragma once
class IComponent
{
protected:
	explicit IComponent() = default;
	explicit IComponent(const IComponent& rhs);
	virtual ~IComponent() = default;

public:
	virtual void init() PURE;
	virtual void clear() PURE;
	virtual void update(const float timeDelta) PURE;
	virtual void process(const float timeDelta) PURE;
	virtual void render(const float timeDelta) PURE;

protected:
	bool isClone_{ false };
};

