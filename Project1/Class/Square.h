#include "Shape.h"
#include "../common/Vector2.h"

class Square :
	public Shape
{
public:
	Square(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed);

	void Update(const float& delta, const Vector2& scrSize, const std::vector<std::shared_ptr<Shape>>& list,std::vector<InstanceData>& instanceData)override final;

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;


	bool CheckHitWall(const Vector2& scrSize, bool& UpDown)override final;
	
private:

};