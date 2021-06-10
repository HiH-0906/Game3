#pragma once
#include <utility>
#include <vector>
#include <map>
#include <string>
#include "XML/TmxLoader/TmxLoader.h"


enum class MAP_LAYER
{
	BLOCK,
	LINE,
	PIPE,
	MAX,
};
MAP_LAYER begin(MAP_LAYER);
MAP_LAYER end(MAP_LAYER);
MAP_LAYER operator++(MAP_LAYER& layer);
MAP_LAYER operator*(MAP_LAYER layer);

// �}�b�v���
using MapDataMap = std::map<std::string, std::pair<std::vector<int>, mapInfo>>;

class MapData
{
public:
	MapData(const std::string& fileName);
	~MapData();

	const std::vector<int>& GetMapData(MAP_LAYER layer);

	const int GetMapChipData(MAP_LAYER layer,const int& x, const int& y);
	const int GetMapChipData(MAP_LAYER layer, const Vector2& pos);
	const int GetMapChipData(MAP_LAYER layer, const Vector2Flt& pos);

	const mapInfo& GetMapInfo(MAP_LAYER layer);
private:
	bool Init(const std::string& fileName);

	MapDataMap mapData_;
	// �R���o�[�^�[
	std::map<MAP_LAYER, std::string> mapKey_;
};

