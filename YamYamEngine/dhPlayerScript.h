#pragma once
//#include "yaScript.h"
#include <dhScript.h>

namespace dh
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:

	};
}