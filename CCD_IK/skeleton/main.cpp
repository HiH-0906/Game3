#include <DxLib.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "common/Vector2.h"
#include "common/Matrix.h"
#include "common/DHUtility.h" 


namespace
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
}

namespace
{
	constexpr size_t POINT_NUM = 8;
	constexpr float ALL_LENGTH = 600.0f;
	constexpr float SPACE = 50.0f;
	constexpr float END_DIFF = 0.0001f;
}

namespace
{
	constexpr int CIRCLE_RAD = 25;
}

namespace
{
	constexpr size_t CYCLE_MAX = 4;
}

float Clampf(float value, float min = 0.0f, float max = 0.0f)
{
	return std::max(std::min(value, max), min);
}

Vector2 Clamp(Vector2 value, Vector2 min = Vector2(0.0f, 0.0f), Vector2 max = Vector2(1.0f, 1.0f)) {
	return Vector2(Clampf(value.x, min.x, max.x), Clampf(value.y, min.y, max.y));
}

struct Point
{
	Vector2 pos_;
	Point() :pos_() {};
	Point(const float& x,const float& y) :pos_(x, y) {};
	Point(const Vector2& pos) :pos_(pos) {};
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916035_‹´–{‘å‹P");

	bool isClick = false;
	bool isCapture = false;

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	std::vector<Point> posList(POINT_NUM);
	Vector2 target = Vector2();

	for (int i = 0; i < posList.size(); i++)
	{
		posList[i].pos_ = Vector2{ SPACE + (i * ALL_LENGTH / POINT_NUM),static_cast<float>(screenSizeY) / 2.0f };
	}
	target = posList.back().pos_;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClearDrawScreen();


		for (size_t cycle = 0; cycle < CYCLE_MAX; cycle++)
		{
			// ––’[
			auto rit = posList.rbegin();
			++rit;
			for (; rit != posList.rend(); ++rit)
			{
				Vector2 endVec = posList.back().pos_ - rit->pos_;
				Vector2 tarVec = target - rit->pos_;

		
				if (endVec.Length() == 0.0f)
				{
					continue;
				}
				if (tarVec.Length() == 0.0f)
				{
					continue;
				}

				endVec.Nomalize();
				tarVec.Nomalize();

				float angle = atan2(Cross(endVec, tarVec), Dot(endVec, tarVec));
				if (angle == 0.0f)
				{
					continue;
				}
				Matrix2D mat = MultipleMatrix2D(TranslateMatrix2D(rit->pos_.x, rit->pos_.y),
					MultipleMatrix2D(RotateMatrix2D(angle), TranslateMatrix2D(-rit->pos_.x, -rit->pos_.y)));
				for (auto it = rit.base(); it != posList.end(); ++it)
				{
					it->pos_ = MultipleVector2(mat, it->pos_);
				}
			}
			if ((posList.back().pos_ - target).Length() < END_DIFF)
			{
				break;
			}
		}
	
		int mx, my;
		GetMousePoint(&mx, &my);
		Vector2 mPos(mx, my);
		auto nowMouseInput = GetMouseInput();
		if (nowMouseInput)
		{
			if (!isClick)
			{
				auto diff = mPos - target;
				auto r = diff.Length();
				if (r <= 20.0f)
				{
					isCapture = true;
				}
			}
			else
			{
				if (isCapture)
				{
					target = Clamp(mPos, Vector2(), Vector2(screenSizeX, screenSizeY));
				}
			}
			isClick = true;
		}
		else
		{
			isClick = false;
			isCapture = false;
		}
		for (size_t i = 0; i < posList.size(); i++)
		{
			DrawCircle(posList[i].pos_.x, posList[i].pos_.y, CIRCLE_RAD, 0xffffff, true);
			if (i < posList.size() - 1)
			{
				DrawLine(posList[i].pos_.x, posList[i].pos_.y, posList[i + 1].pos_.x, posList[i + 1].pos_.y, 0xffffff, 5);
			}
			DrawCircle(target.x, target.y, CIRCLE_RAD, 0xff0000, true);
		}
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}