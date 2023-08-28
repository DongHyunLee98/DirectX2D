#pragma once
#include <dhScript.h>
#include <dhAnimation.h>
#include "dhCagneyBossScript.h"

namespace dh
{
	class GameObject;
	class VineOneScript : public Script
	{
	public:
		VineOneScript();
		~VineOneScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;

		void SetThisObject(GameObject* passObj) { mObject = passObj;}

	public:
		Transform* mTrans;
		Collider2D* mColl;
		Animator* mAnim;
		GameObject* mObject;

	private:
		float vineOneDeleteTime;
		bool vineOneDeleteSwitch;
	};

}