#include <cassert>
#include "TriangleCollision.h"
#include "SquaerCollision.h"
#include "CircleCollision.h"
#include "../Triangle.h"

TriangleCollision::TriangleCollision(const std::array<Vector2Flt, 3>& vertex,const Vector2Flt offset) :
	Collision(offset),vertex_(vertex)
{
}

COLLISION_TAG TriangleCollision::CollisionTag(void)
{
	return COLLISION_TAG::Triangle;
}

bool TriangleCollision::isHit(std::shared_ptr<Collision> col)
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

	// éOäpVSéOäp
	auto tcol = std::dynamic_pointer_cast<TriangleCollision>(col);
	if (tcol != nullptr)
	{
		assert(owner_ && "owner_Ç™nullptr");

		const auto myVertex = GetVertex();
		const auto sVertex = tcol->GetVertex();

		if (CheckSeparationLine(myVertex, sVertex))
		{
			return true;
		}
		else
		{
			for (const auto& vertex : sVertex)
			{
				bool check = true;
				check &= CheckHit(myVertex[0], myVertex[1], vertex);
				check &= CheckHit(myVertex[1], myVertex[2], vertex);
				check &= CheckHit(myVertex[2], myVertex[0], vertex);
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
	}


	// éOäpVSãÈå`
	auto scol = std::dynamic_pointer_cast<SquaerCollision>(col);
	if (scol != nullptr)
	{
		assert(owner_ && "owner_Ç™nullptr");

		const auto myVertex = GetVertex();
		const auto sVertex = scol->GetVertex();

		for (const auto& vertex : sVertex)
		{
			bool check = true;
			check &= CheckHit(myVertex[0], myVertex[1], vertex);
			check &= CheckHit(myVertex[1], myVertex[2], vertex);
			check &= CheckHit(myVertex[2], myVertex[0], vertex);
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
	// éOäpVSâ~
	auto ccol = std::dynamic_pointer_cast<CircleCollision>(col);
	if (ccol != nullptr)
	{
		// åç∑ÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
		const std::array<int, 3> other = { 1,2,0 };
		const auto myVertex = GetVertex();
		const auto cData = ccol->GetCircleData();

		for (int i = 0; i < 3; i++)
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
		// íÜÇ…Ç¢ÇÈÇ©Ç«Ç§Ç©
		bool check = true;
		check &= CheckHit(myVertex[0], myVertex[1], cData.first);
		check &= CheckHit(myVertex[1], myVertex[2], cData.first);
		check &= CheckHit(myVertex[2], myVertex[0], cData.first);
		if (check)
		{
			return true;
		}

	}
	return false;
}

const std::vector<Vector2Flt> TriangleCollision::GetVertex(void)
{
	std::vector<Vector2Flt> vertex;
	vertex.resize(3);

	if (!owner_)
	{
		assert(!"SetVertexÇ≈owner_Ç™null");
		return vertex;
	}

	const auto& pos = (owner_)->GetPos() + offset_;


	vertex[0] = pos + vertex_[0];
	vertex[1] = pos + vertex_[1];
	vertex[2] = pos + vertex_[2];

	return vertex;
}

bool TriangleCollision::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	auto CheckHit = [](const Vector2Flt& veca, const Vector2Flt& vecb, const Vector2Flt& point) {
		float tmp = Cross(Vector2Flt(vecb - veca), Vector2Flt(point - veca));
		if (tmp >= 0)
		{
			return true;
		}
		return false;
	};

	
	Vector2Flt& pos = owner_->GetPos();
	const std::array<Vector2Flt, 3>& myVertex = { vertex_[0] + pos,vertex_[1] + pos ,vertex_[2] + pos };
	std::vector<Vector2Flt> sVertex;

	sVertex.emplace_back(Vector2Flt{});
	sVertex.emplace_back(Vector2Flt{ static_cast<float>(scrSize.x),0.0f });
	sVertex.emplace_back(Vector2Flt{ static_cast<float>(scrSize.x) ,static_cast<float>(scrSize.y) });
	sVertex.emplace_back(Vector2Flt{ 0.0f,static_cast<float>(scrSize.y) });

	for (const auto& vertex : myVertex)
	{
		bool check = true;
		check &= CheckHit(sVertex[0], sVertex[1], vertex);
		check &= CheckHit(sVertex[1], sVertex[2], vertex);
		check &= CheckHit(sVertex[2], sVertex[3], vertex);
		check &= CheckHit(sVertex[3], sVertex[0], vertex);
		if (!check)
		{
			if (vertex.x < 0)
			{
				pos.x = std::abs(vertex.x - pos.x);
				UpDown = false;
			}
			else if (vertex.x >= static_cast<float>(scrSize.x))
			{
				pos.x = static_cast<float>(scrSize.x) - (vertex.x - pos.x);
				UpDown = false;
			}
			if (vertex.y < 0)
			{
				pos.y = std::abs(vertex.y - pos.y);
				UpDown = true;
			}
			else if (vertex.y > static_cast<float>(scrSize.y))
			{
				pos.y = static_cast<float>(scrSize.y) - (vertex.y - pos.y);
				UpDown = true;
			}
			return false;
		}
	}
	return true;
}

bool TriangleCollision::CheckSeparationLine(const std::vector<Vector2Flt>& myvertex, const std::vector<Vector2Flt>& svertex)
{
	const std::array<int, 3> other = { 1,2,0 };
	const std::array<std::vector<Vector2Flt>, 3> triVec = { myvertex,svertex,myvertex };
	for (int t = 0; t < 2; t++)
	{
		const std::vector<Vector2Flt> vertexa = triVec[t];
		const std::vector<Vector2Flt> vertexb = triVec[t + 1];
		for (int i = 0; i < 3; i++)
		{

			Vector2Flt veca = vertexa[i] - vertexa[other[i]];
			veca.Nomalize();
			Vector2Flt sepVec(veca.y, -veca.x);

			float s1min = Dot(sepVec, vertexa[i]);
			float s1max = Dot(sepVec, vertexa[other[i]]);
			if (s1min > s1max)
			{
				float tmp = s1min;
				s1min = s1max;
				s1max = tmp;
			}

			float s2min = Dot(sepVec, vertexb[0]);
			float s2max = Dot(sepVec, vertexb[1]);
			if (s2min > s2max)
			{
				float tmp = s2min;
				s2min = s2max;
				s2max = tmp;
			}
			float d3 = Dot(sepVec, vertexb[2]);
			if (d3 < s2min)
			{
				s2min = d3;
			}
			else if (d3 > s2max)
			{
				s2max = d3;
			}
			if ((s2min <= s1min && s1min <= s2max) ||
				(s2min <= s1max && s1max <= s2max) ||
				(s1min <= s2min && s2min <= s1max) ||
				(s1min <= s2max && s2max <= s1max))
			{
				continue;
			}
			return false;
		}
	}
	return true;
}
