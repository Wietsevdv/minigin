#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		const std::string& Name() const override { return m_Name; }

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		const glm::vec3& GetPosition() const { return m_Transform.GetPosition(); }
		const Texture2D& GetTexture() const { return *m_Texture.get(); }

		TextureComponent() = default;
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		const std::string m_Name = "TextureComponent";

		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}