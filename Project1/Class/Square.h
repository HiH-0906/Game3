#include "Shape.h"
#include "../common/Vector2.h"

class Square :
	public Shape
{
public:
	Square(const float& posX, const float& posY, const float& sizeX, const float& sizeY, const unsigned int& col);
	Square(const Vector2Flt&& pos, const Vector2Flt&& size,const unsigned int& col);

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;

private:

};