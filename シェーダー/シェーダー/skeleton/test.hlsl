// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 pos    : SV_POSITION;
	float4 dif     : COLOR0;
	float2 uv  	: TEXCOORD0;
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 Output      : SV_TARGET0;
};

// C++ 側で設定する定数の定義

// 描画するテクスチャ
SamplerState smp       : register(s0);
Texture2D    tex       : register(t0);
Texture2D    norm       : register(t1);
float Time : register(c0);

float WhiteNoise(float2 coord)
{
	return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.465);
}

PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	
	float4 Tex = tex.Sample(smp, PSInput.uv);

	//float sinv = sin(PSInput.uv.y * 2 - Time * -0.1);
	//float steped = 1 - step(0.99, sinv * sinv);
	//
	//Tex.rgb -= (steped) * abs(sin(PSInput.uv.y * 50.0 + Time * 1.0)) * 0.05;
	//Tex.rgb -= (steped) * abs(sin(PSInput.uv.y * 100.0 - Time * 2.0)) * 0.08;
	//Tex.rgb += (1 - steped) * 0.1;



	float rate = 0.2;
	float stepd = step(8, fmod(480 -PSInput.uv.y * 480 + Time * 20.0, 10.0));


	Tex.g += rate * stepd;

	PSOutput.Output = Tex;

	// 関数の戻り値がラスタライザに渡される
	return PSOutput;
};