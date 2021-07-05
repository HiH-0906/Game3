#pragma once
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include "../Player.h"
#include "../../Map/MapData.h"
#include "../../common/Raycast.h"
#include "../../Input/Controller.h"
#include "../../XML/RapidXml/rapidxml.hpp"
#include "../../XML/RapidXml/rapidxml_utils.hpp"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

namespace state
{
	struct CheckMoveRay
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			Vector2Flt moveVec = {0.0f,0.0f};
			Vector2Flt offset = { 0.0f,0.0f };
			for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
			{
				std::string name = atr->name();
				if (name == "movex")
				{
					moveVec.x = static_cast<float>(std::atof(atr->value()));
				}
				if (name == "movey")
				{
					moveVec.y = static_cast<float>(std::atof(atr->value()));
				}
				if (name == "offSetx")
				{
					std::string str = atr->value();
					if (str == "+")
					{
						moveVec.x += pawn->size_.x / 2.0f;
					}
					if (str == "-")
					{
						moveVec.x += -(pawn->size_.x / 2.0f);
					}
					offset = { 0.0f,pawn->size_.y / 2.0f };

				}
				if (name == "offSety")
				{
					std::string str = atr->value();
					if (str == "+")
					{
						moveVec.y += pawn->size_.y / 2.0f;
					}
					if (str == "-")
					{
						moveVec.y += -(pawn->size_.y / 2.0f);
					}
					offset = { pawn->size_.y / 2.0f ,0.0f };
				}

			}
			Vector2Flt tmpPos = pawn->pos_ - offset;

			for (int i = 0; i < 9; i++)
			{
				Raycast::Ray ray = { tmpPos ,moveVec };
				_dbgDrawLine(ray.point.x, ray.point.y, ray.point.x + ray.vec.x, ray.point.y + ray.vec.y, 0x00ff00);
				_dbgDrawBox(pawn->pos_.x - pawn->size_.x / 2, pawn->pos_.y - pawn->size_.y / 2, pawn->pos_.x + pawn->size_.x / 2, pawn->pos_.y + pawn->size_.y / 2, 0xff0000, false);
				for (auto colData : pawn->mapData_.lock()->GetColData())
				{
					_dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xff0000, false);
					if (pawn->raycast_->CheckCollision(ray, colData))
					{
						_dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xffffff, true);
						return false;
					}
				}
				tmpPos += offset / 4.0f;
			}

			return true;
		}
	};

	struct CheckGuround
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			return true;
		}
	};
	struct Move
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
			{
				std::string name = atr->name();
				if (name == "x")
				{
					float movePow = static_cast<float>(std::atof(atr->value()));
					pawn->pos_.x += movePow;
					if (movePow < 0)
					{
						pawn->reverseXFlag_ = true;
					}
					else
					{
						pawn->reverseXFlag_ = false;
					}
				}
				if (name == "y")
				{
					pawn->pos_.y += static_cast<float>(std::atof(atr->value()));
				}
			}
			return true;
		}
	};

	struct CheckKeyTrg
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			auto atr = node->first_attribute("key");
			if (atr == nullptr)
			{
				assert(!"判別するkeyのattributeがない");
				return false;
			}
			std::string id = atr->value();
			if (pawn->input_IDkey_.count(id) <= 0)
			{
				assert(!"strngに対応したInputID未登録");
				return false;
			}
			if (pawn->controller_->GetTrg(pawn->input_IDkey_[id]))
			{
				return true;
			}
			return false;
		}
	};

	struct CheckKeyNow
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			auto atr = node->first_attribute("key");
			if (atr == nullptr)
			{
				assert(!"判別するkeyのattributeがない");
				return false;
			}
			std::string id = atr->value();
			if (pawn->input_IDkey_.count(id) <= 0)
			{
				assert(!"strngに対応したInputID未登録");
				return false;
			}
			if (pawn->controller_->GetNow(pawn->input_IDkey_[id]))
			{
				return true;
			}
			return false;
		}
	};

	struct CheckStopPos
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			if (oldPos == pawn->pos_)
			{
				return true;
			}
			oldPos = pawn->pos_;
			return false;
		}
	private:
		Vector2Flt oldPos = {};
	};

	struct SetAnimation
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			auto atr = node->first_attribute("id");
			if (atr == nullptr)
			{
				assert(!"判別するidのattributeがない");
				return false;
			}
			std::string id = atr->value();
			if (id == "Run")
			{
				pawn->SetAnimation(Char_Anim_ID::RUN);
			}
			if (id=="Idle")
			{
				pawn->SetAnimation(Char_Anim_ID::IDLE);
			}
			return true;
		}
	};

	struct ModuleNode
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			for (auto module = node->first_node(); module != nullptr; module = module->next_sibling())
			{
				std::string moduleName = module->first_attribute("name")->value();
				if (module_.count(moduleName) <= 0)
				{
					assert(!"state.xmlで指定されているmoduleが存在しない又は登録されていない");
					return false;
				}
				if (!module_[moduleName](pawn, module))
				{
					continue;
				}
				auto subModule = module->first_node();
				if (subModule == nullptr)
				{
					continue;
				}
				// 再起呼び出し
				if (!(*this)(pawn, module))
				{
					return false;
				}
			}
			return true;
		}
		std::map<std::string, std::function<bool(Pawn* pawn, rapidxml::xml_node<>* node)>> module_ = {
			{"Move",Move()},
			{"CheckKeyTrg",CheckKeyTrg()},
			{"CheckKeyNow",CheckKeyNow()},
			{"SetAnimation",SetAnimation()},
			{"CheckStopPos",CheckStopPos()},
			{"CheckMoveRay",CheckMoveRay()},
			{"CheckGuround",CheckGuround()}
		};
	};
}