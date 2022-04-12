#pragma once
#include "Include.h"
#include "IComponent.h"

class vec2 : public IComponent, XMFLOAT2
{
public:
	explicit vec2();
	explicit vec2(const float x, const float y);
	explicit vec2(const float input);
	explicit vec2(const XMFLOAT2& input);
	virtual ~vec2() = default;

public:
	// IComponentÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void init() override;
	virtual void clear() override;
	virtual void update(const float timeDelta) override;
	virtual void process(const float timeDelta) override;
	virtual void render(const float timeDelta) override;

public:
	void print();
	const float getX();
	const float getY();
	XMVECTOR getXMVECTOR();
	void normalize();
	float dot(const vec2& v1);
	vec2 crossInV1(const vec2& v1);
	vec2 crossInV2(const vec2& v2);
	float getLength();
	float getDistance(const vec2& dst);
	float getAngle(const vec2& dst);

public:
	// ¿¬»êÀÚ ¿À¹ö·Îµù
	// µ¡¼À
	vec2 operator+(const vec2& input);
	const vec2 operator+(const vec2& input) const;

	// »¬¼À
	vec2 operator-(const vec2& input);
	const vec2 operator-(const vec2& input) const;

	// °ö¼À
	vec2 operator*(const vec2& input);
	vec2 operator*(const int input);
	vec2 operator*(const float input);
	vec2 operator*(const double input);
	const vec2 operator*(const vec2& input) const;
	const vec2 operator*(const int input) const;
	const vec2 operator*(const float input) const;
	const vec2 operator*(const double input) const;

	friend vec2 operator*(const int input, vec2& v1);
	friend vec2 operator*(const float input, vec2& v1);
	friend vec2 operator*(const double input, vec2& v1);

	// Ãà¾à ¿¬»êÀÚ
	vec2 operator+=(const vec2& input);
	vec2 operator-=(const vec2& input);
	vec2 operator*=(const vec2& input);
	vec2 operator*=(const int input);
	vec2 operator*=(const float input);
	vec2 operator*=(const double input);

	// ºñ±³ ¿¬»êÀÚ
	const bool operator==(const vec2& input);
	const bool operator!=(const vec2& input);
};

