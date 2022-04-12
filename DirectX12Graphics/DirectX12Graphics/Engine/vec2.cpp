#include "framework.h"
#include "vec2.h"

vec2::vec2()
	: XMFLOAT2(0.f, 0.f)
{
}

vec2::vec2(const float x, const float y)
	: XMFLOAT2(x, y)
{
}

vec2::vec2(const float input)
	: XMFLOAT2(input, input)
{
}

vec2::vec2(const XMFLOAT2& input)
	: XMFLOAT2(input)
{
}

void vec2::init()
{
}

void vec2::clear()
{
}

void vec2::update(const float timeDelta)
{
}

void vec2::process(const float timeDelta)
{
}

void vec2::render(const float timeDelta)
{
}

void vec2::print()
{
	TCHAR mas[MAX_STR] = L"";
	wsprintf(mas, L"x : %0.1f, y : %0.1f\n", x, y);

	OutputDebugString(mas);
}

const float vec2::getX()
{
	return x;
}

const float vec2::getY()
{
	return y;
}

XMVECTOR vec2::getXMVECTOR()
{
	return XMVectorSet(this->x, this->y, 0.f, 0.f);
}

void vec2::normalize()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector2Normalize(src);

	this->x = XMVectorGetX(src);
	this->y = XMVectorGetY(src);
}

float vec2::dot(const vec2& v1)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, 0.f, 0.f);
	XMVECTOR V2 = getXMVECTOR();
	XMVECTOR result = XMVector2Dot(V1, V2);

	return XMVectorGetX(result);
}

vec2 vec2::crossInV1(const vec2& v1)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, 0.f, 0.f);
	XMVECTOR V2 = getXMVECTOR();
	XMVECTOR result = XMVector2Cross(V1, V2);

	return vec2(XMVectorGetX(result), XMVectorGetY(result));
}

vec2 vec2::crossInV2(const vec2& v2)
{
	XMVECTOR V1 = getXMVECTOR();
	XMVECTOR V2 = XMVectorSet(v2.x, v2.y, 0.f, 0.f);
	XMVECTOR result = XMVector2Cross(V1, V2);

	return vec2(XMVectorGetX(result), XMVectorGetY(result));
}

float vec2::getLength()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector2Length(src);

	return XMVectorGetX(src);
}

float vec2::getDistance(const vec2& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, 0.f, 0.f);
	XMVECTOR v2 = getXMVECTOR();

	XMVECTOR result = v1 - v2;
	result = XMVector2Length(result);

	return XMVectorGetX(result);
}

float vec2::getAngle(const vec2& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, 0.f, 0.f);
	XMVECTOR v2 = getXMVECTOR();

	XMVECTOR angle = XMVector2AngleBetweenVectors(v1, v2);
	float	angleRadians = XMVectorGetX(angle);

	return XMConvertToDegrees(angleRadians);
}

vec2 vec2::operator+(const vec2& input)
{
	return vec2(this->x + input.x, this->y + input.y);
}

const vec2 vec2::operator+(const vec2& input) const
{
	return vec2(this->x + input.x, this->y + input.y);
}

vec2 vec2::operator-(const vec2& input)
{
	return vec2(this->x - input.x, this->y - input.y);
}

const vec2 vec2::operator-(const vec2& input) const
{
	return vec2(this->x - input.x, this->y - input.y);
}

vec2 vec2::operator*(const vec2& input)
{
	return vec2(this->x * input.x, this->y * input.y);
}

vec2 vec2::operator*(const int input)
{
	return vec2((float)input * this->x, (float)input * this->y);
}

vec2 vec2::operator*(const float input)
{
	return vec2(input * this->x, input * this->y);
}

vec2 vec2::operator*(const double input)
{
	return vec2((float)input * this->x, (float)input * this->y);
}

const vec2 vec2::operator*(const vec2& input) const
{
	return vec2(this->x * input.x, this->y * input.y);
}

const vec2 vec2::operator*(const int input) const
{
	return vec2((float)input * this->x, (float)input * this->y);
}

const vec2 vec2::operator*(const float input) const
{
	return vec2(input * this->x, input * this->y);
}

const vec2 vec2::operator*(const double input) const
{
	return vec2((float)input * this->x, (float)input * this->y);
}

vec2 operator*(const int input, vec2& v1)
{
	return vec2((float)input * v1.x, (float)input * v1.y);
}

vec2 operator*(const float input, vec2& v1)
{
	return vec2(input * v1.x, input * v1.y);
}

vec2 operator*(const double input, vec2& v1)
{
	return vec2((float)input * v1.x, (float)input * v1.y);
}

vec2 vec2::operator+=(const vec2& input)
{
	return (*this) = (*this) + input;
}

vec2 vec2::operator-=(const vec2& input)
{
	return (*this) = (*this) - input;
}

vec2 vec2::operator*=(const vec2& input)
{
	return (*this) = (*this) * input;
}

vec2 vec2::operator*=(const int input)
{
	return (*this) = (*this) * input;
}

vec2 vec2::operator*=(const float input)
{
	return (*this) = (*this) * input;
}

vec2 vec2::operator*=(const double input)
{
	return (*this) = (*this) * input;
}

const bool vec2::operator==(const vec2& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, 0.f, 0.f);
	XMVECTOR src = XMVectorSet(this->x, this->y, 0.f, 0.f);

	return XMVector2Equal(dst, src);
}

const bool vec2::operator!=(const vec2& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, 0.f, 0.f);
	XMVECTOR src = XMVectorSet(this->x, this->y, 0.f, 0.f);

	return !XMVector2Equal(dst, src);
}
