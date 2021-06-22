#pragma once
#include <list>
#include <map>
#include <string>
#include <utility>
#include "../Object/characterID.h"
#include "../Animation/Anim_ID.h"

struct AnimData
{
	std::list<int> flameData;
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
	bool LoadAnimTmx(const std::string& filepath, char_ID id);
	/// <summary>
	/// �����Ŏw�肳�ꂽ�L�����̃A�j���[�V�����Ɋւ���f�[�^
	/// �w�肵���L�����A�������͎w�肵���A�j���[�V���������o�^�̏ꍇ���g�̂Ȃ�Animation���Ԃ��Ă���
	/// </summary>
	/// <param name="cID">�l���������L����</param>
	/// <param name="aID">�l���������A�j���[�V����</param>
	/// <returns>�A�j���[�V�����֘A�f�[�^</returns>
	const Animation GetAnimationData(char_ID cID, Anim_ID aID);
	const int GetAnimImag(char_ID cID, Anim_ID aID, int& elapsed, int& loopNum);
private:
	AnimationMng();
	~AnimationMng() = default;
	// �L�����N�^�[�̎�ʂƃA�j���[�V������ʂ��L�[�ɂ����A�j���[�V�����֘A�f�[�^
	std::map<char_ID, std::map<Anim_ID,Animation>> animData_;
};
