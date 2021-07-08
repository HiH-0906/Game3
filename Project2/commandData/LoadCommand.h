#pragma once
#include <string>
#include <list>
#include <utility>
#include "../Class/Input/INPUT_ID.h"
#include "../Class/XML/RapidXml/rapidxml.hpp"
#include "../Class/XML/RapidXml/rapidxml_utils.hpp"

struct LoadCommad
{
	std::list<std::pair<INPUT_ID, unsigned int>> operator()(const std::string filepath)
	{
		std::list<std::pair<INPUT_ID, unsigned int>> reComList;
		rapidxml::xml_node<>* tmx_orign_node_;
		rapidxml::xml_document<> TmxDoc_;

		rapidxml::file<> file(filepath.c_str());

		TmxDoc_.parse<0>(file.data());
		tmx_orign_node_ = TmxDoc_.first_node("command");


		return reComList;
	}
};
