#include <type_traits>
#include "Anim_ID.h"


Anim_ID begin(Anim_ID)
{
	return Anim_ID::IDLE;
}

Anim_ID end(Anim_ID)
{
	return Anim_ID::MAX;
}

Anim_ID operator*(Anim_ID id)
{
	return id;
}

Anim_ID operator++(Anim_ID& id)
{
	return id = static_cast<Anim_ID>(std::underlying_type<Anim_ID>::type(id) + 1);
}