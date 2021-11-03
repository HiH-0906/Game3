#include "DHUtility.h"

Vector3 DHUtility::VECToVec3(const VECTOR& vec)
{
	return Vector3({ vec.x,vec.y,vec.z });
}

VECTOR DHUtility::Vec3ToVEC(const Vector3& vec)
{
	return VECTOR({ vec.x,vec.y,vec.z });
}

float DHUtility::Rad2Deg(float rad)
{
	return rad * (180.0f / DX_PI_F);
}

float DHUtility::Deg2Rad(float deg)
{
	return deg * (DX_PI_F / 180.0f);
}

int DHUtility::DirNearAroundRad(float from, float to)
{
    float ret = 1.0f;
    float diff = to - from;

    if (diff >= 0.0f)
    {
        // ��r���������v���Ɉʒu����
        if (diff > DX_PI_F)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA�����v���̕����߂�
            ret = -1.0f;
        }
        else
        {
            // ���v���
            ret = 1.0f;
        }
    }
    else
    {
        // ��r�����������v���Ɉʒu����
        if (diff < -DX_PI_F)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA���v���̕����߂�
            ret = 1.0f;
        }
        else
        {
            // �����v���
            ret = -1.0f;
        }
    }
    return ret;
}

int DHUtility::DirNearAroundDeg(float from, float to)
{
    float ret = 1.0f;
    float diff = to - from;

    if (diff >= 0.0f)
    {
        // ��r���������v���Ɉʒu����
        if (diff > 180.0f)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA�����v���̕����߂�
            ret = -1.0f;
        }
        else
        {
            // ���v���
            ret = 1.0f;
        }
    }
    else
    {
        // ��r�����������v���Ɉʒu����
        if (diff < -180.0f)
        {
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA���v���̕����߂�
            ret = 1.0f;
        }
        else
        {
            // �����v���
            ret = -1.0f;
        }

    }
    return ret;
}

double DHUtility::DegIn360(double deg)
{
    deg = fmod(deg, 360.0);
    if (deg < 0.0)
    {
        deg += 360.0;
    }
    return deg;
}

double DHUtility::RadIn2PI(double rad)
{
    rad = fmod(rad, DX_TWO_PI);
    if (rad < 0.0)
    {
        rad += DX_TWO_PI;
    }
    return rad;
}

float DHUtility::DegIn360(float deg)
{
    deg = fmodf(deg, 360.0f);
    if (deg < 0.0f)
    {
        deg += 360.0f;
    }
    return deg;
}

float DHUtility::RadIn2PI(float rad)
{
    rad = fmodf(rad, DX_TWO_PI_F);
    if (rad < 0.0f)
    {
        rad += DX_TWO_PI_F;
    }
    return rad;
}

