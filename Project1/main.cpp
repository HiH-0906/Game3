#include <cassert>
#include <utility>
#include <memory>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <chrono>
#include <algorithm>
#include <Dxlib.h>

#include "Class/Square.h"
#include "Class/Circle.h"
#include "Class/Triangle.h"
#include "Class/Carrot.h"
#include "Class/Star.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

namespace 
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;

	std::chrono::system_clock::time_point now;
	std::chrono::system_clock::time_point old;
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
	SetAlwaysRunFlag(true);

	std::vector<std::shared_ptr<Shape>> shapeList;

	shapeList.reserve(100);

	

	std::array<Vector2Flt, 3> vertex;
	vertex[0] = Vector2Flt{ 0.0f,-50.0f };
	vertex[1] = Vector2Flt{ 50.0f,50.0f };
	vertex[2] = Vector2Flt{ -50.0f,50.0f };

	shapeList.emplace_back(std::make_shared<Triangle>(Vector2Flt{ 300.0f, 150.0f }, vertex, Vector2Flt{ 100.0f ,100.0f }, 0xff0000, Vector2Flt{ -0.4f ,1.5f },200.0f));

	vertex[0] = Vector2Flt{ 0.0f,-75.0f };
	vertex[1] = Vector2Flt{ 50.0f,50.0f };
	vertex[2] = Vector2Flt{ -50.0f,25.0f };
	shapeList.emplace_back(std::make_shared<Triangle>(Vector2Flt{ 150.0f, 250.0f }, vertex, Vector2Flt{ 100.0f ,100.0f }, 0x00ff00, Vector2Flt{ 1.0f ,-0.5f }, 200.0f));

	vertex[0] = Vector2Flt{ 0.0f,-10.0f };
	vertex[1] = Vector2Flt{ 50.0f,30.0f };
	vertex[2] = Vector2Flt{ -50.0f,20.0f };
	shapeList.emplace_back(std::make_shared<Triangle>(Vector2Flt{ 400.0f, 250.0f }, vertex, Vector2Flt{ 100.0f ,100.0f }, 0x0000ff, Vector2Flt{ 1.6f ,1.5f }, 200.0f));

	shapeList.emplace_back(std::make_shared<Square>(Vector2Flt{ 100.0f,50.0f }, Vector2Flt{ 50.0f,50.0f }, 0x00ffff, Vector2Flt{ -1.0f ,0.2f }, 200.0f));
	shapeList.emplace_back(std::make_shared<Square>(Vector2Flt{ 400.0f,350.0f }, Vector2Flt{ 60.0f,60.0f }, 0x88000f, Vector2Flt{ 0.4f ,1.5f }, 200.0f));
	shapeList.emplace_back(std::make_shared<Square>(Vector2Flt{ 500.0f,50.0f }, Vector2Flt{ 20.0f,70.0f }, 0x00ff7f, Vector2Flt{ 0.4f ,1.5f }, 200.0f));

	shapeList.emplace_back(std::make_shared<Circle>(Vector2Flt{ 200.0f,150.0f },50.0f , 0x880088f, Vector2Flt{ 2.0f ,-0.5f }, 200.0f));
	shapeList.emplace_back(std::make_shared<Circle>(Vector2Flt{ 100.0f,250.0f }, 60.0f, 0x008800f, Vector2Flt{ 0.5f ,-2.0f }, 200.0f));
	shapeList.emplace_back(std::make_shared<Circle>(Vector2Flt{ 50.0f,250.0f }, 35.0f, 0x008888f, Vector2Flt{ 1.5f ,-2.0f }, 200.0f));

	shapeList.emplace_back(std::make_shared<Star>(Vector2Flt{ 100.0f,200.0f }, Vector2Flt{ 100.0f ,100.0f }, 0xffff00, Vector2Flt{ 1.7f ,1.3f }, 200.0f));
	shapeList.emplace_back(std::make_shared<Carrot>(Vector2Flt{ 100.0f,200.0f }, Vector2Flt{ 50.0f ,100.0f }, 0xff00ff, Vector2Flt{ 1.0f ,2.0f }, 200.0f));

	for (const auto& shape : shapeList)
	{
		shape->SetCollisionOwner(shape);
	}

	now = std::chrono::system_clock().now();
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		old = now;
		now = std::chrono::system_clock().now();

		float delta = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(now - old).count() / 1000000.0f);
		for (const auto& shape : shapeList)
		{
			shape->HitUpdate(delta,shapeList);
		}
		for (const auto& shape : shapeList)
		{
			shape->Update(delta, Vector2{ screenSizeX,screenSizeY });
		}
		

		ClsDrawScreen();
		DrawLine(50);
		for (const auto& shape : shapeList)
		{
			shape->Draw();
		}
		DrawFormatString(0,0,0xffffff,"deltaTime::%lf\n",delta);
		ScreenFlip();
		auto itr = std::remove_if(shapeList.begin(), shapeList.end(), [](std::weak_ptr<Shape> shape) {return shape.lock()->GetIsDead(); });

		shapeList.erase(itr, shapeList.end());
	}

	DxLib_End();

	return 1;
}