#include <array>

#include <DxLib.h>

namespace
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
}


void MyDrawGraph(int x, int y, int width, int height) {
	std::array<VERTEX2DSHADER, 4> verts;
	for (auto& v : verts) {
		v.rhw = 1.0f;
		v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
		v.u = 0.0f;
		v.v = 0.0f;
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
		v.spc = GetColorU8(0, 0, 0, 0);
	}
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[1].pos.x = x + width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[2].pos.x = x;
	verts[2].pos.y = y + height;
	verts[2].v = 1.0f;
	verts[3].pos.x = x + width;
	verts[3].pos.y = y + height;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

void MyDrawGraph(int texH, int normH, int shaderH, int x, int y, int width, int height) {
	SetUseTextureToShader(0, texH);
	SetUseTextureToShader(1, normH);
	SetUsePixelShader(shaderH);
	MyDrawGraph(x, y, width, height);
}

void MyDrawGraph(int x, int y, int graphH, int normH, int shaderH) {
	SetUseTextureToShader(0, graphH);
	SetUseTextureToShader(1, normH);
	SetUsePixelShader(shaderH);
	int w, h;
	GetGraphSize(graphH, &w, &h);
	MyDrawGraph(graphH, -1, shaderH, x, y, w, h);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916035_‹´–{‘å‹P");
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	int pshandle = LoadPixelShader(L"test.pso");
	int imageH = LoadGraph(L"test.png");
	auto cbuffer = CreateShaderConstantBuffer(sizeof(float) * 4);
	float* gtime = static_cast<float*>(GetBufferShaderConstantBuffer(cbuffer));
	float time = 0.0f;

	SetDrawScreen(DX_SCREEN_BACK);

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		time += 1.0f / 60.0f;
		gtime[0] = time;
		UpdateShaderConstantBuffer(cbuffer);
		SetShaderConstantBuffer(cbuffer, DX_SHADERTYPE_PIXEL, 0);
		ClsDrawScreen();
		MyDrawGraph(0, 0, imageH, -1,pshandle);
		ScreenFlip();
	}
	InitShader();
	DxLib_End();
	return 0;
}