#pragma once
#include "IComponent.h"

class vec3;
class vec4 : public IComponent, XMFLOAT4
{
public:
	explicit vec4();
	explicit vec4(const float x, const float y, const float z, const float w);
	explicit vec4(const float input);
	explicit vec4(const XMFLOAT3& vector, const float w);
	explicit vec4(const XMFLOAT4& input);
	virtual ~vec4() = default;

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
	const float getZ();
	const float getW();
	XMVECTOR getXMVECTOR();
	void normalize();
	float dot(const vec4& dst);
	vec4 crossInV1_V2(const vec4& v1, const vec4& v2);
	vec4 crossInV2_V3(const vec4& v2, const vec4& v3);
	vec4 crossInV1_V3(const vec4& v1, const vec4& v3);
	void planeFromPoints(vec3& v1, vec3& v2, vec3& v3);
	float getLength();
	float getDistance(const vec4& dst);
	float getAngle(const vec4& dst);

public:
	// ¿¬»êÀÚ ¿À¹ö·Îµù
	// µ¡¼À
	vec4 operator+(const vec4& input);
	const vec4 operator+(const vec4& input) const;

	// »¬¼À
	vec4 operator-(const vec4& input);
	const vec4 operator-(const vec4& input) const;

	// °ö¼À
	vec4 operator*(const vec4& input);
	vec4 operator*(const int input);
	vec4 operator*(const float input);
	vec4 operator*(const double input);
	const vec4 operator*(const vec4& input) const;
	const vec4 operator*(const int input) const;
	const vec4 operator*(const float input) const;
	const vec4 operator*(const double input) const;

	friend vec4 operator*(const int input, vec4& v1);
	friend vec4 operator*(const float input, vec4& v1);
	friend vec4 operator*(const double input, vec4& v1);

	// Ãà¾à ¿¬»êÀÚ
	vec4 operator+=(const vec4& input);
	vec4 operator-=(const vec4& input);
	vec4 operator*=(const vec4& input);
	vec4 operator*=(const int input);
	vec4 operator*=(const float input);
	vec4 operator*=(const double input);

	// ºñ±³ ¿¬»êÀÚ
	const bool operator==(const vec4& input);
	const bool operator!=(const vec4& input);
};

