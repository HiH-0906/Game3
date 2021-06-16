#include <DxLib.h>
#include "Star.h"
#include "collision/TriangleCollision.h"

Star::Star(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	Shape(pos, size, col, vec, speed)
{
	Vector2Flt tmp = { size.x / 3.0f ,size.y / 3.0f };
	vertexs_[0][0] = { size.x / 2.0f,0.0f };
	vertexs_[0][1] = { size.x - tmp.x ,tmp.y };
	vertexs_[0][2] = { tmp.x,tmp.y };

	float test = (size.y / 5.0f) * 2;

	vertexs_[1][0] = { size.x - tmp.x,tmp.y };
	vertexs_[1][1] = { size.x , tmp.y };
	vertexs_[1][2] = { size.x - tmp.x,size.y - test };

	vertexs_[2][0] = { size.x - tmp.x,size.y - size.y / 2.0f };
	vertexs_[2][1] = { size.x - size.x / 10.0f,size.y };
	vertexs_[2][2] = { size.x / 2.0f,size.y - size.y / 4.0f };

	vertexs_[3][0] = { tmp.x,size.y - size.y / 2.0f };
	vertexs_[3][1] = { size.x / 2.0f,size.y - size.y / 4.0f };
	vertexs_[3][2] = { size.x / 10.0f,size.y };

	vertexs_[4][0] = {0.0f,tmp.y};
	vertexs_[4][1] = {tmp.x,tmp.y};
	vertexs_[4][2] = { tmp.x,size.y - test };

	for (const auto& vertex : vertexs_)
	{
		colls_.emplace_back(std::make_shared<TriangleCollision>(vertex));
	}

}

void Star::Draw(void)
{
	auto ConvertVector2 = [](std::array<Vector2Flt, 3>& poss)->std::array<Vector2, 3> {
		std::array<Vector2, 3> reposs;
		reposs[0] = static_cast<Vector2>(poss[0]);
		reposs[1] = static_cast<Vector2>(poss[1]);
		reposs[2] = static_cast<Vector2>(poss[2]);
		return reposs;
	};
	for (auto& svertex : vertexs_)
	{
		std::array<Vector2, 3> vertex = ConvertVector2(svertex);

		Vector2 pos = static_cast<Vector2>(pos_);

		DrawTriangle(pos.x + vertex[0].x, pos.y + vertex[0].y, pos.x + vertex[1].x, pos.y + vertex[1].y, pos.x + vertex[2].x, pos.y + vertex[2].y, col_, true);
	}

	Vector2 size = static_cast<Vector2>(size_);
	Vector2 pos = static_cast<Vector2>(pos_);

	DrawBox(pos.x + size.x / 3, pos.y + size.y / 3, pos.x + size.x - size.x / 3, pos.y + size.y - size.y / 4, col_, true);
}

void Star::Draw(const float& rate)
{
}

void Star::Draw(const float& rate, Vector2Flt offSet)
{
}

void Star::HitAction(std::shared_ptr<Shape> shape)
{
	shape->SetSpeed(250.0f);
}
