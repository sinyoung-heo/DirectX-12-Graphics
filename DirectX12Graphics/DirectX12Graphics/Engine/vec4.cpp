#include "framework.h"
#include "vec4.h"
#include "vec3.h"

vec4::vec4()
	: XMFLOAT4(0.f, 0.f, 0.f, 0.f)
{
}

vec4::vec4(const float x, const float y, const float z, const float w)
	: XMFLOAT4(x, y, z, w)
{
}

vec4::vec4(const float input)
	: XMFLOAT4(input, input, input, input)
{
}

vec4::vec4(const XMFLOAT3& vector, const float w)
	: XMFLOAT4(vector.x, vector.y, vector.z, w)
{
}

vec4::vec4(const XMFLOAT4& input)
	: XMFLOAT4(input)
{
}

void vec4::init()
{
}

void vec4::clear()
{
}

void vec4::update(const float timeDelta)
{
}

void vec4::process(const float timeDelta)
{
}

void vec4::render(const float timeDelta)
{
}


void vec4::print()
{
	TCHAR mas[MAX_STR] = L"";
	wsprintf(mas, L"x : %0.1f, y : %0.1f, z : %0.1f, w : 0.1f\n", x, y, z, w);

	OutputDebugString(mas);
}

const float vec4::getX()
{
	return x;
}

const float vec4::getY()
{
	return y;
}

const float vec4::getZ()
{
	return z;
}

const float vec4::getW()
{
	return w;
}

XMVECTOR vec4::getXMVECTOR()
{
	return XMVectorSet(this->x, this->y, this->z, this->w);
}

void vec4::normalize()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector4Normalize(src);

	this->x = XMVectorGetX(src);
	this->y = XMVectorGetY(src);
	this->z = XMVectorGetZ(src);
	this->w = XMVectorGetW(src);
}

float vec4::dot(const vec4& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, dst.z, dst.w);
	XMVECTOR v2 = getXMVECTOR();
	XMVECTOR result = XMVector4Dot(v1, v2);

	return XMVectorGetX(result);
}

vec4 vec4::crossInV1_V2(const vec4& v1, const vec4& v2)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, v1.z, v1.w);
	XMVECTOR V2 = XMVectorSet(v2.x, v2.y, v2.z, v2.w);
	XMVECTOR V3 = getXMVECTOR();
	XMVECTOR result = XMVector4Cross(V1, V2, V3);

	return vec4(XMVectorGetX(result), XMVectorGetY(result), XMVectorGetZ(result), XMVectorGetW(result));
}

vec4 vec4::crossInV2_V3(const vec4& v2, const vec4& v3)
{
	XMVECTOR V1 = getXMVECTOR();
	XMVECTOR V2 = XMVectorSet(v2.x, v2.y, v2.z, v2.w);
	XMVECTOR V3 = XMVectorSet(v3.x, v3.y, v3.z, v3.w);
	XMVECTOR result = XMVector4Cross(V1, V2, V3);

	return vec4(XMVectorGetX(result), XMVectorGetY(result), XMVectorGetZ(result), XMVectorGetW(result));
}

vec4 vec4::crossInV1_V3(const vec4& v1, const vec4& v3)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, v1.z, v1.w);
	XMVECTOR V2 = getXMVECTOR();
	XMVECTOR V3 = XMVectorSet(v3.x, v3.y, v3.z, v3.w);
	XMVECTOR result = XMVector4Cross(V1, V2, V3);

	return vec4(XMVectorGetX(result), XMVectorGetY(result), XMVectorGetZ(result), XMVectorGetW(result));
}

void vec4::planeFromPoints(vec3& v1, vec3& v2, vec3& v3)
{
	XMVECTOR V1 = v1.getXMVECTOR(1.0f);
	XMVECTOR V2 = v2.getXMVECTOR(1.0f);
	XMVECTOR V3 = v3.getXMVECTOR(1.0f);

	XMVECTOR P1 = XMPlaneFromPoints(V1, V2, V3);

	this->x = XMVectorGetX(P1);
	this->y = XMVectorGetY(P1);
	this->z = XMVectorGetZ(P1);
	this->w = XMVectorGetW(P1);
}

float vec4::getLength()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector4Length(src);

	return XMVectorGetX(src);
}

float vec4::getDistance(const vec4& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, dst.z, dst.w);
	XMVECTOR v2 = getXMVECTOR();

	XMVECTOR result = v1 - v2;
	result = XMVector4Length(result);

	return XMVectorGetX(result);
}

float vec4::getAngle(const vec4& dst)
{
	XMVECTOR v1 = getXMVECTOR();
	XMVECTOR v2 = XMVectorSet(dst.x, dst.y, dst.z, dst.w);

	XMVECTOR angle = XMVector4AngleBetweenVectors(v1, v2);
	float	angleRadians = XMVectorGetX(angle);

	return XMConvertToDegrees(angleRadians);
}

vec4 vec4::operator+(const vec4& input)
{
	return vec4(this->x + input.x, this->y + input.y, this->z + input.z, this->w + input.w);
}

const vec4 vec4::operator+(const vec4& input) const
{
	return vec4(this->x + input.x, this->y + input.y, this->z + input.z, this->w + input.w);
}

vec4 vec4::operator-(const vec4& input)
{
	return vec4(this->x - input.x, this->y - input.y, this->z - input.z, this->w - input.w);
}

const vec4 vec4::operator-(const vec4& input) const
{
	return vec4(this->x - input.x, this->y - input.y, this->z - input.z, this->w - input.w);
}

vec4 vec4::operator*(const vec4& input)
{
	return vec4(this->x * input.x, this->y * input.y, this->z * input.z, this->w * input.w);
}

vec4 vec4::operator*(const int input)
{
	return vec4((float)input * this->x, (float)input * this->y, (float)input * this->z, (float)input * this->w);
}

vec4 vec4::operator*(const float input)
{
	return vec4(input * this->x, input * this->y, input * this->z, input * this->w);
}

vec4 vec4::operator*(const double input)
{
	return vec4((float)input * this->x, (float)input * this->y, (float)input * this->z, (float)input * this->w);
}

const vec4 vec4::operator*(const vec4& input) const
{
	return vec4(this->x * input.x, this->y * input.y, this->z * input.z, this->w * input.w);
}

const vec4 vec4::operator*(const int input) const
{
	return vec4((float)input * this->x, (float)input * this->y, (float)input * this->z, (float)input * this->w);
}

const vec4 vec4::operator*(const float input) const
{
	return vec4(input * this->x, input * this->y, input * this->z, input * this->w);
}

const vec4 vec4::operator*(const double input) const
{
	return vec4((float)input * this->x, (float)input * this->y, (float)input * this->z, (float)input * this->w);
}

vec4 operator*(const int input, vec4& v1)
{
	return vec4((float)input * v1.x, (float)input * v1.y, (float)input * v1.z, (float)input * v1.w);
}

vec4 operator*(const float input, vec4& v1)
{
	return vec4(input * v1.x, input * v1.y, input * v1.z, input * v1.w);
}

vec4 operator*(const double input, vec4& v1)
{
	return vec4((float)input * v1.x, (float)input * v1.y, (float)input * v1.z, (float)input * v1.w);
}

vec4 vec4::operator+=(const vec4& input)
{
	return (*this) = (*this) + input;
}

vec4 vec4::operator-=(const vec4& input)
{
	return (*this) = (*this) - input;
}

vec4 vec4::operator*=(const vec4& input)
{
	return (*this) = (*this) * input;
}

vec4 vec4::operator*=(const int input)
{
	return (*this) = (*this) * input;
}

vec4 vec4::operator*=(const float input)
{
	return (*this) = (*this) * input;
}

vec4 vec4::operator*=(const double input)
{
	return (*this) = (*this) * input;
}

const bool vec4::operator==(const vec4& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, input.z, input.w);
	XMVECTOR src = XMVectorSet(this->x, this->y, this->z, this->w);

	return XMVector4Equal(dst, src);
}

const bool vec4::operator!=(const vec4& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, input.z, input.w);
	XMVECTOR src = XMVectorSet(this->x, this->y, this->z, this->w);

	return !XMVector4Equal(dst, src);
}
