#pragma once
#include "dhComponent.h"
#include "dhMesh.h"
#include "dhMaterial.h"

namespace dh
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}
