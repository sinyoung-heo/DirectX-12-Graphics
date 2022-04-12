#include "framework.h"
#include "vec3.h"

vec3::vec3()
	: XMFLOAT3(0.f, 0.f, 0.f)
{
}

vec3::vec3(const float x, const float y, const float z)
	: XMFLOAT3(x, y, z)
{
}

vec3::vec3(const float input)
	: XMFLOAT3(input, input, input)
{
}

vec3::vec3(const XMFLOAT3& input)
	: XMFLOAT3(input)
{
}

vec3::vec3(const XMFLOAT4& input)
	: XMFLOAT3(input.x, input.y, input.z)
{
}

void vec3::init()
{
}

void vec3::clear()
{
}

void vec3::update(const float timeDelta)
{
}

void vec3::process(const float timeDelta)
{
}

void vec3::render(const float timeDelta)
{
}

void vec3::print()
{
	TCHAR mas[MAX_STR] = L"";
	wsprintf(mas, L"x : %0.1f, y : %0.1f, z : %0.1f\n", x, y, z);

	OutputDebugString(mas);
}

const float vec3::getX()
{
	return x;
}

const float vec3::getY()
{
	return y;
}

const float vec3::getZ()
{
	return z;
}

XMVECTOR vec3::getXMVECTOR(const float w)
{
	return XMVectorSet(this->x, this->y, this->z, w);
}

void vec3::normalize()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector3Normalize(src);

	this->x = XMVectorGetX(src);
	this->y = XMVectorGetY(src);
	this->z = XMVectorGetZ(src);
}

float vec3::dot(const vec3& v1)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, v1.z, 0.f);
	XMVECTOR V2 = getXMVECTOR();

	XMVECTOR result = XMVector3Dot(V1, V2);

	return XMVectorGetX(result);
}

vec3 vec3::crossInV1(const vec3& v1)
{
	XMVECTOR V1 = XMVectorSet(v1.x, v1.y, v1.z, 0.f);
	XMVECTOR V2 = getXMVECTOR();
	XMVECTOR result = XMVector3Cross(V1, V2);

	return vec3(XMVectorGetX(result), XMVectorGetY(result), XMVectorGetZ(result));
}

vec3 vec3::crossInV2(const vec3& v2)
{
	XMVECTOR V1 = getXMVECTOR();
	XMVECTOR V2 = XMVectorSet(v2.x, v2.y, v2.z, 0.f);
	XMVECTOR result = XMVector3Cross(V1, V2);

	return vec3(XMVectorGetX(result), XMVectorGetY(result), XMVectorGetZ(result));
}

void vec3::transformCoord(const vec3& input, const XMMATRIX& matrix)
{
	XMVECTOR in = XMVectorSet(input.x, input.y, input.z, 0.f);
	XMVECTOR out = XMVector3TransformCoord(in, matrix);

	this->x = XMVectorGetX(out);
	this->y = XMVectorGetY(out);
	this->z = XMVectorGetZ(out);
}

void vec3::transformNormal(const vec3& input, const XMMATRIX& matrix)
{
	XMVECTOR in = XMVectorSet(input.x, input.y, input.z, 0.f);
	XMVECTOR out = XMVector3TransformNormal(in, matrix);

	this->x = XMVectorGetX(out);
	this->y = XMVectorGetY(out);
	this->z = XMVectorGetZ(out);
}

vec3 vec3::convertWindowToDescartes(const int width, const int height)
{
	// 2D UI 사용 시, Window좌표를 입력해서 사용할 수 있도록
	// 윈도우 좌표를 데카르트 좌표로 변환해주는 좌표.
	vec3 descartes;

	descartes.x = this->x - float(width) / 2.f;
	descartes.y = -this->y + float(height) / 2.f;
	descartes.z = 0.f;

	return descartes;
}

vec3 vec3::convertDescartesToWindow(const int width, const int height)
{
	vec3 window;

	window.x = this->x + float(width) / 2.f;

	if (this->y >= 0)
		window.y = (-1.0f * this->y + float(height) / 2.f);
	else
		window.y = float(height) - (this->y + float(height) / 2.f);

	window.z = this->z;

	return window;
}

vec3 vec3::convertProjectionToScreen(const XMMATRIX& matView, const XMMATRIX& matProj, const D3D12_VIEWPORT& vp)
{
	// 3D 투영 좌표 -> 2D 스크린 좌표로 변환.
	// 1. 월드 좌표 -> 뷰 스페이스 변환.
	vec3 posWV;
	posWV.transformCoord(*this, matView);

	// 2. 뷰 스페이스 -> 투영 변환.
	vec3 posWVP;
	posWVP.transformCoord(posWV, matProj);

	// 3. 투영 변환 -> 뷰포트 변환. (Screen 좌표 변환)
	vec3 screen;
	screen.x = posWVP.x * (vp.Width / 2) + (vp.TopLeftX + vp.Width / 2);
	screen.y = posWVP.y * (-1.f * vp.Height / 2) + (vp.TopLeftY + vp.Height / 2);
	screen.z = 0.f;

	return screen;
}

void vec3::convertCatmullRom(vec3& v0, vec3& v1, vec3& v2, vec3& v3, float t)
{
	XMVECTOR temp = XMVectorCatmullRom(v0.getXMVECTOR(), v1.getXMVECTOR(), v2.getXMVECTOR(), v3.getXMVECTOR(), t);

	this->x = XMVectorGetX(temp);
	this->y = XMVectorGetY(temp);
	this->z = XMVectorGetZ(temp);
}

float vec3::getLength()
{
	XMVECTOR src = getXMVECTOR();
	src = XMVector3Length(src);

	return XMVectorGetX(src);
}

float vec3::getDistance(const vec3& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, dst.z, 0.f);
	XMVECTOR v2 = getXMVECTOR();

	XMVECTOR result = v1 - v2;
	result = XMVector3Length(result);

	return XMVectorGetX(result);
}

float vec3::getAngle(const vec3& dst)
{
	XMVECTOR v1 = XMVectorSet(dst.x, dst.y, dst.z, 0.f);
	XMVECTOR v2 = getXMVECTOR();

	XMVECTOR angle = XMVector3AngleBetweenVectors(v1, v2);
	float angleRadians = XMVectorGetX(angle);

	float ret = 0.f;

	if (this->z < 0.f)
	{
		ret = XMConvertToDegrees(angleRadians);

		if (this->x < 0.0f)
			return 360.f - ret;
		else
			return ret;
	}
	else
	{
		ret = XMConvertToDegrees(angleRadians);
		if (this->x < 0.0f)
			return 360.f - ret;
		else
			return ret;
	}
}

vec3 vec3::operator+(const vec3& input)
{
	return vec3(this->x + input.x, this->y + input.y, this->z + input.z);
}

const vec3 vec3::operator+(const vec3& input) const
{
	return vec3(this->x + input.x, this->y + input.y, this->z + input.z);
}

vec3 vec3::operator-(const vec3& input)
{
	return vec3(this->x - input.x, this->y - input.y, this->z - input.z);
}

const vec3 vec3::operator-(const vec3& input) const
{
	return vec3(this->x - input.x, this->y - input.y, this->z - input.z);
}

vec3 vec3::operator*(const vec3& input)
{
	return vec3(this->x * input.x, this->y * input.y, this->z * input.z);
}

vec3 vec3::operator*(const int input)
{
	return vec3((float)input * this->x, (float)input * this->y, (float)input * this->z);
}

vec3 vec3::operator*(const float input)
{
	return vec3(input * this->x, input * this->y, input * this->z);
}

vec3 vec3::operator*(const double input)
{
	return vec3((float)input * this->x, (float)input * this->y, (float)input * this->z);
}

const vec3 vec3::operator*(const vec3& input) const
{
	return vec3(this->x * input.x, this->y * input.y, this->z * input.z);
}

const vec3 vec3::operator*(const int input) const
{
	return vec3((float)input * this->x, (float)input * this->y, (float)input * this->z);
}

const vec3 vec3::operator*(const float input) const
{
	return vec3(input * this->x, input * this->y, input * this->z);
}

const vec3 vec3::operator*(const double input) const
{
	return vec3((float)input * this->x, (float)input * this->y, (float)input * this->z);
}

vec3 operator*(const int input, vec3& v1)
{
	return vec3((float)input * v1.x, (float)input * v1.y, (float)input * v1.z);
}

vec3 operator*(const float input, vec3& v1)
{
	return vec3(input * v1.x, input * v1.y, input * v1.z);
}

vec3 operator*(const double input, vec3& v1)
{
	return vec3((float)input * v1.x, (float)input * v1.y, (float)input * v1.z);
}

vec3 vec3::operator/(const int input)
{
	return vec3(this->x / (float)input, this->y / (float)input, this->z / (float)input);
}

vec3 vec3::operator/(const float input)
{
	return vec3(this->x / input, this->y / input, this->z / input);
}

vec3 vec3::operator/(const double input)
{
	return vec3(this->x / (float)input, this->y / (float)input, this->z / (float)input);
}

const vec3 vec3::operator/(const int input) const
{
	return vec3(this->x / (float)input, this->y / (float)input, this->z / (float)input);
}

const vec3 vec3::operator/(const float input) const
{
	return vec3(this->x / input, this->y / input, this->z / input);
}

const vec3 vec3::operator/(const double input) const
{
	return vec3(this->x / (float)input, this->y / (float)input, this->z / (float)input);
}

vec3 vec3::operator+=(const vec3& input)
{
	return (*this) = (*this) + input;
}

vec3 vec3::operator-=(const vec3& input)
{
	return (*this) = (*this) - input;
}

vec3 vec3::operator*=(const vec3& input)
{
	return (*this) = (*this) * input;
}

vec3 vec3::operator*=(const int input)
{
	return (*this) = (*this) * input;
}

vec3 vec3::operator*=(const float input)
{
	return (*this) = (*this) * input;
}

vec3 vec3::operator*=(const double input)
{
	return (*this) = (*this) * input;
}

const bool vec3::operator==(const vec3& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, input.z, 0.f);
	XMVECTOR src = XMVectorSet(this->x, this->y, this->z, 0.f);

	return XMVector3Equal(dst, src);
}

const bool vec3::operator!=(const vec3& input)
{
	XMVECTOR dst = XMVectorSet(input.x, input.y, input.z, 0.f);
	XMVECTOR src = XMVectorSet(this->x, this->y, this->z, 0.f);

	return !XMVector3Equal(dst, src);
}
