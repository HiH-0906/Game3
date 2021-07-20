#pragma once
#include <string>
#include <map>
#include <functional>
#include <cassert>
#include "../Pawn.h"
#include "../Bullet.h"
#include "../../collision/Collision.h"
#include "../../collision/SquaerCollision.h"
#include "../../Mng/CollisionMng.h"
#include "../../Map/MapData.h"
#include "../../common/Raycast.h"
#include "../../Input/Controller.h"
#include "../../XML/RapidXml/rapidxml.hpp"
#include "../../XML/RapidXml/rapidxml_utils.hpp"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

// コンバーター系
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
	std::array<CMD_ID, 8> cmdExtension = {
			CMD_ID::LEFT_D_D,
			CMD_ID::DOWN,
			CMD_ID::RIGHT_D_D,
			CMD_ID::RIGHT,
			CMD_ID::RIGHT_U_D,
			CMD_ID::UP,
			CMD_ID::LEFT_U_D,
			CMD_ID::LEFT
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
					moveVec.x = static_cast<float>(std::atof(atr->value()))*pawn->delta_;
				}
				if (name == "movey")
				{
					moveVec.y = static_cast<float>(std::atof(atr->value())) * pawn->delta_;
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
				for (auto colData : pawn->mapData_.lock()->GetColData())
				{
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
			for (auto colData : pawn->mapData_.lock()->GetColData())
			{
				_dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xff0000, false);
			}
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
				for (auto colData : pawn->mapData_.lock()->GetColData())
				{
					_dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xff0000, false);
					if (pawn->raycast_->CheckCollision(ray, colData))
					{
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
				pawn->bullet_ = std::make_shared<Bullet>(pawn->pos_, Vector2{ 32,32 }, Object_ID::Bullet, speed, pawn->reverseXFlag_, pawn->teamTag_);
				Vector2Flt size = static_cast<Vector2Flt>(pawn->bullet_->GetSize());
				auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
				col->SetOwner(pawn->bullet_);
				lpCollisionMng.RegistrationCol(col);
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
				const Controller::RingBuf* buf = pawn->controller_->GetRingBuf();
				unsigned int timeCnt_ = 0;
				for (std::reverse_iterator<std::list<CommandData::command>::iterator> cmd = data.command_.rbegin(); cmd != data.command_.rend(); cmd++)
				{
					int cnt = 0;
					unsigned int checkID = static_cast<unsigned int>(cmd->id);
					unsigned int mask = 0xffffffff;
					// ボタン入力時は方向入力を無視する
					if (buf->id_ >= static_cast<unsigned int>(CMD_ID::BTN_1))
					{
						mask -= 0x0000000f;
					}
					// 左右反転処理
					if (pawn->reverseXFlag_ && ((cmd->id >= CMD_ID::LEFT) && cmd->id <= CMD_ID::RIGHT_D_D))
					{
						checkID ^= 0x0000000c;
					}
					auto check = CheckInput(&buf, mask, checkID, *cmd);
					if (check.first)
					{
						timeCnt_ += check.second;
					}
					else
					{
						TRACE(("COMMAND失敗"+data.name_+"\n").c_str());
						return false;
					}
				}
				if (timeCnt_ > data.allTime_)
				{
					TRACE(("COMMAND失敗！" + data.name_ + ":全体入力時間が長すぎ:%d/%d\n").c_str(), timeCnt_, data.allTime_);
					return false;
				}
				TRACE(("COMMAND成功！" + data.name_ + "\n").c_str());
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
	private:
		// 入力されたコマンドとコマンドデータを比較する。隣に入力がずれても許容するニュートラルも許容する
		std::pair<bool, int> CheckInput(const Controller::RingBuf** buf, const unsigned int mask, const unsigned int& check,
			CommandData::command cmd, int nCnt = 0)
		{
			// 5フレーム分しか許容しません
			if (nCnt > 5)
			{
				TRACE("許容over\n");
				return { false,0 };
			}
			int cnt = 0;
			// 判定 設定されたTime分まで遡る
			while ((((*buf)->id_ & mask)) == check && (cnt < cmd.time))
			{
				(*buf) = (*buf)->befor_;
				cnt++;
			};
			// 入力があったか
			if (cnt == 0)
			{
				unsigned int befor = -1;
				unsigned int next = -1;
				// 許容位置探し
				for (int i = 0; i < cmdExtension.size(); i++)
				{
					// 方向だけ取り出す
					unsigned int id = (*buf)->id_ & 0x0000000f;
					// ニュートラルも許容
					if (id == 0)
					{
						TRACE("N許容\n");
						(*buf) = (*buf)->befor_;
						auto tmp = CheckInput(buf, mask, check, cmd, ++nCnt);
						return { tmp.first,tmp.second + cnt };
					}
					if (cmdExtension[i] == static_cast<CMD_ID>(cmd.id))
					{
						befor = i - 1 < 0 ? cmdExtension.size() - 1 : i - 1;
						next = i + 1 > cmdExtension.size() ? 0 : i + 1;
						if (cmdExtension[befor] == static_cast<CMD_ID>(id) || cmdExtension[next] == static_cast<CMD_ID>(id))
						{
							TRACE("許容\n");
							(*buf) = (*buf)->befor_;
							auto tmp = CheckInput(buf, mask, check, cmd,++nCnt);
							return { tmp.first,tmp.second + cnt };
						}
						break;
					}
				}
				// 許容できる入力ではなかった
				TRACE("駄目\n");
				return { false ,0 };
			}
			return { true ,cnt };
		};
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

	struct CheckAlive
	{
		bool operator()(Pawn* pawn, rapidxml::xml_node<>* node)
		{
			std::string check = node->first_attribute("flag")->value();
			bool reflag = true;
			if (check == "false")
			{
				reflag = false;
			}
			if (pawn->isAlive_)
			{
				return reflag;
			}
			return !reflag;
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
					pawn->pos_.x += movePow*pawn->delta_;
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
					pawn->pos_.y += static_cast<float>(std::atof(atr->value())) * pawn->delta_;
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
			pawn->yaddPower_ += 0.4f;
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
				assert(!"判別するkeyのattributeがない");
				return false;
			}
			std::string id = atr->value();
			if (input_IDkey_.count(id) <= 0)
			{
				assert(!"strngに対応したInputID未登録");
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
				assert(!"判別するkeyのattributeがない");
				return false;
			}
			std::string id = atr->value();
			if (input_IDkey_.count(id) <= 0)
			{
				assert(!"strngに対応したInputID未登録");
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
			if (id == "death")
			{
				pawn->SetAnimation(Char_Anim_ID::DEATH);
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
			{"CheckGuround",CheckGuround()},
			{"Fall",Fall()},
			{"Jump",Jump()},
			{"CheckAnim",CheckAnim()},
			{"Attack",Attack()},
			{"CheckCmmand",CheckCmmand()},
			{"CheckAlive",CheckAlive()},
		};
	};
}