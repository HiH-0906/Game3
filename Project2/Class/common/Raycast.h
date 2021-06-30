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
		Line(Vector2 p, Vector2 e)
		{
			point = p;
			end = e;
		}
		Vector2 point;
		Vector2 end;
		Vector2 vec()
		{
			return end - point;
		}
	};
	bool CheckCollision(const Ray& ray, const std::pair<Vector2, Vector2>& col);
	bool CheckLine(Ray ray, Line line);
};