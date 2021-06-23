#pragma once
#include <list>
#include <map>
#include <string>
#include <utility>
#include "../Object/characterID.h"
#include "../Animation/Anim_ID.h"

struct AnimData
{
	// �\������
	std::list<int> flameData;
	// �Y����
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
	/// �L�����N�^�[�ɑΉ������A�j���[�V�����f�[�^�̓ǂݍ��݂Ɠo�^
	/// </summary>
	/// <param name="filepath">tmx�ւ̃p�X</param>
	/// <param name="id">�o�^����L������ID</param>
	/// <returns>true:���� false:���s</returns>
	bool LoadAnimTmx(const std::string& filepath, char_ID id);
	/// <summary>
	/// �����Ŏw�肳�ꂽ�L�����̃A�j���[�V�����Ɋւ���f�[�^
	/// �w�肵���L�����A�������͎w�肵���A�j���[�V���������o�^�̏ꍇ���g�̂Ȃ�Animation���Ԃ��Ă���
	/// </summary>
	/// <param name="cID">�l���������L������ID</param>
	/// <param name="aID">�l���������A�j���[�V������ID</param>
	/// <returns>�A�j���[�V�����֘A�f�[�^</returns>
	const Animation GetAnimationData(char_ID cID, Anim_ID aID);
	/// <summary>
	/// �����Ŏw�肳�ꂽ�L�����̃A�j���[�V������Image�Ɋւ���f�[�^
	/// �w�肵���L�����A�������͎w�肵���A�j���[�V���������o�^�̏ꍇ���g�̂Ȃ�AnimInfo���Ԃ��Ă���
	/// </summary>
	/// <param name="cID">�l���������L������ID</param>
	/// <param name="aID">�l���������A�j���[�V������ID</param>
	/// <returns>�A�j���[�V�����̉摜�֘A�f�[�^</returns>
	const AnimInfo GetAnimInfo(char_ID cID, Anim_ID aID);
	/// <summary>
	/// �����̏������ƂɌ��ݕ\������ׂ��摜��Ԃ�
	/// �L����ID��A�j���[�V����ID�ɑΉ������f�[�^�o�^����Ă��Ȃ��ꍇ-1���Ԃ��Ă���
	/// </summary>
	/// <param name="cID">�L����ID</param>
	/// <param name="aID">�A�j���[�V����ID</param>
	/// <param name="elapsed">�o�߃t���[���� ���[�v����ꍇ���Z�b�g�����</param>
	/// <param name="loopNum">���݃A�j���[�V�����J��Ԃ���</param>
	/// <returns>�f�[�^������ꍇ�\�����ׂ��摜 �Ȃ��ꍇ-1</returns>
	const int GetAnimImag(char_ID cID, Anim_ID aID, int& elapsed, int& loopNum);
private:
	AnimationMng();
	~AnimationMng() = default;
	// �L�����N�^�[�̎�ʂƃA�j���[�V������ʂ��L�[�ɂ����A�j���[�V�����֘A�f�[�^
	std::map<char_ID, std::map<Anim_ID,Animation>> animData_;
};
