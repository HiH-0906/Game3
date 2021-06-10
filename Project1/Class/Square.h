#include "Shape.h"
#include "../common/Vector2.h"

class Square :
	public Shape
{
public:
	Square(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed);

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;

	void HitAction(std::shared_ptr<Shape> shape)override;
	
	const Vector2Flt& GetSize(void)const;
	void SetSize(const Vector2Flt& size);
private:
	int tmp;
};