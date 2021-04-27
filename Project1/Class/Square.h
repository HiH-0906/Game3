#include "Shape.h"
#include "../common/Vector2.h"

class Square :
	public Shape
{
public:
	Square(const int& posX, const int& posY, const int& sizeX, const int& sizeY,const unsigned int& col);
	Square(const Vector2& pos, const Vector2& size);

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate,const Vector2& offSet)override final;
	
private:

};