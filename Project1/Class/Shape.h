#pragma once
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "../common/Vector2.h"

enum class ShapeTag
{
	NON,
	Squeare,
	Circle,
	Triangle,
	Carrot
};


struct InstanceData
{
	ShapeTag tag = ShapeTag::NON;
	Vector2Flt pos = {};
	Vector2Flt size = {};
	unsigned int col = 0;
	Vector2Flt vec = {};
	float speed = 0.0f;
};
class Collision;

class Shape
{
public:
	Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col,const Vector2Flt& vec,const float& speed);

	void SetCollisionOwner(std::shared_ptr<Shape> owner);

	void HitUpdate(const float& delta,const std::vector<std::shared_ptr<Shape>>& list);

	virtual void Update(const float& delta, const Vector2& scrSize);

	virtual void Update(const int& x, const int& y);

	virtual void HitAction(std::shared_ptr<Shape> shape) = 0;

	virtual void Draw(void) = 0;
	virtual void Draw(const float& rate) = 0;
	virtual void Draw(const float& rate, Vector2Flt offSet);
	bool CheckHitWall(const Vector2& scrSize, bool& UpDown);

	bool CheckHit(const std::weak_ptr<Shape>& shape);

	void SetIsDead(void);
	bool GetIsDead(void);


	const Vector2Flt GetVec(void);
	void SetCol(const unsigned int& col);
	void SetVec(const Vector2Flt& vec);
	void SetSpeed(const float& speed);
	const float& GetIntervel(void)const;
	void SetInterval(const float& inter);
	const unsigned int& GetCol(void)const;

	Vector2Flt& GetPos(void);
	const Vector2Flt& GetSize(void); 

	void RefVec(bool UpDown);
	void ReSetVec(void);

	const ShapeTag& GetTag()const;

protected:
	Vector2Flt pos_;
	Vector2Flt size_;
	Vector2Flt vec_;
	Vector2Flt defvec_;

	float interval_;

	std::vector<std::shared_ptr<Collision>> colls_;

	bool isDead_;
	float speed_;
	unsigned int col_;
	unsigned int defCol_;

	std::vector<std::weak_ptr<Shape>> hitShapes_;

	ShapeTag tag_;
};

