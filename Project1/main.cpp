#include <cassert>
#include <utility>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <algorithm>
#include <Dxlib.h>
#include "Class/Square.h"
#include "Class/Circle.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

namespace 
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
	std::chrono::system_clock::time_point now;
	std::chrono::system_clock::time_point old;

	std::vector<InstanceData> instanceData;
	std::map<ShapeTag, std::function<void(std::vector<std::shared_ptr<Shape>>& list, const InstanceData& data)>> instanceFunc;
}

/// <summary>
/// íÜêSÇ©ÇÁéwíËÇ≥ÇÍÇΩä‘äuÇ≈ï™äÑê¸Çï`Ç≠
/// </summary>
/// <param name="inter">ä‘äu</param>
void DrawLine(const int& inter, bool flg = true, unsigned int col = 0xffff00)
{
	Vector2 tmp = flg == true ? Vector2{ (screenSizeX / 2) % inter ,(screenSizeY / 2) % inter } : Vector2{};
	for (int x = 0; x <= screenSizeX; x += inter)
	{
		DrawLine(tmp.x + x, 0, tmp.x + x, screenSizeY, col);
	}
	for (int y = -0; y <= screenSizeY; y += inter)
	{
		DrawLine(0, tmp.y + y, screenSizeX, tmp.y + y, col);
	}

	DrawLine(screenSizeX / 2, 0, screenSizeX / 2, screenSizeY, 0xffffff);
	DrawLine(0, screenSizeY / 2, screenSizeX, screenSizeY / 2, 0xffffff);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText("1916035_ã¥ñ{ëÂãP");

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	instanceFunc.try_emplace(ShapeTag::NON, [](std::vector<std::shared_ptr<Shape>>& list,const InstanceData& data) {assert(!"instanceFunc:shapeTagÇ™NON"); });
	instanceFunc.try_emplace(ShapeTag::Squeare, [](std::vector<std::shared_ptr<Shape>>& list, const InstanceData& data) {
		list.emplace_back(std::make_shared<Square>(data.pos, data.size, data.col, data.vec, data.speed));
	});
	instanceFunc.try_emplace(ShapeTag::Circle, [](std::vector<std::shared_ptr<Shape>>& list, const InstanceData& data) {
		list.emplace_back(std::make_shared<Circle>(data.pos, data.size, data.col, data.vec, data.speed));
	});

	std::vector<std::shared_ptr<Shape>> shapeList;

	shapeList.reserve(100);

	//shapeList.emplace_back(std::make_shared<Square>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 50.0f ,50.0f }, 0xff0000, Vector2Flt{ 1.0f ,1.0f },100.0f));
	shapeList.emplace_back(std::make_shared<Circle>(Vector2Flt{ 0.0f, 0.0f }, Vector2Flt{ 50.0f ,50.0f }, 0xff0000, Vector2Flt{ 0.0f ,-1.0f }, 150.0f));
	//shapeList.emplace_back(std::make_shared<Square>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 100.0f, 100.0f }, 0xffffff, Vector2Flt{ 0.4f ,0.6f },200.0f));
	shapeList.emplace_back(std::make_shared<Circle>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 50.0f, 50.0f }, 0xff0000, Vector2Flt{ 1.0f ,0.0f }, 150.0f));

	now = std::chrono::system_clock().now();

	int cnt = 0;
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		old = now;
		now = std::chrono::system_clock().now();
		ClsDrawScreen();

		float delta = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(now - old).count() / 1000000.0f);
		bool test = false;
		int x, y;
		GetMousePoint(&x, &y);
		for (const auto& shape : shapeList)
		{
			shape->Update(0.0, Vector2{ screenSizeX,screenSizeY }, shapeList,instanceData);
			if (!test)
			{
				shape->UpDate(x, y);
				test = true;
			}
		}

		/*for (auto shape = shapeList.begin(); shape != shapeList.end(); shape++)
		{
			(*shape)->Update(delta, Vector2{ screenSizeX,screenSizeY }, shapeList, instanceData);
		}*/

		DrawLine(50);

		for (const auto& shape : shapeList)
		{
			shape->Draw();
		}

		auto itr = std::remove_if(shapeList.begin(), shapeList.end(), [](std::weak_ptr<Shape> shape) {return shape.lock()->GetIsDead(); });

		shapeList.erase(itr, shapeList.end());

		DrawFormatString(0,0,0xffffff,"deltaTime::%lf\n",delta);
		ScreenFlip();

		for (const auto& IData : instanceData)
		{
			instanceFunc[IData.tag](shapeList, IData);
		}

		/*cnt++;
		if (cnt == 600)
		{
			shapeList[1]->SetIsDead();
		}
		if (cnt == 300)
		{
			shapeList[0]->SetIsDead();
		}*/
	}

	DxLib_End();

	return 1;
}