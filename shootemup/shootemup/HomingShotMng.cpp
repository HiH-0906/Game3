#include <DxLib.h>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "HomingShotMng.h"
#include "HomingShot.h"
#include "Trail.h"

namespace
{
	std::vector<VERTEX2D> vertices_;
	int handle_;
	Vector2f GetOrthogonalVector(const Vector2f& v) {
		return { -v.y,v.x };
	}
}

void HomingShotMng::AddHoming(std::shared_ptr<HomingShot> shot)
{
	shots_.push_back(shot);
}

void HomingShotMng::Update(void)
{
	auto itr = std::remove_if(shots_.begin(), shots_.end(), [](std::shared_ptr<HomingShot> shot) {return !shot->isActive; });
	shots_.erase(itr, shots_.end());
	if (shots_.size() == 0)
	{
		vertices_.clear();
		indices_.clear();
	}
	for (const auto& shot:shots_)
	{
		shot->Update(enemyPos_);
	}
}

void HomingShotMng::Draw(void)
{
	if (!vertices_.empty() && !indices_.empty()) {
		DrawPolygonIndexed2D(vertices_.data(), vertices_.size(), indices_.data(), indices_.size() / 3, handle_, true);
	}
	vertices_.clear();
	indices_.clear();
	for (const auto& shot : shots_)
	{
		AddTrail(shot->trail_,shot->islaser);
	}
}

void HomingShotMng::AddTrail(const Trail& trail, bool flag)
{
	if (trail.history_.empty())
	{
		return;
	}
	float thickness = 64.0f;
	Position2f lastPos = trail.history_.front();
	Vector2f lastRv = Vector2f::ZERO;
	float div = trail.history_.size();
	float u = 0.0f;
	// サイズを記録
	size_t lastVertSize = vertices_.size();
	for (const auto& pos : trail.history_)
	{
		Vector2f v = pos - lastPos;
		Vector2f rv = {};
		if (v == Vector2f::ZERO)
		{
			lastPos = pos;
			continue;
		}
		if (v != Vector2f::ZERO)
		{
			rv = GetOrthogonalVector(v).Normalized();
			if (isnan(rv.x))
			{
				lastPos = pos;
				continue;
			}
		}
		Vector2f rightV = rv;
		if (lastRv != Vector2f::ZERO)
		{
			if (isnan(lastRv.x))
			{
				assert(0);
			}

			rightV = lastRv;
			if (rightV == Vector2f::ZERO)
			{
				lastPos = pos;
				continue;
			}
			rightV.Normalize();
		}
		assert(!isnan(rightV.x));
		if (flag)
		{
			thickness = 16.0f;
		}

		Vector2f headV = rightV * (thickness * 0.5f);
		auto p1 = lastPos - headV;
		auto p2 = lastPos + headV;
		if (!flag)
		{
			thickness *= 0.9f;
		}
		headV = rv * (thickness * 0.5f);

		VERTEX2D vert;
		vert.pos.x = p1.x;
		vert.pos.y = p1.y;
		vert.pos.z = 0;
		vert.u = u;
		vert.v = 0.0f;
		vert.rhw = 1.0f;
		vertices_.push_back(vert);
		vert.pos.x = p2.x;
		vert.pos.y = p2.y;
		vert.pos.z = 0;
		vert.u = u;
		vert.v = 1.0f;
		vert.rhw = 1.0f;
		u += 1.0f / div;
		vertices_.push_back(vert);

		lastPos = pos;
		lastRv = rv;
	}

	if (vertices_.empty())
	{
		return;
	}
	size_t vert_num = vertices_.size() - lastVertSize;
	if (vert_num == 0)
	{
		return;
	}
	std::vector<unsigned short> indices((vert_num / 2 - 1) * 2 * 3);
	unsigned short index = lastVertSize;
	for (int i = 0; i < indices.size(); i += 6) {
		//三角形1
		indices[i] = index;
		indices[i + 1] = index + 2;
		indices[i + 2] = index + 1;

		//三角形2
		indices[i + 3] = index + 1;
		indices[i + 4] = index + 2;
		indices[i + 5] = index + 3;
		index += 2;
	}
	std::copy(indices.begin(), indices.end(), std::back_inserter(indices_));
}

HomingShotMng::HomingShotMng(Position2f& enemyPos):
	enemyPos_(enemyPos)
{
	handle_ = LoadGraph("img/arrow2.png");
}

HomingShotMng::~HomingShotMng()
{
	DeleteGraph(handle_);
}
