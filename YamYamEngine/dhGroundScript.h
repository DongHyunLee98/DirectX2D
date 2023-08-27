#pragma once
#include <dhScene.h>
#include <dhGameObject.h>

namespace dh
{
	class GroundScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void OnCollisionEnter(Collider2D* other) override;
	};
};

