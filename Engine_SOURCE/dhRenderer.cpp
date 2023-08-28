#include "dhRenderer.h"
#include "dhResources.h"
#include "dhTexture.h"
#include "dhMaterial.h"
#include "dhStructedBuffer.h"
#include "dhPaintShader.h"
#include "dhParticleShader.h"

// inputLayer - LoadShader - LoadMaterial ( ������ PSVS����� �۾��ϰ� globals�� ����������� �����߰�)

namespace renderer
{
	using namespace dh;
	using namespace dh::graphics;
	dh::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	//
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

	//
	dh::Camera* mainCamera = nullptr;
	std::vector<dh::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = dh::Resources::Find<Shader>(L"TriangleShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = dh::Resources::Find<Shader>(L"SpriteShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = dh::Resources::Find<Shader>(L"GridShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = dh::Resources::Find<Shader>(L"DebugShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = dh::Resources::Find<Shader>(L"SpriteAnimationShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = dh::Resources::Find<Shader>(L"ParticleShader");
		dh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		
#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion

	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};


		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);


		vertexes.clear();
		indexes.clear();
		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		// ====== �ε��� ���� �����
		// 1. �ε��� ���۷� �׷��� ������ ������ ������ �迭�� �־� �����Ѵ�.
		// ��, �ִ� ������ �ݵ�� '�ð� ����'���� �־���Ѵ�.
		// �ݽð� �������� ������ �����ϸ� �޸����� �ν��Ͽ� �׷����� �ʰ� �ȴ�.
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

	
		// ���ҽ� ���� shared_ptr�� �����Ǳ� ������ new ������ ��� std::make_shared<>�� ����Ѵ�
		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadBuffer()
	{
		// ������� �����ϴ� �κ�
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		// Animator Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		// Collision Buffer
		constantBuffer[(UINT)eCBType::Collision] = new ConstantBuffer(eCBType::Collision);
		constantBuffer[(UINT)eCBType::Collision]->Create(sizeof(ColliderCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> triangleShader = std::make_shared<Shader>();
		triangleShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		triangleShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		dh::Resources::Insert(L"TriangleShader", triangleShader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		dh::Resources::Insert(L"SpriteShader", spriteShader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		dh::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		dh::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		dh::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		dh::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		dh::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		dh::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTexture()
	{
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		dh::Resources::Insert(L"PaintTexuture", uavTexture);


		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		// Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"CupheadParticle", L"..\\Resources\\particle\\cupheadParticle.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}
	void LoadMaterial()
	{
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");


		//std::shared_ptr<Texture> texture
		//	= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		//std::shared_ptr<Material> material = std::make_shared<Material>();
		//material->SetShader(shader);
		//material->SetTexture(texture);
		//Resources::Insert(L"SpriteMaterial", material);

	// +.+.+.+. ����
	// 1. �⺻������ ���� �� ���������� �Ѵ�. (UI ����)
	// 2. ����� �ȵ� �� ���������� �ٲ۴�.
	// 3. ���������� �ٲ� �� �ȳ��´ٸ� �� �� �������Ͻ� �ϳ��� Grid ���̾�� �ִ´�
	// 4. UI�� �׻� �������� �صα�(�Ⱥ��δٸ� �Ⱥ��̴� �༮�� ���������� ������)

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BossStage1", L"..\\Resources\\Texture\\BossStage1.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"BossStage1_Material", material);

		// texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		// texture = Resources::Find<Texture>(L"PaintTexuture");
		// material = std::make_shared<Material>();
		// material->SetShader(shader);
		// material->SetTexture(texture);
		// material->SetRenderingMode(eRenderingMode::Transparent);
		// Resources::Insert(L"SpriteMaterial02", material);

		// �ִϸ��̼��� ������ �ڿ��־���Ѵ�. (���ο� ���̴��� �ֱ⶧��)
		std::shared_ptr<Shader> shaderAnimation
			= Resources::Find<Shader>(L"SpriteAnimationShader");
		material = std::make_shared<Material>();
		material->SetShader(shaderAnimation);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimaionMaterial", material);

		std::shared_ptr<Shader> particleShader
			= Resources::Find<Shader>(L"ParticleShader");
		material = std::make_shared<Material>();
		material->SetShader(particleShader);
		material->SetRenderingMode(eRenderingMode::Transparent);

		std::shared_ptr<Texture> particleTex
			= Resources::Find<Texture>(L"CupheadParticle");
		material->SetTexture(particleTex);
		Resources::Insert(L"ParticleMaterial", material);

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		// Logo
		{
			texture = Resources::Load<Texture>(L"Logo", L"..\\Resources\\Texture\\Logo.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Logo_Material", material);
		}

		// Title
		{
			texture = Resources::Load<Texture>(L"title1", L"..\\Resources\\Texture\\title1.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"title1_Material", material);

			texture = Resources::Load<Texture>(L"title2", L"..\\Resources\\Texture\\title2.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"title2_Material", material);
		}

		// mainLand
		{
			texture = Resources::Load<Texture>(L"world1_large_island_main", L"..\\Resources\\Texture\\world1_large_island_main.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"world1_large_island_main_Material", material);

			// �÷��̾�
			texture = Resources::Load<Texture>(L"Cuphead_Overload", L"..\\Resources\\Texture\\Cuphead_Overload.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Cuphead_Overload_Material", material);

			// ��
			texture = Resources::Load<Texture>(L"Shop", L"..\\Resources\\Texture\\Shop.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Shop_Material", material);

			// �÷���
			texture = Resources::Load<Texture>(L"Flag1", L"..\\Resources\\Texture\\Flag1.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Flag1_Material", material);
		}

		// Boss1
		{
			// ���
			//texture = Resources::Load<Texture>(L"BossStage1", L"..\\Resources\\Texture\\BossStage1.png");
			//material = std::make_shared<Material>();
			//material->SetShader(shader);
			//material->SetTexture(texture);
			//// material->SetRenderingMode(eRenderingMode::Transparent);
			//Resources::Insert(L"BossStage1_Material", material);

			// �����ղ�
			texture = Resources::Load<Texture>(L"FlowerFront", L"..\\Resources\\Texture\\flowerFront.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FlowerFront_Material", material);

			// ������Ǯ
			texture = Resources::Load<Texture>(L"BushFront", L"..\\Resources\\Texture\\bushFront.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"BushFront_Material", material);

			// ����
			texture = Resources::Load<Texture>(L"FlowerBoss", L"..\\Resources\\Texture\\FlowerBoss.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FlowerBoss_Material", material);

			// ĳ����
			texture = Resources::Load<Texture>(L"Cuphead_Boss", L"..\\Resources\\Texture\\Cuphead_Boss.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Cuphead_Boss_Material", material);

			// ü��(UI)
			texture = Resources::Load<Texture>(L"HP3", L"..\\Resources\\Texture\\HP3.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"HP3_Material", material);

			// �÷���
			texture = Resources::Load<Texture>(L"PlatformOne", L"..\\Resources\\Texture\\CagneyCarnation\\Platform\\Platform_A_01.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"PlatformOne_Material", material);
		}

		// �¸�ȭ��
		{
			// �޹��
			texture = Resources::Load<Texture>(L"winscreen_bg", L"..\\Resources\\Texture\\winscreen_bg.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"winscreen_bg_Material", material);

			// ����
			texture = Resources::Load<Texture>(L"winscreen_board", L"..\\Resources\\Texture\\winscreen_board.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"winscreen_board_Material", material);

			// ��
			texture = Resources::Load<Texture>(L"winscreen_stars", L"..\\Resources\\Texture\\winscreen_star.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"winscreen_star_Material", material);

			// ��� ����
			texture = Resources::Load<Texture>(L"winscreen_results_title", L"..\\Resources\\Texture\\winscreen_results_title.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"winscreen_results_title_Material", material);

			// ��� ĳ����
			texture = Resources::Load<Texture>(L"winscreen_ch", L"..\\Resources\\Texture\\winscreen_ch.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"winscreen_ch_Material", material);
		}

		// END	
		{
			texture = Resources::Load<Texture>(L"End", L"..\\Resources\\Texture\\End.png");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(texture);
			// material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"End_Material", material);
		}

		//// ��ƼŬ
		//std::shared_ptr<Shader> particleShader
		//	= Resources::Find<Shader>(L"ParticleShader");
		//std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		//// particleMaterial = std::make_shared<Material>();
		//particleMaterial->SetShader(particleShader);
		//particleMaterial->SetRenderingMode(eRenderingMode::Transparent);

		//std::shared_ptr<Texture> particleTexx
		//	= Resources::Find<Texture>(L"CartoonSmoke");
		//material->SetTexture(particleTexx);
		//Resources::Insert(L"ParticleMaterial", material);
	}

	// ���� ���� ������ uv��ǥ �������� �־��ش�. 
	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		// �������� ī�޶� ���� �̷����Ƿ�, ���� ���� ī�޶���� ��ȸ�ϸ�
		// ī�޶� Ŭ������ ���� �Լ��� ȣ���Ѵ�.
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		// �߰��� ī�޶� �߰��ɼ��ִ� ��쵵 ���� ���̴�.Ư���� ȿ���� ��� ���Դٰ� ������� ��찡 �ֱ� ����
		// �׷��� ī�޶� ���� ��ü�� ������ �� �Ŀ� ī�޶� clear�ؼ� �����ְ�,
		// �� �����Ӹ��� ȣ��Ǵ� ī�޶��� lateupdate���� �ٽ� ī�޶� ������ְ�, �� Render�Լ��� ȣ��Ǹ鼭
		// ��ϵ� ī�޶�� �������� �ϰ�, ����ߴ� ī�޶� �ٽ� �����ְ�.. �̷������� �ݺ��ǰԲ� ���ش�.
		// (�˾Ƽ� �����Ҵ� �ǰԲ�) 
		cameras.clear();
		lights.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

}



