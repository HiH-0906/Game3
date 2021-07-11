#pragma once
#include <string>
#include <list>
#include <map>
#include <utility>
#include "../Class/Object/Pawn.h"
#include "../Class/Input/INPUT_ID.h"
#include "../Class/XML/RapidXml/rapidxml.hpp"
#include "../Class/XML/RapidXml/rapidxml_utils.hpp"

namespace
{
	std::map<std::string, std::list<INPUT_ID>> chengeData
	{
		{"1",{INPUT_ID::LEFT,INPUT_ID::DOWN}},
		{"2",{INPUT_ID::DOWN}},
		{"3",{INPUT_ID::RIGHT,INPUT_ID::DOWN}},
		{"4",{INPUT_ID::LEFT}},
		{"5",{}},
		{"6",{INPUT_ID::RIGHT}},
		{"7",{INPUT_ID::LEFT,INPUT_ID::UP}},
		{"8",{INPUT_ID::UP}},
		{"9",{INPUT_ID::RIGHT,INPUT_ID::UP}},
		{"BTN_2",{INPUT_ID::BTN_2}},
		{"BTN_3",{INPUT_ID::BTN_3}},
	};
}

struct LoadCommad
{
	std::list<CommandData> operator()(const std::string filepath)
	{
		std::list<CommandData> reComList;
		rapidxml::file<> file(filepath.c_str());
		TmxDoc_.parse<0>(file.data());
		tmx_orign_node_ = TmxDoc_.first_node("character");
		for (auto comNode = tmx_orign_node_->first_node("command"); comNode != nullptr; comNode = comNode->next_sibling("command"))
		{
			CommandData commndData;
			commndData.name_ = comNode->first_attribute("name")->value();
			commndData.allTime_ = std::atoi(comNode->first_attribute("allTime")->value());
			for (auto node = comNode->first_node("data"); node != nullptr; node = node->next_sibling("data"))
			{
				commndData.command_.push_back({ chengeData[node->first_attribute("key")->value()],std::atoi(node->first_attribute("time")->value()) });
			}
			reComList.push_back(commndData);
		}
		return reComList;
	}
private:
	rapidxml::xml_node<>* tmx_orign_node_;
	rapidxml::xml_document<> TmxDoc_;
};
