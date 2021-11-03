#pragma once
#include <DxLib.h>
#include "Vector3.h"

static struct DHUtility
{
	// VECTOR ����Vector3�ϊ�
	static Vector3 VECToVec3(const VECTOR& vec);
	static VECTOR Vec3ToVEC(const Vector3& vec);
	// ���W�A��(rad)����x(deg)
	static float Rad2Deg(float rad);

	// �x(deg)���烉�W�A��(rad)
	static float Deg2Rad(float deg);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundRad(float from, float to);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundDeg(float from, float to);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static double DegIn360(double deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static double RadIn2PI(double rad);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static float DegIn360(float deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static float RadIn2PI(float rad);
};

