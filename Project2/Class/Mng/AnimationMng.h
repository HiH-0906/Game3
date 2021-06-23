#pragma once
#include <list>
#include <map>
#include <string>
#include <utility>
#include "../Object/characterID.h"
#include "../Animation/Anim_ID.h"

struct AnimData
{
	// 表示時間
	std::list<int> flameData;
	// 添え字
	std::list<int> subscript;
};

struct AnimInfo
{
	int width = 0;
	int height = 0;
	int widthCnt = 0;
	int heightCnt = 0;
	int loop = 0;
	std::string source = "";
	std::string imgKey = "";
};

#define lpAnimMng AnimationMng::GetInstance()
using Animation = std::pair<AnimInfo,AnimData>;

class AnimationMng
{
public:
	static AnimationMng& GetInstance()
	{
		static AnimationMng s_instance_;
		return s_instance_;
	}
	/// <summary>
	/// キャラクターに対応したアニメーションデータの読み込みと登録
	/// </summary>
	/// <param name="filepath">tmxへのパス</param>
	/// <param name="id">登録するキャラのID</param>
	/// <returns>true:成功 false:失敗</returns>
	bool LoadAnimTmx(const std::string& filepath, char_ID id);
	/// <summary>
	/// 引数で指定されたキャラのアニメーションに関するデータ
	/// 指定したキャラ、もしくは指定したアニメーションが未登録の場合中身のないAnimationが返ってくる
	/// </summary>
	/// <param name="cID">獲得したいキャラのID</param>
	/// <param name="aID">獲得したいアニメーションのID</param>
	/// <returns>アニメーション関連データ</returns>
	const Animation GetAnimationData(char_ID cID, Anim_ID aID);
	/// <summary>
	/// 引数で指定されたキャラのアニメーションのImageに関するデータ
	/// 指定したキャラ、もしくは指定したアニメーションが未登録の場合中身のないAnimInfoが返ってくる
	/// </summary>
	/// <param name="cID">獲得したいキャラのID</param>
	/// <param name="aID">獲得したいアニメーションのID</param>
	/// <returns>アニメーションの画像関連データ</returns>
	const AnimInfo GetAnimInfo(char_ID cID, Anim_ID aID);
	/// <summary>
	/// 引数の情報をもとに現在表示するべき画像を返す
	/// キャラIDやアニメーションIDに対応したデータ登録されていない場合-1が返ってくる
	/// </summary>
	/// <param name="cID">キャラID</param>
	/// <param name="aID">アニメーションID</param>
	/// <param name="elapsed">経過フレーム数 ループする場合リセットされる</param>
	/// <param name="loopNum">現在アニメーション繰り返し回数</param>
	/// <returns>データがある場合表示すべき画像 ない場合-1</returns>
	const int GetAnimImag(char_ID cID, Anim_ID aID, int& elapsed, int& loopNum);
private:
	AnimationMng();
	~AnimationMng() = default;
	// キャラクターの種別とアニメーション種別をキーにしたアニメーション関連データ
	std::map<char_ID, std::map<Anim_ID,Animation>> animData_;
};
