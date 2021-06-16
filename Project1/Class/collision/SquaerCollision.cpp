#include <cassert>
#include <array>
#include "SquaerCollision.h"
#include "TriangleCollision.h"
#include "CircleCollision.h"
#include "../Shape.h"
#include "../Square.h"

SquaerCollision::SquaerCollision(const Vector2Flt& size, const Vector2Flt offset) :
	Collision(offset),size_(size)
{
}

COLLISION_TAG SquaerCollision::CollisionTag(void)
{
	return COLLISION_TAG::Square;
}

bool SquaerCollision::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	Vector2Flt& pos = std::dynamic_pointer_cast<Square>(owner_)->GetPos();
	if (pos.x < 0)
	{
		pos.x = 0;
		UpDown = false;
	}
	else if (pos.x + size_.x > scrSize.x)
	{
		pos.x = scrSize.x - size_.x;
		UpDown = false;
	}
	else if (pos.y < 0)
	{
		pos.y = 0;
		UpDown = true;
	}
	else if (pos.y + size_.y > scrSize.y)
	{
		pos.y = scrSize.y - size_.y;
		UpDown = true;
	}
	else
	{
		return true;
	}
	return false;
}

bool SquaerCollision::isHit(std::shared_ptr<Collision> col)
{
	auto CheckHit = [](const Vector2Flt& veca, const Vector2Flt& vecb, const Vector2Flt& point) {
		float tmp = Cross(Vector2Flt(vecb - veca), Vector2Flt(point - veca));
		if (tmp >= 0)
		{
			return true;
		}
		return false;
	};
	assert(col && "あたり判定をするコライダーがnullptr");
	// 矩形VS矩形
	auto scol = std::dynamic_pointer_cast<SquaerCollision>(col);
	if (scol != nullptr)
	{
		assert(owner_ && "owner_がnullptr");

		const auto myVertex = GetVertex();
		const auto sVertex = scol->GetVertex();

		for (const auto& vertex : sVertex)
		{
			bool check = true;
			check &= CheckHit(myVertex[0], myVertex[1], vertex);
			check &= CheckHit(myVertex[1], myVertex[2], vertex);
			check &= CheckHit(myVertex[2], myVertex[3], vertex);
			check &= CheckHit(myVertex[3], myVertex[0], vertex);
			if (check)
			{
				return true;
			}
		}
		for (const auto& vertex : myVertex)
		{
			bool check = true;
			check &= CheckHit(sVertex[0], sVertex[1], vertex);
			check &= CheckHit(sVertex[1], sVertex[2], vertex);
			check &= CheckHit(sVertex[2], sVertex[3], vertex);
			check &= CheckHit(sVertex[3], sVertex[0], vertex);
			if (check)
			{
				return true;
			}
		}
	}
	auto tcol = std::dynamic_pointer_cast<TriangleCollision>(col);
	if (tcol != nullptr)
	{
		assert(owner_ && "owner_がnullptr");

		const auto myVertex = GetVertex();
		const auto sVertex = tcol->GetVertex();

		for (const auto& vertex : sVertex)
		{
			bool check = true;
			check &= CheckHit(myVertex[0], myVertex[1], vertex);
			check &= CheckHit(myVertex[1], myVertex[2], vertex);
			check &= CheckHit(myVertex[2], myVertex[3], vertex);
			check &= CheckHit(myVertex[3], myVertex[0], vertex);
			if (check)
			{
				return true;
			}
		}
		for (const auto& vertex : myVertex)
		{
			bool check = true;
			check &= CheckHit(sVertex[0], sVertex[1], vertex);
			check &= CheckHit(sVertex[1], sVertex[2], vertex);
			check &= CheckHit(sVertex[2], sVertex[0], vertex);
			if (check)
			{
				return true;
			}
		}
	}
	auto ccol = std::dynamic_pointer_cast<CircleCollision>(col);
	if (ccol != nullptr)
	{
		// 交差しているかどうか
		const std::array<int, 4> other = { 1,2,3,0 };
		const auto myVertex = GetVertex();
		const auto cData = ccol->GetCircleData();

		for (int i = 0; i < 4; i++)
		{
			auto veca = myVertex[other[i]] - myVertex[i];
			auto vecb = cData.first - myVertex[i];
			auto vecc = cData.first - myVertex[other[i]];

			auto d = Cross(veca, vecb) / veca.Magnitude();

			if (abs(d) <= cData.second)
			{
				if (Dot(vecb, veca) * Dot(vecc, veca) <= 0)
				{
					return true;
				}
				else if ((cData.second > vecb.Magnitude()) || (cData.second > vecc.Magnitude()))
				{
					return true;
				}
			}
		}
		// 内部にいるかどうか
		bool check = true;
		check &= CheckHit(myVertex[0], myVertex[1], cData.first);
		check &= CheckHit(myVertex[1], myVertex[2], cData.first);
		check &= CheckHit(myVertex[2], myVertex[3], cData.first);
		check &= CheckHit(myVertex[3], myVertex[0], cData.first);
		if (check)
		{
			return true;
		}
	}
	return false;
}

const Rect SquaerCollision::GetRect(void)
{
	if (!owner_)
	{
		return Rect();
	}
	return Rect(owner_->GetPos(), size_);
}

const std::vector<Vector2Flt> SquaerCollision::GetVertex(void)
{
	std::vector<Vector2Flt> vec;
	if (!owner_)
	{
		assert(!"SetVertexでowner_がnull");
		return vec;
	}
	const auto& pos = owner_->GetPos() + offset_;
	vec.emplace_back(Vector2Flt{ pos.x,pos.y });
	vec.emplace_back(Vector2Flt{ pos.x + size_.x,pos.y });
	vec.emplace_back(Vector2Flt{ pos.x + size_.x,pos.y + size_.y });
	vec.emplace_back(Vector2Flt{ pos.x ,pos.y + size_.y });
	return vec;
}

void SquaerCollision::SetSize(const Vector2Flt& size)
{
	size_ = size;
}

