#include <cassert>
#include <array>
#include "CircleCollision.h"
#include "SquaerCollision.h"
#include "TriangleCollision.h"
#include "../Circle.h"

CircleCollision::CircleCollision(const float& rad, const Vector2Flt offset):
	Collision(offset),rad_(rad)
{
}

COLLISION_TAG CircleCollision::CollisionTag(void)
{
    return COLLISION_TAG::Circle;
}

bool CircleCollision::isHit(std::shared_ptr<Collision> col)
{
	auto CheckHit = [](const Vector2Flt& veca, const Vector2Flt& vecb, const Vector2Flt& point) {
		float tmp = Cross(Vector2Flt(vecb - veca), Vector2Flt(point - veca));
		if (tmp >= 0)
		{
			return true;
		}
		return false;
	};
	assert(col && "Ç†ÇΩÇËîªíËÇÇ∑ÇÈÉRÉâÉCÉ_Å[Ç™nullptr");
	// â~VSâ~
	auto ccol = std::dynamic_pointer_cast<CircleCollision>(col);
	if (ccol != nullptr)
	{
		const auto myData = GetCircleData();
		const auto cData = ccol->GetCircleData();

		const auto& distance = myData.first - cData.first;
		const auto& radius = myData.second + cData.second;

		if ((distance.x * distance.x) + (distance.y * distance.y) <= radius * radius)
		{
			return true;
		}
	}

	// â~VSãÈå`
	auto scol = std::dynamic_pointer_cast<SquaerCollision>(col);
	if (scol != nullptr)
	{
		// åç∑ÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
		const std::array<int, 4> other = { 1,2,3,0 };
		const auto sVertex = scol->GetVertex();
		const auto myData = GetCircleData();

		for (int i = 0; i < 4; i++)
		{
			auto veca = sVertex[other[i]] - sVertex[i];
			auto vecb = myData.first - sVertex[i];
			auto vecc = myData.first - sVertex[other[i]];
			
			auto d = Cross(veca , vecb) / veca.Magnitude();

			if (abs(d) <= myData.second)
			{
				if (Dot(vecb, veca) * Dot(vecc, veca) <= 0)
				{
					return true;
				}
				else if ((myData.second > vecb.Magnitude()) || (myData.second > vecc.Magnitude()))
				{
					return true;
				}
			}
		}
		// ì‡ïîÇ…Ç¢ÇÈÇ©Ç«Ç§Ç©
		bool check = true;
		check &= CheckHit(sVertex[0], sVertex[1], myData.first);
		check &= CheckHit(sVertex[1], sVertex[2], myData.first);
		check &= CheckHit(sVertex[2], sVertex[3], myData.first);
		check &= CheckHit(sVertex[3], sVertex[0], myData.first);
		if (check)
		{
			return true;
		}
	}
	// â~VSéOäp
	auto tcol = std::dynamic_pointer_cast<TriangleCollision>(col);
	if (tcol != nullptr)
	{
		const std::array<int, 3> other = { 1,2,0 };
		const auto sVertex = tcol->GetVertex();
		const auto myData = GetCircleData();

		for (int i = 0; i < 3; i++)
		{
			auto veca = sVertex[other[i]] - sVertex[i];
			auto vecb = myData.first - sVertex[i];
			auto vecc = myData.first - sVertex[other[i]];

			auto d = Cross(veca, vecb) / veca.Magnitude();

			if (abs(d) <= myData.second)
			{
				if (Dot(vecb, veca) * Dot(vecc, veca) <= 0)
				{
					return true;
				}
				else if ((myData.second > vecb.Magnitude()) || (myData.second > vecc.Magnitude()))
				{
					return true;
				}
			}
		}

		bool check = true;
		check &= CheckHit(sVertex[0], sVertex[1], myData.first);
		check &= CheckHit(sVertex[1], sVertex[2], myData.first);
		check &= CheckHit(sVertex[2], sVertex[0], myData.first);
		if (check)
		{
			return true;
		}

	}
    return false;
}

bool CircleCollision::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	Vector2Flt& pos = owner_->GetPos();
	if (pos.x - rad_ < 0)
	{
		pos.x = rad_;
		UpDown = false;
	}
	else if (pos.x + rad_ > scrSize.x)
	{
		pos.x = scrSize.x - rad_;
		UpDown = false;
	}
	else if (pos.y - rad_ < 0)
	{
		pos.y = rad_;
		UpDown = true;
	}
	else if (pos.y + rad_ > scrSize.y)
	{
		pos.y = scrSize.y - rad_;
		UpDown = true;
	}
	else
	{
		return true;
	}
	return false;
}

const std::pair<Vector2Flt, float> CircleCollision::GetCircleData(void)
{
	std::pair<Vector2Flt, float> data;
	if (!owner_)
	{
		assert(!"SetVertexÇ≈owner_Ç™null");
		return data;
	}


	data.first = owner_->GetPos() + offset_;
	data.second = rad_;

    return data;
}

void CircleCollision::SetRadius(const float& rad)
{
	rad_ = rad;
}
