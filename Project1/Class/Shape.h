#pragma once
#include "../common/Vector2.h"

class Shape
{
public:
	Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col,const Vector2Flt& vec,const float& speed, const float& rate, const Vector2Flt& offSet);

	virtual void Update(const float& delta,const Vector2& scrSize);

	virtual void Draw(void) = 0;
	virtual void Draw(const float& rate) = 0;
	virtual void Draw(const float& rate, Vector2Flt offSet);

	virtual bool CheckHitWall(const Vector2& scrSize) = 0;

	void RefVec(void);

	Vector2Flt pos_;
	Vector2Flt size_;
	Vector2Flt offSet_;
	Vector2Flt vec_;

	float speed_;
	float rate_;
	int col_;

private:
};

