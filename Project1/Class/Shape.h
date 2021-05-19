#pragma once
#include <memory>
#include <vector>
#include "../common/Vector2.h"

enum class ShapeTag
{
	NON,
	Squeare,
	Circle
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

class Shape
{
public:
	Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col,const Vector2Flt& vec,const float& speed);

	virtual void Update(const float& delta, const Vector2& scrSize, const std::vector<std::shared_ptr<Shape>>&list, std::vector<InstanceData>& instanceData);

	void UpDate(const int& x, const int& y);

	virtual void Draw(void) = 0;
	virtual void Draw(const float& rate) = 0;
	virtual void Draw(const float& rate, Vector2Flt offSet);
	virtual void GetDrawSpace(Vector2& pos, Vector2& size);
	virtual bool CheckHitWall(const Vector2& scrSize, bool& UpDown) = 0;

	const int& GetDrawScreen(void);

	bool CheckHit(const std::weak_ptr<Shape>& shape);
	/// <summary>
	/// •`‰æ”ÍˆÍ‚ª‚©‚Ô‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©
	/// </summary>
	/// <param name="shape">“–‚½‚è”»’è‚µ‚½‚¢‘ŠŽè</param>
	/// <returns>true:“–‚½‚è</returns>
	bool CheckHitDrawSpace(const std::weak_ptr<Shape>& shape);
	/// <summary>
	/// •`‰æ”ÍˆÍ‚ª‚Ô‚Â‚©‚Á‚Ä‚¢‚éShape‚ª‚Ô‚Â‚©‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©
	/// </summary>
	/// <param name="shape">“–‚½‚è”»’è‚µ‚½‚¢‘ŠŽè</param>
	/// <returns>true:“–‚½‚è</returns>
	bool CheckHitCol(const std::weak_ptr<Shape>& shape);

	bool CheckHitScreen(const std::weak_ptr<Shape>& shape,bool isLeft);

	void SetIsDead(void);
	bool GetIsDead(void);

	void SetCol(const unsigned int& col);
	const unsigned int& GetCol(void)const;

	void RefVec(bool UpDown);

	void ScrDraw(const Vector2 offSet);

	void PreparaScreen(void);

protected:
	Vector2Flt pos_;
	Vector2Flt size_;
	Vector2Flt vec_;
	Vector2 scrSize_;
	Vector2 hitOffSet_;

	bool isDead_;
	float speed_;
	unsigned int col_;
	int screen_;

	ShapeTag tag_;
};

