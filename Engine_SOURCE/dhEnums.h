#pragma once


namespace dh::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Rigidbody,
		Light,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Ground,
		Player,
		BackGround,
		Monster,
		NotMonster,
		Light,
		Camera,
		UI,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	// Rigid
	enum class eColliderOwner
	{
		None,
		Player,
		Monster,
		Ground,
		Bullet,
		UI,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}