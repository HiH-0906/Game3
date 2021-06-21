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
		chengeCsvToList(data.subscriptData, dataS.subscriptData);
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
	}
	return true;
}

AnimationMng::AnimationMng()
{
}
