#pragma once
#include <DxLib.h>
#include "Vector3.h"

static struct DHUtility
{
	// VECTOR ←→Vector3変換
	static Vector3 VECToVec3(const VECTOR& vec);
	static VECTOR Vec3ToVEC(const Vector3& vec);
	// ラジアン(rad)から度(deg)
	static float Rad2Deg(float rad);

	// 度(deg)からラジアン(rad)
	static float Deg2Rad(float deg);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundRad(float from, float to);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundDeg(float from, float to);

	// 0～360度の範囲に収める
	static double DegIn360(double deg);

	// 0(0)～2π(360度)の範囲に収める
	static double RadIn2PI(double rad);

	// 0～360度の範囲に収める
	static float DegIn360(float deg);

	// 0(0)～2π(360度)の範囲に収める
	static float RadIn2PI(float rad);
};

