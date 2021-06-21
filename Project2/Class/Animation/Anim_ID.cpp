#include <type_traits>
#include "Anim_ID.h"


Anim_ID begin(Anim_ID)
{
	return Anim_ID::IDLE;
}

Anim_ID operator++(Anim_ID& key)
{
	return key = static_cast<Anim_ID>(std::underlying_type<Anim_ID>::type(key) + 1);
}