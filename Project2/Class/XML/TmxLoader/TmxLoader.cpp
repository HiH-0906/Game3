#include <iostream>
#include <cassert>
#include "TmxLoader.h"
#include "../RapidXml/rapidxml.hpp"
#include "../RapidXml/rapidxml_utils.hpp"
#include "../../../_debug/_DebugConOut.h"

Loader::TmxLoader::TmxLoader()
{
	VersionMap();
}

Loader::TmxLoader::TmxLoader(const char* filename)
{
	VersionMap();
	TmxLoad(filename);
}

Loader::TmxLoader::~TmxLoader()
{
}
// 対応しているバージョンの登録
void Loader::TmxLoader::VersionMap(void)
{
	version_["2021.01.13"] = 1;
	version_["1.4.2"] = 1;
	version_["1.4.3"] = 1;
	version_["1.6.0"] = 1;
}
// Tmxファイルをロード
bool Loader::TmxLoader::TmxLoad(std::string filename)
{
	// Tmx関連準備
	rapidxml::file<> file(filename.c_str());
	TmxDoc_.parse<0>(file.data());

	tmx_orign_node_ = TmxDoc_.first_node("map");
	if (!tmx_orign_node_)
	{
		assert(!"Tmxのfirst_node(map)がない");
		return false;
	}
	// バージョン対応しているか確認
	if (version_.count(tmx_orign_node_->first_attribute("tiledversion")->value()) == 0)
	{
		assert(!"TiledVersion未対応");
		return false;
	}

	info_.firstGID = std::atoi(tmx_orign_node_->first_node("tileset")->first_attribute("firstgid")->value());

	// マップの全体サイズ格納
	info_.mapSize.x = std::atoi(tmx_orign_node_->first_attribute("width")->value());
	info_.mapSize.y = std::atoi(tmx_orign_node_->first_attribute("height")->value());
	info_.nextLayer = std::atoi(tmx_orign_node_->first_attribute("nextlayerid")->value());

	// データの格納準備
	mapStr_.resize(GetLayerSize());

	auto itrLayer = mapStr_.begin();

	for (rapidxml::xml_node<>* layer = tmx_orign_node_->first_node("layer"); layer != nullptr; layer = layer->next_sibling())
	{
		itrLayer->name = layer->first_attribute("name")->value();
		auto data = layer->first_node("data")->first_node();
		itrLayer->data = data->value();
		++itrLayer;
	}

	// Tsx用のパスづくり

	auto source = tmx_orign_node_->first_node("tileset")->first_attribute("source")->value();

	std::string pass = filename.substr(0, filename.find_last_of("/") + 1);

	return TsxLoad(pass + source);
}

bool Loader::TmxLoader::TsxLoad(std::string filename)
{
	// 準備
	rapidxml::file<> file(filename.c_str());
	TsxDoc_.parse<0>(file.data());

	// Tmxで確認してるけど一応確認
	if (version_.count(tmx_orign_node_->first_attribute("tiledversion")->value()) == 0)
	{
		assert(!"TiledVersion未対応");
		return false;
	}

	tsx_orign_node_ = TsxDoc_.first_node("tileset");
	if (!tsx_orign_node_)
	{
		assert(!"Tsxのfirst_node(tileset)がない");
		return false;
	}
	// マップ関連 べた書き 特に省略もできないんじゃないかな感 やれるならstringを打たなくていいようにしたい
	info_.chipSize.x = std::atoi(tsx_orign_node_->first_attribute("tilewidth")->value());
	info_.chipSize.y = std::atoi(tsx_orign_node_->first_attribute("tileheight")->value());
	info_.imageAllNum = std::atoi(tsx_orign_node_->first_attribute("tilecount")->value());
	info_.columnsNum = std::atoi(tsx_orign_node_->first_attribute("columns")->value());
	info_.lineNum = info_.imageAllNum / info_.columnsNum;
	info_.key = tsx_orign_node_->first_attribute("name")->value();
	info_.imageStr = tsx_orign_node_->first_node("image")->first_attribute("source")->value();
	info_.imageSize.x = std::atoi(tsx_orign_node_->first_node("image")->first_attribute("width")->value());
	info_.imageSize.y = std::atoi(tsx_orign_node_->first_node("image")->first_attribute("height")->value());

	return true;
}

int Loader::TmxLoader::GetLayerSize(void)
{
	if (tmx_orign_node_ == nullptr)
	{
		return 0;
	}
	return (std::atoi(tmx_orign_node_->first_attribute("nextlayerid")->value()) - 1);
}

const mapStr Loader::TmxLoader::GetmapStr(void)
{
	return mapStr_;
}

const std::string Loader::TmxLoader::GetMapKey(void)
{
	return info_.key;
}

const mapInfo Loader::TmxLoader::GetMapInfo(void)
{
	return info_;
}


