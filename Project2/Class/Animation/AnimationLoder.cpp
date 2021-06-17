#include <cassert>
#include <type_traits>
#include "AnimationLoder.h"
#include "../XML/RapidXml/rapidxml.hpp"
#include "../XML/RapidXml/rapidxml_utils.hpp"


AnimationLoder::AnimationLoder()
{
	VersionMap();
	tmx_orign_node_ = nullptr;
}

bool AnimationLoder::LoadAnimTmx(const std::string& filepath, character_ID id)
{
	// Tmx関連準備
	rapidxml::file<> file(filepath.c_str());
	TmxDoc_.parse<0>(file.data());

	tmx_orign_node_ = TmxDoc_.first_node("anim");
	if (!tmx_orign_node_)
	{
		assert(!"Tmxのfirst_node(anim)がない");
		return false;
	}
	// versiton対応チェック
	if (version_.count(tmx_orign_node_->first_attribute("version")->value()) == 0)
	{
		assert(!"AnimVersion未対応");
		return false;
	}
	charID_[id] = tmx_orign_node_->first_node("character")->first_attribute("characterkey")->value();
	anim_ID animid = anim_ID::RUN;
	for (rapidxml::xml_node<>* animNode = tmx_orign_node_->first_node("character")->first_node("animation"); animNode != nullptr; animNode = animNode->next_sibling())
	{
		animID_[animid] = animNode->first_attribute("animkey")->value();
		info_[animID_[animid]].width = std::atoi(animNode->first_attribute("width")->value());
		info_[animID_[animid]].height = std::atoi(animNode->first_attribute("height")->value());
		info_[animID_[animid]].widthCnt = std::atoi(animNode->first_attribute("tilecountwidth")->value());
		info_[animID_[animid]].heightCnt = std::atoi(animNode->first_attribute("tilecountheight")->value());
		info_[animID_[animid]].loop = std::atoi(animNode->first_attribute("loop")->value());
		info_[animID_[animid]].source = animNode->first_attribute("source")->value();
		auto flamedata = animNode->first_node("flamedata");
		if (!flamedata)
		{
			assert(!"flamedataNodeがありません");
			return false;
		}
		animData_[charID_[id]][animID_[animid]].flameData = flamedata->first_node()->value();
		auto subscriptdata = animNode->first_node("subscriptdata");
		if (!subscriptdata)
		{
			assert(!"subscriptdataNodeがありません");
			return false;
		}
		animData_[charID_[id]][animID_[animid]].subscriptData = subscriptdata->first_node()->value();
	}
	return true;
}

void AnimationLoder::VersionMap(void)
{
	version_["1.0"] = 1;
}

anim_ID operator++(anim_ID& key)
{
	return key = static_cast<anim_ID>(std::underlying_type<anim_ID>::type(key) + 1);
}
