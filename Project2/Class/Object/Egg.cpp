#include "Egg.h"
#include "Player.h"
#include "../UI/PlayerUI.h"
#include "../Mng/ImageMng.h"
#include "../Mng/CollisionMng.h"
#include "../collision/SquaerCollision.h"

Egg::Egg(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, TeamTag tag, InputType type, std::shared_ptr<PlayerUI> owner, std::list<std::shared_ptr<Object>>& list) :
	Object(pos, size, oID, tag), objList_(list),owner_(owner), type_(type)
{
	isActive_ = false;
	imageKey_ = "Egg";
	time_ = 0.0;
	lpImageMng.GetID(imageKey_, "Image/UI/Egg.png", { 32,32 }, { 1,1 });
}

void Egg::InstancePlayer(void)
{
	auto obj = std::make_shared<Player>(Vector2Flt{ 500.0f,100.0f }, Vector2{ 0,0 },
		Object_ID::Pawn, 20, teamTag_, owner_.lock()
		, type_);
	objList_.emplace_back(obj);

	Vector2Flt size = static_cast<Vector2Flt>(obj->GetSize());
	auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
	col->SetOwner(obj);
	lpCollisionMng.RegistrationCol(col);

	isDead_ = true;
}

void Egg::SetActive(const double& time)
{
	isActive_ = true;
	time_ = time;
}

void Egg::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
	if (!isActive_)
	{
		return;
	}
	time_ -= delta;
	if (time_ <= 0)
	{
		InstancePlayer();
	}
}
