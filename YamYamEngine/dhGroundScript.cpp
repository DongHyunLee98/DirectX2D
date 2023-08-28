#include "dhGroundScript.h"
#include "dhCollider2D.h"
#include "dhGameObject.h"
#include "dhObject.h"

namespace dh
{
	void GroundScript::Initialize()
	{
		Collider2D* collider = GetOwner()->AddComponent<Collider2D>();
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* other)
	{

		if (other->GetOwner()->GetName() == L"playerBullet")
		{
			// object::Destroy(other->GetOwner());
		}
	}
	void GroundScript::OnCollisionExit(Collider2D* other)
	{
		object::Destroy(other->GetOwner());
	}
}