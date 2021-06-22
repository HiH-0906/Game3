#include <cassert>
#include <sstream>
#include <memory>
#include "AnimationMng.h"
#include "../Animation/AnimationLoder.h"
#include "../Mng/ImageMng.h"

bool AnimationMng::LoadAnimTmx(const std::string& filepath, char_ID id)
{
	auto chengeInfoS = [](AnimInfo& info,const AnimInfoS& infoS) {
		info.width = std::atoi(infoS.width.c_str());
		info.height = std::atoi(infoS.height.c_str());
		info.widthCnt = std::atoi(infoS.widthCnt.c_str());
		info.heightCnt = std::atoi(infoS.heightCnt.c_str());
		info.loop = std::atoi(infoS.loop.c_str());
		info.source = infoS.source;
	};
	auto chengeCsvToList = [](std::list<int>& list, const std::string str){
		// éÊÇËèoÇ≥ÇÍÇÈstringÇÃàÍéûï€ë∂êÊ
		std::string dataStr;
		std::stringstream sstr(str);
		while (std::getline(sstr, dataStr, ','))
		{
			list.push_back(std::atoi(dataStr.c_str()));
		}
	};
	auto chengeAnimDataS = [chengeCsvToList](AnimData& data, const AnimDataS& dataS) {
		chengeCsvToList(data.flameData, dataS.flameData);
		chengeCsvToList(data.subscript, dataS.subscriptData);
	};

	if (animData_.count(id) != 0)
	{
		// assert(!"ìoò^çœÇ›ID");
		return true;
	}
	std::unique_ptr<AnimationLoder> loder = std::make_unique<AnimationLoder>();
	if (!loder->LoadAnimTmx(filepath))
	{
		assert(!"AnimTmxì«Ç›çûÇ›é∏îs");
		return false;
	}
	for (const auto& animid : loder->GetAnimID())
	{
		auto infoS = loder->GetAnimInfoS(animid.first);
		chengeInfoS(animData_[id][animid.first].first, infoS);
		auto dataS = loder->GetAnimDataS(animid.first);
		chengeAnimDataS(animData_[id][animid.first].second, dataS);
		animData_[id][animid.first].first.imgKey = infoS.source;
		const auto& info = animData_[id][animid.first].first;
		lpImageMng.GetID(info.imgKey, info.source.c_str(), Vector2{ info.width / info.widthCnt,info.height / info.heightCnt }, Vector2{ info.widthCnt, info.heightCnt });
	}
	
	return true;
}

const Animation AnimationMng::GetAnimationData(char_ID cID, Anim_ID aID)
{
	if (animData_.count(cID) == 0)
	{
		assert(!"ñ¢ìoò^ÉLÉÉÉâ");
		return Animation{};
	}
	if (animData_.count(cID) == 0)
	{
		assert(!"ñ¢ìoò^ÉAÉjÉÅÅ[ÉVÉáÉì");
		return Animation{};
	}
	return animData_[cID][aID];
}

const int AnimationMng::GetAnimImag(char_ID cID, Anim_ID aID, int& elapsed,int& loopNum)
{
	if (animData_.count(cID) == 0)
	{
		assert(!"ñ¢ìoò^ÉLÉÉÉâ");
		return  -1;
	}
	if (animData_[cID].count(aID) == 0)
	{
		assert(!"ñ¢ìoò^ÉAÉjÉÅÅ[ÉVÉáÉì");
		return -1;
	}
	int elapsedCnt = 0;
	auto subscriptData = animData_[cID][aID].second.subscript.begin();

	for (const auto& elapsedData : animData_[cID][aID].second.flameData)
	{
		elapsedCnt += elapsedData;
		if (elapsed < elapsedCnt)
		{
			return lpImageMng.GetID(animData_[cID][aID].first.imgKey)[*subscriptData];
		}
		subscriptData++;
	}
	if (animData_[cID][aID].first.loop < 0 || animData_[cID][aID].first.loop > loopNum)
	{
		elapsed = 0;
		loopNum++;
		return lpImageMng.GetID(animData_[cID][aID].first.imgKey)[*animData_[cID][aID].second.subscript.begin()];
	}
	else
	{
		return lpImageMng.GetID(animData_[cID][aID].first.imgKey)[*(--animData_[cID][aID].second.subscript.end())];
	}
}

AnimationMng::AnimationMng()
{
}
