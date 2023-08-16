#pragma once
#include "dhGameObject.h"

namespace dh
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void LateUpdate() override;

	private:
	};
}