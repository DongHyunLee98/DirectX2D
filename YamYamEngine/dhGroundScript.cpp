#include "dhGroundScript.h"
#include "dhCollider2D.h"
#include "dhGameObject.h"

namespace dh
{
	void GroundScript::Initialize()
	{

		Collider2D* collider = GetOwner()->AddComponent<Collider2D>();
	}
	void GroundScript::Update()
	{
	}
}