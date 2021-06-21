#pragma once
#include <list>
#include <map>
#include <string>
#include <utility>
#include "../Object/characterID.h"
#include "../Animation/Anim_ID.h"

struct AnimData
{
	std::list<int> flameData;
	std::list<int> subscriptData;
};

struct AnimInfo
{
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int widthCnt = 0;
	unsigned int heightCnt = 0;
	int loop = 0;
	std::string source = "";
};

#define lpAnimMng AnimationMng::GetInstance()
using Animation = std::pair<AnimInfo,AnimData>;

class AnimationMng
{
public:
	static AnimationMng& GetInstance()
	{
		static AnimationMng s_instance_;
		return s_instance_;
	}
	bool LoadAnimTmx(const std::string& filepath, char_ID id);
private:
	AnimationMng();
	~AnimationMng() = default;
	// キャラクターの種別とアニメーション種別をキーにしたアニメーション関連データ
	std::map<char_ID, std::map<Anim_ID,Animation>> animData_;
};
