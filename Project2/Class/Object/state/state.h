#pragma once
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include "../Pawn.h"
#include "../Bullet.h"
#include "../../Map/MapData.h"
#include "../../common/Raycast.h"
#include "../../Input/Controller.h"
#include "../../XML/RapidXml/rapidxml.hpp"
#include "../../XML/RapidXml/rapidxml_utils.hpp"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"


namespace
{
	std::map<std::string, INPUT_ID>  input_IDkey_ = {
		{"LEFT",INPUT_ID::LEFT},
		{"RIGHT",INPUT_ID::RIGHT},
		{"UP",INPUT_ID::UP},
		{"DOWN",INPUT_ID::DOWN},
		{"BTN_1",INPUT_ID::BTN_1},
		{"BTN_2",INPUT_ID::BTN_2},
		{"BTN_3",INPUT_ID::BTN_3}
	};
	std::map<std::string, Char_Anim_ID>  Anim_IDkey_ = {
		{"IDLE",Char_Anim_ID::IDLE},
		{"RUN",Char_Anim_ID::RUN},
		{"JUMP",Char_Anim_ID::JUMP},
		{"FALL",Char_Anim_ID::FALL}
	};
}
namespace state
{
	struct CheckMoveRay
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			Vector2Flt moveVec = { 0.0f,0.0f };
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
					offset = { pawn->size_.x / 2.0f ,0.0f };
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
			std::string atr = node->first_attribute("isGuround")->value();
			bool reFlag = false;
			if (atr=="true")
			{
				reFlag = true;
			}
			Vector2Flt moveVec = { 0.0f,(pawn->size_.y / 2.0f) + pawn->yaddPower_ };
			Vector2Flt offset = { pawn->size_.x / 2.0f ,0.0f };
			if (pawn->yaddPower_ <= 0)
			{
				moveVec = { 0.0f,-(pawn->size_.y / 2.0f) - pawn->yaddPower_ };
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
						pawn->yaddPower_ = 0.2f;
						return reFlag;
					}
				}
				tmpPos += offset / 4.0f;
			}
			return !reFlag;
		}
	};

	struct Attack
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			TRACE("ATTACK!!\n");
			if (!pawn->bullet_)
			{
				Vector2Flt speed = {};
				if (pawn->reverseXFlag_)
				{
					speed = { -10.0f,0.0f };
				}
				else
				{
					speed = { 10.0f,0.0f };
				}
				pawn->bullet_ = std::make_unique<Bullet>(pawn->pos_, Vector2{ 32,32 }, Object_ID::Bullet, speed, pawn->reverseXFlag_);
			}
			return true;
		}
	};

	struct CheckCmmand
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			
			auto CheckCommand = [&](CommandData data)
			{
				auto input = pawn->controller_->GetRingBuf();
				int timeCnt_ = 0;
				for (auto cmd = data.command_.rbegin(); cmd != data.command_.rend(); cmd++)
				{
					int cnt = 0;
					unsigned int checkID = static_cast<unsigned int>(cmd->first);
					unsigned int mask = 0xffffffff;
					if (input->id_ >= static_cast<unsigned int>(CMD_ID::BTN_1))
					{
						mask -= 0x0000000f;
					}
					// ”½“]ˆ—
					if (pawn->reverseXFlag_&& ((cmd->first>=CMD_ID::LEFT)&& cmd->first <= CMD_ID::RIGHT_D_D))
					{
						checkID ^= 0x0000000c;
					}
					while (((input->id_ & mask)) == checkID && (cnt < cmd->second))
					{
						input = input->befor_;
						cnt++;
					};
					if (cnt == 0)
					{
						TRACE(("COMMANDŽ¸”sI"+ data.name_+ ": % d\n").c_str(), checkID);
						return false;
					}
					timeCnt_ += cnt;
				}
				if (timeCnt_ >= data.allTime_)
				{
					TRACE(("COMMANDŽ¸”sI" + data.name_ + ":‘S‘Ì“ü—ÍŽžŠÔ‚ª’·‚·‚¬:%d/%d\n").c_str(), timeCnt_, data.allTime_);
					return false;
				}
				TRACE(("COMMAND¬Œ÷I" + data.name_ + "\n").c_str());
				return true;
			};
			
			for (const auto& data:pawn->commandList_)
			{
				if (CheckCommand(data))
				{
					return true;
				}
			}
			return false;
		}
	};

	struct CheckAnim
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			std::string flag = node->first_attribute("flag")->value();
			bool reFlag = false;
			if (flag == "true")
			{
				reFlag = true;
			}
			for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
			{
				std::string name = atr->name();
				if (name == "id")
				{
					std::string val = atr->value();
					if (pawn->animID_ == Anim_IDkey_[val])
					{
						return reFlag;
					}
				}
			}
			return !reFlag;
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

	struct Fall
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			pawn->pos_.y += pawn->yaddPower_;
			pawn->yaddPower_ += 0.2f;
			if (pawn->yaddPower_ < 0)
			{
				pawn->SetAnimation(Char_Anim_ID::JUMP);
			}
			else
			{
				pawn->SetAnimation(Char_Anim_ID::FALL);
			}
			return true;
		}
	};

	struct Jump
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			pawn->yaddPower_ = pawn->defJunpPower_;
			pawn->pos_.y += pawn->yaddPower_;
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
				assert(!"”»•Ê‚·‚ékey‚Ìattribute‚ª‚È‚¢");
				return false;
			}
			std::string id = atr->value();
			if (input_IDkey_.count(id) <= 0)
			{
				assert(!"strng‚É‘Î‰ž‚µ‚½InputID–¢“o˜^");
				return false;
			}
			if (pawn->controller_->GetTrg(input_IDkey_[id]))
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
				assert(!"”»•Ê‚·‚ékey‚Ìattribute‚ª‚È‚¢");
				return false;
			}
			std::string id = atr->value();
			if (input_IDkey_.count(id) <= 0)
			{
				assert(!"strng‚É‘Î‰ž‚µ‚½InputID–¢“o˜^");
				return false;
			}
			if (pawn->controller_->GetNow(input_IDkey_[id]))
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
				assert(!"”»•Ê‚·‚éid‚Ìattribute‚ª‚È‚¢");
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
					assert(!"state.xml‚ÅŽw’è‚³‚ê‚Ä‚¢‚émodule‚ª‘¶Ý‚µ‚È‚¢–”‚Í“o˜^‚³‚ê‚Ä‚¢‚È‚¢");
					return false;
				}
				if (!module_[moduleName](pawn, module))
				{
					continue;
				}
				// Ä‹NŒÄ‚Ño‚µ
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
			{"CheckGuround",CheckGuround()},
			{"Fall",Fall()},
			{"Jump",Jump()},
			{"CheckAnim",CheckAnim()},
			{"Attack",Attack()},
			{"CheckCmmand",CheckCmmand()}
		};
	};
}