#include <DxLib.h>
#include "Bullet.h"
#include "../Mng/ImageMng.h"
#include "../Mng/SceneMng.h"

Bullet::Bullet(const Vector2Flt& pos, const Vector2& size,const int& damage, const Object_ID oID, const Vector2Flt& speed, bool reverseXFlag,TeamTag tag):
	Object(pos,size,oID,tag), speed_(speed),damage_(damage)
{
	reverseXFlag_ = reverseXFlag;
	lpImageMng.GetID("Bullet", "Image/player/ChickenBullet.png", Vector2{ 32,32 }, Vector2{ 1,3 });
	imageKey_ = "Bullet";
	animMax_ = 3;
	animFlam_ = 5;
}

Bullet::~Bullet()
{
}

void Bullet::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
	pos_ += speed_;
	Vector2 checkPos = static_cast<Vector2>(pos_);
	const auto& ScrSize = lpSceneMng.GetScreenSize();
	if (checkPos.x<-(size_.x / 2) || checkPos.x>ScrSize.x + (size_.x / 2) || checkPos.y<-(size_.y / 2) || checkPos.y>ScrSize.y + (size_.y / 2))
	{
		isAlive_ = false;
	}
}

void Bullet::HitCollision(std::shared_ptr<Object> otehr)
{
	if (otehr->GetTeamTag() != teamTag_)
	{
		otehr->AddDamage(damage_);
		isAlive_ = false;
	}
}
