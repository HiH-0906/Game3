#include "Shape.h"
#include "../common/Vector2.h"

class Square :
	public Shape
{
public:
	Square(const Vector2Flt&& pos, const Vector2Flt&& size, const unsigned int& col, const Vector2Flt& vec, const float& speed, const float& rate = 1.0f, const Vector2Flt& offSet = {});

	void Update(const float& delta, const Vector2& scrSize)override final;

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;

	bool CheckHitWall(const Vector2& scrSize)override final;

private:

};