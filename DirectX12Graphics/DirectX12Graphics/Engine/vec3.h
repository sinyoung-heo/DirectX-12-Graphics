#pragma once
#include "Include.h"
#include "IComponent.h"

class vec3 : public IComponent, XMFLOAT3
{
public:
	explicit vec3();
	explicit vec3(const float x, const float y, const float z);
	explicit vec3(const float input);
	explicit vec3(const XMFLOAT3& input);
	explicit vec3(const XMFLOAT4& input);
	virtual ~vec3() = default;

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
	XMVECTOR getXMVECTOR(const float w = 0);
	void normalize();
	float dot(const vec3& v1);
	vec3 crossInV1(const vec3& v1);
	vec3 crossInV2(const vec3& v2);
	void transformCoord(const vec3& input, const XMMATRIX& matrix);
	void transformNormal(const vec3& input, const XMMATRIX& matrix);
	vec3 convertWindowToDescartes(const int width, const int height);
	vec3 convertDescartesToWindow(const int width, const int height);
	vec3 convertProjectionToScreen(const XMMATRIX& matView, const XMMATRIX& matProj, const D3D12_VIEWPORT& vp);
	void convertCatmullRom(vec3& v0, vec3& v1, vec3& v2, vec3& v3, float t);
	float getLength();
	float getDistance(const vec3& dst);
	float getAngle(const vec3& dst);

public:
	// ¿¬»êÀÚ ¿À¹ö·Îµù
	// µ¡¼À
	vec3 operator+(const vec3& input);
	const vec3 operator+(const vec3& input) const;

	// »¬¼À
	vec3 operator-(const vec3& input);
	const vec3 operator-(const vec3& input) const;

	// °ö¼À
	vec3 operator*(const vec3& input);
	vec3 operator*(const int input);
	vec3 operator*(const float input);
	vec3 operator*(const double input);
	const vec3 operator*(const vec3& input) const;
	const vec3 operator*(const int input) const;
	const vec3 operator*(const float input) const;
	const vec3 operator*(const double input) const;

	friend vec3 operator*(const int input, vec3& v1);
	friend vec3 operator*(const float input, vec3& v1);
	friend vec3 operator*(const double input, vec3& v1);

	// ³ª´°¼À
	vec3 operator/(const int input);
	vec3 operator/(const float input);
	vec3 operator/(const double input);
	const vec3 operator/(const int input) const;
	const vec3 operator/(const float input) const;
	const vec3 operator/(const double input) const;

	// Ãà¾à ¿¬»êÀÚ
	vec3 operator+=(const vec3& input);
	vec3 operator-=(const vec3& input);
	vec3 operator*=(const vec3& input);
	vec3 operator*=(const int input);
	vec3 operator*=(const float input);
	vec3 operator*=(const double input);

	// ºñ±³ ¿¬»êÀÚ
	const bool operator==(const vec3& input);
	const bool operator!=(const vec3& input);
};

