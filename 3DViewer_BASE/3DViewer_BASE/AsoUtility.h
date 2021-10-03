#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
static class AsoUtility
{

public:

	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ラジアン(rad)から度(deg)
	static double Rad2Deg(double rad);

	// 度(deg)からラジアン(rad)
	static double Deg2Rad(double deg);

	// ラジアン(rad)から度(deg)
	static float Rad2Deg(float rad);

	// 度(deg)からラジアン(rad)
	static float Deg2Rad(float deg);

	// 0～360度の範囲に収める
	static double DegIn360(double deg);

	// 0(0)～2π(360度)の範囲に収める
	static double RadIn2PI(double rad);

	// 0～360度の範囲に収める
	static float DegIn360(float deg);

	// 0(0)～2π(360度)の範囲に収める
	static float RadIn2PI(float rad);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundRad(float from, float to);
	
	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundDeg(float from, float to);
	
	// 線形補間
	static double Lerp(double start, double end, double t);

	// 角度の線形補間
	static double LerpDeg(double start, double end, double t);

	// 角度の線形補間
	static VECTOR RotXZPos(VECTOR centerPos, VECTOR radiusPos, double rad);

	static double Magnitude(VECTOR v);
	static double Distance(VECTOR v1, VECTOR v2);

};

