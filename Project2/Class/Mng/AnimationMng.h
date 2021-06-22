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
	std::list<int> subscript;
};

struct AnimInfo
{
	int width = 0;
	int height = 0;
	int widthCnt = 0;
	int heightCnt = 0;
	int loop = 0;
	std::string source = "";
	std::string imgKey = "";
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
	/// <summary>
	/// 引数で指定されたキャラのアニメーションに関するデータ
	/// 指定したキャラ、もしくは指定したアニメーションが未登録の場合中身のないAnimationが返ってくる
	/// </summary>
	/// <param name="cID">獲得したいキャラ</param>
	/// <param name="aID">獲得したいアニメーション</param>
	/// <returns>アニメーション関連データ</returns>
	const Animation GetAnimationData(char_ID cID, Anim_ID aID);
	const int GetAnimImag(char_ID cID, Anim_ID aID, int& elapsed, int& loopNum);
private:
	AnimationMng();
	~AnimationMng() = default;
	// キャラクターの種別とアニメーション種別をキーにしたアニメーション関連データ
	std::map<char_ID, std::map<Anim_ID,Animation>> animData_;
};
