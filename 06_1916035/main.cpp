#include <DxLib.h>
#include <list>
#include <vector>
#include <utility>
#include <functional>
#include <memory>
#include "NumPad.h"


#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 600
#define H_NUM 8
#define H_STICK_X ((SCREEN_SIZE_X-100)/4)
#define H_STICK_Y ((SCREEN_SIZE_Y-150))
#define H_MIN_SIZE_X (H_STICK_X/H_NUM)
#define H_MIN_SIZE_Y (H_STICK_Y/(H_NUM+1))


using HanoiStack = std::pair<std::list<int>, std::vector<std::list<int>>>;

std::unique_ptr<NumPad> pad_;
HanoiStack hStackA_;
HanoiStack hStackB_;
HanoiStack hStackC_;
int clickCnt;
int hCnt_;
bool leftold;
bool leftnow;
bool rightold;
bool rightnow;
bool strFlag_;
std::string str_;

std::function<void()> upDate_;

void hUpdate();
void NumUpdate();


void padnit()
{
	pad_->init();
	str_ = "段数を入力してENを押してください\n注：大きい数字を入力すると固まります（20段は厳しいかも）";
	strFlag_ = false;
	upDate_ = NumUpdate;
}

void InitHanoi()
{
	hStackA_.first.clear();
	hStackA_.second.clear();
	hStackB_.first.clear();
	hStackB_.second.clear();
	hStackC_.first.clear();
	hStackC_.second.clear();
	for (int i = hCnt_; i > 0; i--)
	{
		hStackA_.first.push_front(i);
	}
};

void HDarw()
{
	auto StackDraw = [&](const HanoiStack& stack, int num) {
		int hanoiCnt = 0;
		if (clickCnt >= stack.second.size())
		{
			clickCnt = stack.second.size() - 1;
		}
		for (auto iter = stack.second[clickCnt].rbegin(); iter != stack.second[clickCnt].rend(); iter++)
		{
			int hanoiX = (((H_STICK_X / hCnt_) / 2) * (*iter));
			int hanoiY = ((H_STICK_Y / (hCnt_ + 1)) * hanoiCnt);

			DrawBox(H_STICK_X - hanoiX + 60 + (H_STICK_X * num), SCREEN_SIZE_Y - 50 - (H_STICK_Y / (hCnt_ + 1)) - hanoiY, H_STICK_X + hanoiX + 60 + (H_STICK_X * num), SCREEN_SIZE_Y - 50 - hanoiY, 0xff8888, false);
			hanoiCnt++;
		}
	};
	for (int i = 0; i < 3; i++)
	{
		DrawBox(H_STICK_X + H_STICK_X * i + 50, 100, H_STICK_X + 20 + H_STICK_X * i + 50, SCREEN_SIZE_Y - 50, 0x88ff88, false);
	}
	StackDraw(hStackA_, 0);
	StackDraw(hStackB_, 1);
	StackDraw(hStackC_, 2);

	DrawFormatString(0, 0, 0xffffff, "%d　段",hCnt_);
	DrawFormatString(0, 32, 0xffffff, "手数　%d／%d　手目", clickCnt, hStackA_.second.size() - 1);
	DrawFormatString(0, 64, 0xffffff, "左クリック：1手進める");
	DrawFormatString(0, 96, 0xffffff, "右クリック：1手戻る");
	DrawFormatString(0, 128, 0xffffff, "右矢印：早送り");
	DrawFormatString(0, 160, 0xffffff, "左矢印：巻き戻し");

	DrawBox(50, SCREEN_SIZE_Y - 50, SCREEN_SIZE_X - 50, SCREEN_SIZE_Y - 25, 0xffffff, true);
}

void hMove(HanoiStack& a, HanoiStack& b, HanoiStack& c, int num)
{
	if (num > 0)
	{
		hMove(a, c, b, num - 1);
		int hanoi = a.first.front();
		a.first.pop_front();
		c.first.push_front(hanoi);
		a.second.emplace_back(a.first);
		b.second.emplace_back(b.first);
		c.second.emplace_back(c.first);
		hMove(b, a, c, num - 1);
	}
}


void NumUpdate()
{
	int x = 0;
	int y = 0;
	GetMousePoint(&x, &y);
	DrawFormatString(400, 0, 0xffffff, str_.c_str());
	if (pad_->UpDate(Vector2{ x,y }, !leftold && leftnow))
	{
		hCnt_ = atoi(pad_->GetInputStr().c_str());
		if (hCnt_ >= 3)
		{
			clickCnt = 0;
			InitHanoi();
			hStackA_.second.emplace_back(hStackA_.first);
			hStackB_.second.emplace_back(hStackB_.first);
			hStackC_.second.emplace_back(hStackC_.first);
			hMove(hStackA_, hStackB_, hStackC_, hCnt_);
			upDate_ = hUpdate;
		}
		else
		{
			if (!strFlag_)
			{
				str_ = str_ + "\n3以上を入力してください";
				strFlag_ = !strFlag_;
			}
		}
	}
}

void hUpdate()
{
	if (!leftold && leftnow)
	{
		clickCnt++;
		if (clickCnt >= hStackA_.second.size() - 1)
		{
			clickCnt = hStackA_.second.size() - 1;
		}
	}
	if (!rightold && rightnow)
	{
		clickCnt--;
		if (clickCnt < 0)
		{
			clickCnt = 0;
		}
	}
	HDarw();
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		clickCnt++;
		if (clickCnt >= hStackA_.second.size() - 1)
		{
			clickCnt = hStackA_.second.size() - 1;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		clickCnt--;
		if (clickCnt < 0)
		{
			clickCnt = 0;
		}
	}
	if (clickCnt >= hStackA_.second.size()-1)
	{
		DrawFormatString(0, 192, 0xffffff, "エンターキーでもう一度", hCnt_);
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			padnit();
		}
	}
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	SetOutApplicationLogValidFlag(false);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("問6_1916035_橋本大輝");
	if (DxLib_Init() == -1)
	{
		return 0;
	}

	
	leftold = false;
	leftnow = false;

	rightold = false;
	rightnow = false;

	pad_ = std::make_unique<NumPad>(Vector2{ SCREEN_SIZE_X / 2 - 132 / 2,SCREEN_SIZE_Y / 2 - 196 / 2 });
	padnit();

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		leftold = leftnow;
		leftnow = GetMouseInput() & MOUSE_INPUT_LEFT;
		rightold = rightnow;
		rightnow = GetMouseInput() & MOUSE_INPUT_RIGHT;
		upDate_();

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}