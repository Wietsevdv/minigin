#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
    class RenderComponent final : public Component
    {
    public:
		const std::string& Name() const override { return m_Name; }

		void Render(const Texture2D & texture, const glm::vec3& pos) const;

		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		const std::string m_Name = "RenderComponent";
    };
}