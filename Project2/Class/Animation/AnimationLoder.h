#pragma once
#include <map>
#include <vector>
#include <utility>
#include <string>
#include "../XML/RapidXml/rapidxml.hpp"
#include "../Object/characterID.h"
#include "Anim_ID.h"


struct AnimDataS
{
	std::string flameData;
	std::string subscriptData;
};

struct AnimInfoS
{
	std::string width = "";
	std::string height = "";
	std::string widthCnt = "";
	std::string heightCnt = "";
	std::string loop = "";
	std::string widthOffset = "";
	std::string heigthOffset = "";
	std::string source = "";
};

/// <summary>
/// アニメーションのTMX読み込みクラス
/// std::stringで情報は持ってる
/// </summary>
class AnimationLoder
{
public:
	AnimationLoder();
	~AnimationLoder() = default;
	bool LoadAnimTmx(const std::string& filepath);


	const std::map<Anim_ID, std::string>& GetAnimID(void);
	const AnimInfoS& GetAnimInfoS(Anim_ID animID);
	const AnimDataS& GetAnimDataS(Anim_ID animid);
private:
	void VersionMap(void);

	rapidxml::xml_document<> TmxDoc_;

	rapidxml::xml_node<>* tmx_orign_node_;		// 一番最初のノード 基本的にここからアクセスする

	std::map<std::string, int> version_;

	std::map<Anim_ID, std::string> animID_;
	// animationごとの画像関係データ
	std::map<std::string, AnimInfoS> info_;
	// std::map<animID,AnimInfo>>
	std::map<std::string, AnimDataS> animDataS_;
};

