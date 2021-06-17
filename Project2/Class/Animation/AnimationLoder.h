#pragma once
#include <map>
#include <vector>
#include <utility>
#include <string>
#include "../XML/RapidXml/rapidxml.hpp"
#include "../characterID.h"


enum class anim_ID
{
	RUN,
	MAX,
};

anim_ID operator++(anim_ID& key);

struct AnimData
{
	std::string flameData;
	std::string subscriptData;
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

class AnimationLoder
{
public:
	AnimationLoder();
	~AnimationLoder() = default;
	bool LoadAnimTmx(const std::string& filepath, character_ID id);
private:
	void VersionMap(void);

	rapidxml::xml_document<> TmxDoc_;

	rapidxml::xml_node<>* tmx_orign_node_;		// 一番最初のノード 基本的にここからアクセスする

	std::map<std::string, int> version_;

	std::map<character_ID, std::string> charID_;
	std::map<anim_ID, std::string> animID_;
	std::map<std::string, AnimInfo> info_;
	// std::pair<charID_,std::pair<animID,AnimInfo>>
	std::map<std::string, std::map<std::string, AnimData>> animData_;
};

