#pragma once
#include <utility>
#include "Vector2.h"

class Raycast
{
public:
	struct Ray
	{
		Vector2 point;
		Vector2 vec;
	};
	struct Line
	{
		Vector2 point;
		Vector2 end;
		Vector2 vec() {
			return end - point;
		};
	};
	bool CheckCollision(const Vector2& ray, const std::pair<Vector2, Vector2>& col);
	bool CheckRay(Ray ray, Line line);
};

