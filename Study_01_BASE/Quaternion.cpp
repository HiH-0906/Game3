#include <math.h>
#include "DxLib.h"
#include "AsoUtility.h"
#include "Quaternion.h"

Quaternion::Quaternion(void)
{
    w = 1;
    x = y = z = 0;
}

Quaternion::Quaternion(VECTOR rad)
{
    Quaternion q = Euler(rad.x, rad.y, rad.z);
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}

Quaternion::Quaternion(double ww, double wx, double wy, double wz)
{
    w = ww;
    x = wx;
    y = wy;
    z = wz;
}

Quaternion Quaternion::Euler(VECTOR rad)
{
    return Euler(rad.x, rad.y, rad.z);
}

Quaternion Quaternion::Euler(double radX, double radY, double radZ)
{

    Quaternion ret;

    radX = AsoUtility::RadIn2PI(radX);
    radY = AsoUtility::RadIn2PI(radY);
    radZ = AsoUtility::RadIn2PI(radZ);

    double cosZ = cos(radZ / 2.0f);
    double sinZ = sin(radZ / 2.0f);
    double cosX = cos(radX / 2.0f);
    double sinX = sin(radX / 2.0f);
    double cosY = cos(radY / 2.0f);
    double sinY = sin(radY / 2.0f);

    //ret.w = cosZ * cosX * cosY + sinZ * sinX * sinY;
    //ret.x = sinZ * cosX * cosY - cosZ * sinX * sinY;
    //ret.y = cosZ * sinX * cosY + sinZ * cosX * sinY;
    //ret.z = cosZ * cosX * sinY - sinZ * sinX * cosY;

    ret.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
    ret.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
    ret.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
    ret.z = cosX * cosY * sinZ - sinX * sinY * cosZ;

    return ret;

}

Quaternion Quaternion::Mult(Quaternion q1, Quaternion q2)
{

    Quaternion ret;
    double d1, d2, d3, d4;

    // wの計算 
    d1 = q1.w * q2.w;
    d2 = -q1.x * q2.x;
    d3 = -q1.y * q2.y;
    d4 = -q1.z * q2.z;
    ret.w = d1 + d2 + d3 + d4;

    // xの計算 
    d1 = q1.w * q2.x;
    d2 = q2.w * q1.x;
    d3 = q1.y * q2.z;
    d4 = -q1.z * q2.y;
    ret.x = d1 + d2 + d3 + d4;

    // yの計算
    d1 = q1.w * q2.y;
    d2 = q2.w * q1.y;
    d3 = q1.z * q2.x;
    d4 = -q1.x * q2.z;
    ret.y = d1 + d2 + d3 + d4;

    // zの計算
    d1 = q1.w * q2.z;
    d2 = q2.w * q1.z;
    d3 = q1.x * q2.y;
    d4 = -q1.y * q2.x;
    ret.z = d1 + d2 + d3 + d4;

    return ret;

}

Quaternion Quaternion::Mult(Quaternion q)
{
    return Mult(Quaternion(w, x, y, z), q);
}

Quaternion Quaternion::AngleAxis(double rad, VECTOR axis)
{

    Quaternion ret;

    double norm;
    double c, s;

    ret.w = ret.x = ret.y = ret.z = 0.0;

    norm = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
    if (norm <= 0.0f)
    {
        return ret;
    }

    norm = 1.0f / sqrt(norm);
    axis.x *= norm;
    axis.y *= norm;
    axis.z *= norm;

    c = cos(0.5f * rad);
    s = sin(0.5f * rad);

    ret.w = c;
    ret.x = s * axis.x;
    ret.y = s * axis.y;
    ret.z = s * axis.z;

    return ret;

}

VECTOR Quaternion::PosAxis(Quaternion q, VECTOR pos)
{
    // 位置情報に回転情報を反映させる
    // pos' = q・pos・q(-1)
    Quaternion tmp = Quaternion();
    tmp = tmp.Mult(q);
    tmp = tmp.Mult(Quaternion(0.0f, pos.x, pos.y, pos.z));
    tmp = tmp.Mult(q.Inverse());
    return { (float)tmp.x, (float)tmp.y, (float)tmp.z };
}

VECTOR Quaternion::PosAxis(VECTOR pos)
{
    return PosAxis(Quaternion(w, x, y, z), pos);
}

VECTOR Quaternion::ToEuler(Quaternion q)
{

    VECTOR ret;

    double r11 = 2 * (q.x * q.z + q.w * q.y);
    double r12 = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
    double r21 = -2 * (q.y * q.z - q.w * q.x);
    double r31 = 2 * (q.x * q.y + q.w * q.z);
    double r32 = q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z;

    ret.x = asin(r21);
    ret.y = atan2(r11, r12);
    ret.z = atan2(r31, r32);

    return ret;

}

VECTOR Quaternion::ToEuler(void)
{
    return ToEuler(Quaternion(w, x, y, z));
}

MATRIX Quaternion::ToMatrix(Quaternion q)
{

    float sqw = q.w * q.w;
    float sqx = q.x * q.x;
    float sqy = q.y * q.y;
    float sqz = q.z * q.z;
    float invs = 1.0f / (sqx + sqy + sqz + sqw);

    MATRIX matrix = MGetIdent();

    matrix.m[0][0] = (sqx - sqy - sqz + sqw) * invs;
    matrix.m[1][1] = (-sqx + sqy - sqz + sqw) * invs;
    matrix.m[2][2] = (-sqx - sqy + sqz + sqw) * invs;

    float tmp1 = q.x * q.y;
    float tmp2 = q.z * q.w;
    matrix.m[0][1] = 2.0 * (tmp1 + tmp2) * invs;
    matrix.m[1][0] = 2.0 * (tmp1 - tmp2) * invs;

    tmp1 = q.x * q.z;
    tmp2 = q.y * q.w;
    matrix.m[0][2] = 2.0 * (tmp1 - tmp2) * invs;
    matrix.m[2][0] = 2.0 * (tmp1 + tmp2) * invs;

    tmp1 = q.y * q.z;
    tmp2 = q.x * q.w;
    matrix.m[1][2] = 2.0 * (tmp1 + tmp2) * invs;
    matrix.m[2][1] = 2.0 * (tmp1 - tmp2) * invs;

    return matrix;

}

MATRIX Quaternion::ToMatrix(void)
{
    return ToMatrix(Quaternion(w, x, y, z));
}

Quaternion Quaternion::LookRotation(VECTOR dir)
{

    VECTOR up = { 0.0f, 1.0f, 0.0f };

    dir = AsoUtility::VNormalize(dir);
    VECTOR right = AsoUtility::VNormalize(VCross(up, dir));
    up = VCross(dir, right);
    auto m00 = right.x;
    auto m01 = right.y;
    auto m02 = right.z;
    auto m10 = up.x;
    auto m11 = up.y;
    auto m12 = up.z;
    auto m20 = dir.x;
    auto m21 = dir.y;
    auto m22 = dir.z;


    float num8 = (m00 + m11) + m22;
    auto quaternion = Quaternion();
    if (num8 > 0.0f)
    {
        auto num = sqrt(num8 + 1.0f);
        quaternion.w = num * 0.5f;
        num = 0.5f / num;
        quaternion.x = (m12 - m21) * num;
        quaternion.y = (m20 - m02) * num;
        quaternion.z = (m01 - m10) * num;
        return quaternion.Normalized();
    }
    if ((m00 >= m11) && (m00 >= m22))
    {
        // xとwが逆？
        //auto num7 = sqrt(((1.0f + m00) - m11) - m22);
        //auto num4 = 0.5f / num7;
        //quaternion.x = 0.5f * num7;
        //quaternion.y = (m01 + m10) * num4;
        //quaternion.z = (m02 + m20) * num4;
        //quaternion.w = (m12 - m21) * num4;
        //return quaternion.Normalized();
        auto num7 = sqrt(((1.0f + m00) - m11) - m22);
        auto num4 = 0.5f / num7;
        quaternion.x = (m12 - m21) * num4;
        quaternion.y = (m01 + m10) * num4;
        quaternion.z = (m02 + m20) * num4;
        quaternion.w = 0.5f * num7;
        return quaternion.Normalized();
    }
    if (m11 > m22)
    {
        auto num6 = sqrt(((1.0f + m11) - m00) - m22);
        auto num3 = 0.5f / num6;
        quaternion.x = (m10 + m01) * num3;
        quaternion.y = 0.5f * num6;
        quaternion.z = (m21 + m12) * num3;
        quaternion.w = (m20 - m02) * num3;
        return quaternion.Normalized();
    }
    auto num5 = sqrt(((1.0f + m22) - m00) - m11);
    auto num2 = 0.5f / num5;
    quaternion.x = (m20 + m02) * num2;
    quaternion.y = (m21 + m12) * num2;
    quaternion.z = 0.5f * num5;
    quaternion.w = (m01 - m10) * num2;
    return quaternion.Normalized();

}

Quaternion Quaternion::GetRotation(MATRIX mat)
{

    float elem[4];
    elem[0] = mat.m[0][0] - mat.m[1][1] - mat.m[2][2] + 1.0f;
    elem[1] = -mat.m[0][0] + mat.m[1][1] - mat.m[2][2] + 1.0f;
    elem[2] = -mat.m[0][0] - mat.m[1][1] + mat.m[2][2] + 1.0f;
    elem[3] = mat.m[0][0] + mat.m[1][1] + mat.m[2][2] + 1.0f;

    int biggestIdx = 0;
    for (int i = 0; i < 4; i++)
    {
        if (elem[i] > elem[biggestIdx])
        {
            biggestIdx = i;
        }
    }

    if (elem[biggestIdx] < 0)
    {
        return Quaternion();
    }

    float q[4];
    float v = sqrt(elem[biggestIdx]) * 0.5f;
    q[biggestIdx] = v;
    float mult = 0.25f / v;

    switch (biggestIdx)
    {
    case 0:
        q[1] = (mat.m[1][0] + mat.m[0][1]) * mult;
        q[2] = (mat.m[0][2] + mat.m[2][0]) * mult;
        q[3] = (mat.m[2][1] - mat.m[1][2]) * mult;
        break;
    case 1:
        q[0] = (mat.m[1][0] + mat.m[0][1]) * mult;
        q[2] = (mat.m[2][1] + mat.m[1][2]) * mult;
        q[3] = (mat.m[0][2] - mat.m[2][0]) * mult;
        break;
    case 2:
        q[0] = (mat.m[0][2] + mat.m[2][0]) * mult;
        q[1] = (mat.m[2][1] + mat.m[1][2]) * mult;
        q[3] = (mat.m[1][0] - mat.m[0][1]) * mult;
        break;
    case 3:
        q[0] = (mat.m[2][1] - mat.m[1][2]) * mult;
        q[1] = (mat.m[0][2] - mat.m[2][0]) * mult;
        q[2] = (mat.m[1][0] - mat.m[0][1]) * mult;
        break;
    }

    return Quaternion(q[3], q[0], q[1], q[2]);

}

VECTOR Quaternion::GetDir(VECTOR dir)
{
    return PosAxis(dir);
}

VECTOR Quaternion::GetForward(void)
{
    return GetDir(AsoUtility::DIR_F);
}

VECTOR Quaternion::GetBack(void)
{
    return GetDir(AsoUtility::DIR_B);
}

VECTOR Quaternion::GetRight(void)
{
    return GetDir(AsoUtility::DIR_R);
}

VECTOR Quaternion::GetLeft(void)
{
    return GetDir(AsoUtility::DIR_F);
}

VECTOR Quaternion::GetUp(void)
{
    return GetDir(AsoUtility::DIR_U);
}

VECTOR Quaternion::GetDown(void)
{
    return GetDir(AsoUtility::DIR_D);
}

float Quaternion::Dot(Quaternion q1, Quaternion q2)
{
    return (q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
}

float Quaternion::Dot(Quaternion q)
{
    return (w * q.w + x * q.x + y * q.y + z * q.z);
}

Quaternion Quaternion::Normalized(void)
{

    float mag = sqrtf(w * w + x * x + y * y + z * z);
    return Quaternion(w / mag, x / mag, y / mag, z / mag);

}

void Quaternion::Normalize(void)
{

    float mag = sqrtf(w * w + x * x + y * y + z * z);

    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;

}

Quaternion Quaternion::Inverse(void)
{

    double n = 1.0f / (w * w + x * x + y * y + z * z);
    Quaternion tmp = Quaternion(w, -x, -y, -z);
    return Quaternion(tmp.w * n, tmp.x * n, tmp.y * n, tmp.z * n);;

}


Quaternion Quaternion::Slerp(Quaternion from, Quaternion to, double t)
{

    float cos = Quaternion::Dot(from, to);
    Quaternion temp(to);

    if (cos < 0.0f) {
        cos *= -1.0f;
        temp = temp * -1.0f;
    }

    float theta = acosf(cos);
    float sinTheta = 1.0f / sinf(theta);

    auto q = (
        ((Quaternion)(from * sinf(theta * (1.0f - t)))) +
        ((Quaternion)(temp * sinf(t * theta)))
        );

    //return sinTheta * q;
    return q * sinTheta;

}

inline float SIGN(float x) {
    return (x >= 0.0f) ? +1.0f : -1.0f;
}

inline float NORM(float a, float b, float c, float d) {
    return sqrt(a * a + b * b + c * c + d * d);
}

Quaternion Quaternion::operator*(float& f) {
    return Quaternion(w * f, x * f, y * f, z * f);
}

const Quaternion Quaternion::operator*(const float& f) {
    return Quaternion(w * f, x * f, y * f, z * f);
}

Quaternion Quaternion::operator+(Quaternion& rhs) {
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

const Quaternion Quaternion::operator+(const Quaternion& rhs) {
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}