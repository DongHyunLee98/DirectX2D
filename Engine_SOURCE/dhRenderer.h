#pragma once
#include "YamYamEngine.h"
#include "dhGraphicDevice_Dx11.h"
#include "dhMesh.h"
#include "dhShader.h"
#include "dhConstantBuffer.h"
#include "dhCamera.h"
#include "dhLight.h"

using namespace dh::math;
using namespace dh::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		float deltaTime;
		int padd;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	CBUFFER(ColliderCB, CBSLOT_COLLISION)
	{
		int collCheck;
		int padd[3];
	};

	extern dh::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<dh::Light*> lights;
	extern dh::Camera* mainCamera;
	extern std::vector<dh::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}
